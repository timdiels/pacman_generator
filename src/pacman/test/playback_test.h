/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <pacman/model/Action.h>
#include <pacman/run/GameObserver.h>
#include <pacman/run/Game.h>

#include <vector>

namespace PACMAN {
    namespace MODEL {
        class ExternalGameState;
    }

    namespace TEST {
        void playback_test(const std::vector<MODEL::Action>& path, const ::PACMAN::MODEL::ExternalGameState& game_state, const int player_index, const int recorded_steps);

        class PlaybackTest : public ::PACMAN::RUN::GameObserver {
        public:
            PlaybackTest(const std::vector< ::PACMAN::MODEL::Action>& path, const ::PACMAN::MODEL::ExternalGameState& game_state, int player_index, int recorded_steps);
            void run();

            void finished_step(const ::PACMAN::MODEL::GameState& state);
            bool should_stop();
            bool is_paused();

        private:
            const ::PACMAN::MODEL::ExternalGameState& expected_state;
            const int recorded_steps;
            ::PACMAN::RUN::Game game;
        };
    }
}
