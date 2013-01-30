/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <pacman/util/Directions.h>
#include <pacman/run/Game.h>
#include <pacman/run/DirectionPreference.h>
#include <pacman/model/Action.h>
#include <pacman/model/NullUIHints.h>

namespace PACMAN {
    namespace MODEL {
        class GameState;
    }

    namespace TEST {

        class Test : public RUN::DirectionPreference {
        public:
            Test(int player_index);
            int move(Direction::Type direction);
            void directions_to_actions(Direction::Type pacman, Direction::Type blinky, Direction::Type pinky, Direction::Type inky, Direction::Type clyde, ::PACMAN::MODEL::Action* actions);
            const ::PACMAN::MODEL::GameState* get_state();
            Direction::Type get_preferred_direction();

        private:
            Direction::Type current_direction;
            int player_index;
            ::PACMAN::RUN::Game game;
            ::PACMAN::MODEL::NullUIHints uihints;
        };

    }
}
