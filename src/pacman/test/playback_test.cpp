/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "playback_test.h"
#include <pacman/model/NullUIHints.h>
#include <pacman/model/IntermediateGameState.h>
#include <pacman/run/PlaybackInput.h>

#include <memory>

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;

using namespace ::PACMAN::MODEL;
using namespace ::PACMAN::RUN;

namespace PACMAN {
    namespace TEST {

PlaybackTest::PlaybackTest(const std::vector<Action>& path, const ExternalGameState& game_state, int player_index, int recorded_steps) 
:   expected_state(game_state),
    recorded_steps(recorded_steps)
{
    game.init(Game::make_inputs(player_index, shared_ptr<Input>(new PlaybackInput(path))), shared_ptr<UIHints>(new NullUIHints));
}

void PlaybackTest::run() {
    game.run(*this);

    ASSERT(game.get_state().is_equivalent_to(expected_state));
}

void PlaybackTest::finished_step(const ::PACMAN::MODEL::GameState& state) {
}

bool PlaybackTest::should_stop() {
    return recorded_steps == game.get_steps();
}

bool PlaybackTest::is_paused() {
    return false;
}

void playback_test(const std::vector<Action>& path, const ExternalGameState& game_state, const int player_index, const int recorded_steps) {
    PlaybackTest test(path, game_state, player_index, recorded_steps);
    test.run();
}

}}
