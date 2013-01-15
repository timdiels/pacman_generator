/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Tests.h"
#include "MinimaxTests.h"
#include "GeneratorTests.h"

#include "Test.h"
#include "util.h"

#include "../model/GameState.h"
#include "../Point.h"
#include "../Constants.h"

#include <boost/assert.hpp>

using std::cout;
using std::endl;
using std::vector;

using namespace PACMAN::MODEL;
using namespace PACMAN::SPECIFICATION;

namespace PACMAN {
    namespace TEST {


void test_initial_game_state() {
    Test test;
    auto state = test.get_state();

    // start positions
    assert_equals(state->get_player(0).get_pixel_pos(), FPoint(14, 23.5) * TILE_SIZE);
    assert_equals(state->get_player(0).get_tile_pos(), IPoint(14, 23));
    assert_equals(state->get_player(GHOST_BLINKY+1).get_pixel_pos(), FPoint(14, 11.5) * TILE_SIZE);
    assert_equals(state->get_player(GHOST_PINKY+1).get_pixel_pos(), FPoint(14, 14) * TILE_SIZE);
    assert_equals(state->get_player(GHOST_INKY+1).get_pixel_pos(), FPoint(12, 14) * TILE_SIZE);
    assert_equals(state->get_player(GHOST_CLYDE+1).get_pixel_pos(), FPoint(16, 14) * TILE_SIZE);

    // vulnerability
    for (int i=0; i < GHOST_COUNT; ++i) {
        BOOST_ASSERT(((GhostState&)state->get_player(i+1)).state == GhostState::NORMAL);
    }
}

void test_ghosts_remain_normal_when_not_eating_energizer() {
    Test test;
    test.move(1, Direction::ANY);
}

void test_pacman_movement_regular_speed_not_cornering() {
    Test test;

    assert_equals(test.move(0, Direction::EAST), (int)ceil(1 /*tile*/ / (FULL_SPEED * NORMAL_PACMAN_SPEED)));
    auto tile_pos = test.get_state()->get_player(0).get_tile_pos();
    assert_equals(tile_pos, IPoint(15, 23));

    // check we are really moving east
    test.move(0, Direction::EAST);
    tile_pos = test.get_state()->get_player(0).get_tile_pos();
    assert_equals(tile_pos, IPoint(16, 23));
}

void test_dot_eating_no_cornering() {
    Test test;

    int start_food = test.get_food_count();
    test.move(0, Direction::EAST);
    assert_equals(test.get_food_count(), start_food-1);

    // should take 1 step longer because pacman idles 1 tick after eating a dot
    assert_equals(test.move(0, Direction::EAST), 1 + (int)ceil(1 /*tile*/ / (FULL_SPEED * NORMAL_PACMAN_SPEED)));
    assert_equals(test.get_food_count(), start_food-2);
}

/* TODO
 * move from node to node takes expected amount of ticks:
 * - pacman:
 *   - at regular speed:
 *     - move between nodes
 *     - do a corner
 *   - at vulnerable speed:
 *     - move between nodes
 *     - do a corner
 * - ghost:
 *   - for every speed: move between nodes, =doing a corner
 *
 * fruit, ...
 */

void test(int index) {
    typedef void (*TestFunc)();

    vector<TestFunc> tests = {
        test_initial_game_state,
        test_ghosts_remain_normal_when_not_eating_energizer,
        test_pacman_movement_regular_speed_not_cornering,
        test_dot_eating_no_cornering,
        MinimaxTests::test_1,
        GeneratorTests::test_1,
        GeneratorTests::test_save_load,
        GeneratorTests::test_save_load_of_running_instance
    };
    tests.at(index)();
}

}}
