/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Tests.h"
#include <pacman/test/Test.h>
#include <pacman/model/GameState.h>
#include <pacman/util/assertion.h>
#include <pacman/util/Point.h>
#include <pacman/Constants.h>

using std::cout;
using std::endl;
using std::vector;
using std::string;

using namespace PACMAN::MODEL;
using namespace PACMAN::SPECIFICATION;

namespace PACMAN {
    namespace TEST {
        namespace MODEL {

/*
 * Map has 240 dots and 4 energizers
 */
void test_start_foods() {
    // validate a part of requirements: start_foods
    int dot_count = 0;
    int energizer_count = 0;
    for (int y=0; y<MAP_HEIGHT; ++y) {
        for (int x=0; x<MAP_WIDTH; ++x) {
            int food_index = y*MAP_WIDTH + x;
            if (start_foods[food_index] == Food::DOT) {
                ++dot_count;
            }
            if (start_foods[food_index] == Food::ENERGIZER) {
                ++energizer_count;
            }
        }
    }
    ASSERT(dot_count == 240);
    ASSERT(energizer_count == 4);
}

/*
 * Correct spawn positions
 */
void test_initial_game_state() {
    Test test(PLAYER_PACMAN);
    auto state = test.get_state();

    ASSERT(state->get_player(PLAYER_PACMAN).get_pixel_pos() == FPoint(14, 23.5) * TILE_SIZE);
    ASSERT(state->get_player(PLAYER_PACMAN).get_tile_pos() == IPoint(14, 23));
    ASSERT(state->get_player(GHOST_BLINKY+1).get_pixel_pos() == FPoint(14, 11.5) * TILE_SIZE);
    ASSERT(state->get_player(GHOST_PINKY+1).get_pixel_pos() == FPoint(14, 14) * TILE_SIZE);
    ASSERT(state->get_player(GHOST_INKY+1).get_pixel_pos() == FPoint(12, 14) * TILE_SIZE);
    ASSERT(state->get_player(GHOST_CLYDE+1).get_pixel_pos() == FPoint(16, 14) * TILE_SIZE);
}

/*
 * Regression test to an earlier fix
 */
void test_ghosts_remain_normal_when_not_eating_energizer() {
    Test test(1);
    test.move(Direction::ANY);
}

/*
 * Correct timing normal speed pacman movement
 */
void test_pacman_movement_regular_speed_not_cornering() {
    Test test(PLAYER_PACMAN);

    ASSERT(test.move(Direction::EAST) == (int)ceil(1 /*tile*/ / (FULL_SPEED * NORMAL_PACMAN_SPEED)) +1); // +1 because the first tick is a tick for the initial game state to tell players what to do, actual movement starts from the second tick onwards
    auto tile_pos = test.get_state()->get_player(PLAYER_PACMAN).get_tile_pos();
    ASSERT(tile_pos == IPoint(15, 23));

    // check we are really moving east
    test.move(Direction::EAST);
    tile_pos = test.get_state()->get_player(PLAYER_PACMAN).get_tile_pos();
    ASSERT(tile_pos == IPoint(16, 23));
}

/*
 * Correct timing of dot eating when not cornering
 */
void test_dot_eating_no_cornering() {
    Test test(PLAYER_PACMAN);

    int start_food = test.get_state()->get_food_count();
    test.move(Direction::EAST);
    ASSERT(test.get_state()->get_food_count() == start_food-1);

    // should take 1 step longer because pacman idles 1 tick after eating a dot
    ASSERT(test.move(Direction::EAST) == 1 + (int)ceil(1 /*tile*/ / (FULL_SPEED * NORMAL_PACMAN_SPEED)));
    ASSERT(test.get_state()->get_food_count() == start_food-2);
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

}}}
