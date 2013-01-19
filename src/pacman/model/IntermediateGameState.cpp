/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "IntermediateGameState.h"
#include "../util/serialization.h"
#include "../util/assertion.h"
#include "../model/PacmanNodes.h"
#include "../model/GhostNodes.h"

using std::vector;
using std::cout;
using std::endl;

namespace PACMAN {
    namespace MODEL {

// intermediate state with new_game as predecessor
IntermediateGameState::IntermediateGameState(const GameState predecessor)
:   predecessor(predecessor),
    successor(predecessor)
{
    for (int i=0; i < PLAYER_COUNT; ++i) {
        movement_excess[i] = 0.0;
    }
}

IntermediateGameState::IntermediateGameState(const GameState predecessor, UIHints& uihints)
:   predecessor(predecessor),
    successor(GameState(predecessor, uihints, movement_excess))
{
}

IntermediateGameState::IntermediateGameState(std::istream& in, UIHints& uihints)
:   IntermediateGameState(GameState(in), uihints)
{
}

void IntermediateGameState::save(std::ostream& out) const {
    REQUIRE(predecessor != successor); // Can't save the initial/new game state
    predecessor.save(out);
}

IntermediateGameState IntermediateGameState::new_game() {
    return IntermediateGameState(GameState(PACMAN_NODES.get_spawn(), GHOST_NODES.get_spawns()));
}

const PlayerState& IntermediateGameState::get_player(int index) const {
    return successor.get_player(index);
}

bool IntermediateGameState::operator==(const IntermediateGameState& o) const {
    for (int i=0; i < PLAYER_COUNT; ++i) {
        if (o.movement_excess[i] != movement_excess[i]) {
            return false;
        }
    }

    return o.predecessor == predecessor &&
        o.successor == successor;
}

IntermediateGameState IntermediateGameState::act(const std::vector<Action>& actions, UIHints& uihints) const {
    auto copy = successor;
    copy.act(actions, predecessor, uihints, movement_excess);

    IntermediateGameState next_intermediate(copy, uihints);
    return next_intermediate;
}

}}