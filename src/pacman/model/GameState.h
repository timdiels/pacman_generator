/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <boost/utility.hpp>
#include "PacmanState.h"
#include "GhostState.h"
#include "../specification/Food.h"
#include "../Constants.h"

#include <assert.h>
#include <vector>

namespace PACMAN {

    namespace TEST {
        class Test;
    }

    namespace MODEL {

        class UIHints;

        class GameState : public boost::noncopyable  // why copy a big thing when you can point!
        {
        public:
            static shared_ptr<GameState> start_new_game(const Node* pacman_spawn, const std::vector<Node*> ghost_spawns);
            shared_ptr<GameState> get_successor(const Action* actions, UIHints& app);  // game state after 1 tick/frame

            bool get_vulnerable_ghost_count() const;

            inline int get_level() const {
                return 1;
            }

            inline int get_score() const {
                return score;
            }

            inline int get_lives() const {
                return lives;
            }

            inline bool did_pacman_lose() const {
                assert(lives >= 0);
                return lives == 0;
            }

            inline bool did_pacman_win() const {
                return food_count == 0;
            }

            inline const PlayerState& get_player(int index) const {
                if (index == 0) {
                    return pacman;
                }
                else {
                    return ghosts[index-1];
                }
            }

            inline const SPECIFICATION::Foods& get_foods() const {
                return foods;
            }

        private:
            GameState(const Node* pacman_spawn, const std::vector<Node*> ghost_spawns);
            GameState(const Action* actions, const GameState* state, UIHints& app);

            void resetLvl();
            void nextLvl();

            inline int get_fruit_score() const {
                return 100;
            }

            bool is_elroy1(int ghost_index) const;
            bool is_elroy2(int ghost_index) const;

        private:
            PacmanState pacman;
            GhostState ghosts[GHOST_COUNT];

            SPECIFICATION::Foods foods; // shows where food lies on the map
            int food_count;
            int score;
            int lives;

            bool fruit_spawned;

            int vulnerable_ticks_left;  // how many more ticks ghosts will be vulnerable
            int fruit_ticks_left;  // amount of ticks left til fruit disappears
            int idler_ticks_left;  // ticks left til pacman gets off his lazy ass and starts moving again (pacman rests after eating dot or energizer)

            friend class PACMAN::TEST::Test;
        };

    }
}