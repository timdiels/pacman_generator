/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "PacmanChoiceTree.h"

#include "../model/GameState.h"
#include "../model/PacmanNodes.h"
#include "../model/GhostNodes.h"
#include "../Constants.h"
#include "../util/assertion.h"

namespace PACMAN {

    using namespace MODEL;
    using namespace SPECIFICATION;

    namespace GENERATOR {

static const int MAX_CHOICES = 100;  // the max depth of choices to generate into

PacmanChoiceTree::PacmanChoiceTree() 
:   initialised(false),
    search_complete(false)
{
    choices.reserve(MAX_CHOICES);
    states.reserve(MAX_CHOICES);  // Note: this is probably too much as sometimes multiple players need to move at the same time in the same tick

    states.emplace_back(PACMAN_NODES.get_spawn(), GHOST_NODES.get_spawns());

    // progress to initial choice
    int next_player = progress_game_until_choice(get_state());
    ASSERT(next_player > -1); // the game of pacman has choices
    push_choice(next_player);

    initialised = true;
    ASSERT_INVARIANTS();
}

/*
 * Returns true if player has multiple legal actions to act upon the current state
 */
bool PacmanChoiceTree::has_choice(int player) const {
    REQUIRE(player >= 0);
    REQUIRE(player < PLAYER_COUNT);
    LegalActions legal_actions;
    get_state().get_player(player).get_legal_actions(legal_actions);
    return legal_actions.count > 1;
}

void PacmanChoiceTree::parent() {
    REQUIRE(!search_complete);
    //REQUIRE(choices.size() > 0);

    auto previous = choices.back();
    choices.pop_back();

    if (choices.empty()) {
        // popped the last choice, search complete
        states.pop_back();
        ASSERT(states.empty());
        search_complete = true;
    }
    else if (get().player >= previous.player) {
        states.pop_back();
    }

    ASSERT_INVARIANTS();
}

/*
 * Proceeds to next legal action
 *
 * Returns whether there was a next legal action to try
 */
bool PacmanChoiceTree::next_sibling() {
    REQUIRE(!search_complete);

    LegalActions legal_actions;
    get_state().get_player(get().player).get_legal_actions(legal_actions);
    bool has_next_action = get().action + 1 < legal_actions.count;
    if (has_next_action) {
        ++get_().action;
    }

    ASSERT_INVARIANTS();
    return has_next_action;
}

void PacmanChoiceTree::first_child() {
    REQUIRE(!search_complete);
    REQUIRE(!is_leaf());

    const int next_player = progress_game_state();
    push_choice(next_player);
}

bool PacmanChoiceTree::is_leaf() {
    REQUIRE(!search_complete);
    return get().player == -1 || choices.size() == choices.capacity() < 0;
}

int PacmanChoiceTree::get_score() {
    REQUIRE(!search_complete);
    return get_state().get_score();
}

int PacmanChoiceTree::get_max_depth() {
    REQUIRE(!search_complete);
    return MAX_CHOICES - 1;
}

const ChoiceNode& PacmanChoiceTree::get() const {
    REQUIRE(!search_complete);
    return choices.back();
}

const ChoiceNode& PacmanChoiceTree::get(int depth) const {
    REQUIRE(!search_complete);
    return choices.at(depth);
}

void PacmanChoiceTree::push_choice(int next_player) {
    REQUIRE(next_player >= 0);
    REQUIRE(next_player < PLAYER_COUNT);

    REQUIRE(!choices.empty());

    choices.emplace_back(ChoiceNode{-1, next_player});

    ASSERT_INVARIANTS();
}

/*
 * Returns first player that still needs to choose an action for next tick
 *
 * Returns -1 if no player has a choice.
 *
 * player: index of first player that might have a choice
 */
int PacmanChoiceTree::get_first_undecided(int player) const {
    REQUIRE(player >= 0);
    REQUIRE(player < PLAYER_COUNT);

    while (!has_choice(player)) {
        ++player;
        if (player == PLAYER_COUNT) {
            player = -1;
            break;
        }
    }

    ENSURE(player < PLAYER_COUNT);
    return player;
}

/*
 * Progresses the game up til game over, or the next choice
 *
 * Makes use of this->choices when necessary.
 *
 * Returns the player who has to make a choice, or -1 if game over
 */
int PacmanChoiceTree::progress_game_state() {
    REQUIRE(get().action > -1);  // current player has chosen

    // sufficient choices made to proceed to next state?
    int next_player = get().player + 1;
    if (next_player < PLAYER_COUNT) {
        next_player = get_first_undecided(next_player);
    }
    else {
        next_player = -1;
    }

    if (next_player == -1) {
        GameState state = get_state();

        // get actions
        Action actions[PLAYER_COUNT] = {-1, -1, -1, -1, -1};
        for (int i=0; i<=get().player; ++i) {
            if (has_choice(i)) {
                // TODO extract get_action(i)
                int j = depth;
                while (j < choices.size()) {
                    if (get(j).player == i) {
                        actions[i] = get(j).action;
                        break;
                    }
                    ++j;
                }
                ENSURE(actions[i] > -1);
            }
            else {
                actions[i] = 0;
            }
        }

        // proceed to next state
        state = GameState(actions, &state, uihints);

        progress_game_until_choice(state);
    }
    
    ENSURE(get_state().is_game_over() || has_choice(next_player));
    ENSURE(!get_state().is_game_over() || next_player == -1);
    ASSERT_INVARIANTS();
    return next_player;
}

/*
 * Progress game state until game over or a player has a choice
 */
int PacmanChoiceTree::progress_game_until_choice(GameState& state) {
    int next_player = -1;

    // progress as far as possible
    Action actions[PLAYER_COUNT] = {0, 0, 0, 0, 0};
    while (!state.is_game_over() && (next_player = get_first_undecided(0)) == -1) {
        state = GameState(actions, &state, uihints);
    }

    // push state
    states.push_back(state);

    ENSURE(get_state().is_game_over() || has_choice(next_player));
    ENSURE(!get_state().is_game_over() || next_player == -1);
    ASSERT_INVARIANTS();
    return next_player;
}


void PacmanChoiceTree::invariants() {
    INVARIANT(states.capacity() == MAX_CHOICES);
    INVARIANT(!states.empty() || search_complete);  // state_index valid unless search_complete

    INVARIANT(choices.capacity() == MAX_CHOICES);
    INVARIANT(!initialised || search_complete || depth < choices.size()); // depth valid unless not initialised or search completed

    INVARIANT(state_index >= depth);

    INVARIANT(get().player >= -1);

    // Invariant: the action field of all ancestors is valid and shows the path
    // to the current node
}

}}