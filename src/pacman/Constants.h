/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <string>
#include "Point.h"

namespace PACMAN {
    namespace SPECIFICATION {
        // ticks per second
        extern const int TICK_RATE;

        extern const double NORMAL_PACMAN_SPEED;
        extern const double ENERGETIC_PACMAN_SPEED;
        extern const double GHOST_TUNNEL_SPEED;
        extern const double GHOST_VULNERABLE_SPEED;
        extern const double ELROY2_SPEED;
        extern const double ELROY1_SPEED;
        extern const double GHOST_NORMAL_SPEED;
        // the amount of ticks ghosts are vulnerable
        extern const int VULNERABLE_TICKS;
        // the amount of ticks fruit stays on the map after spawning
        extern const int FRUIT_TICKS;
        // 100% speed expressed in tiles per tick.
        extern const double FULL_SPEED;

        // initial food count of start_foods, which is also the max
        extern const unsigned int MAX_FOOD_COUNT;
        extern const IPoint FRUIT_LEFT_TPOS;
        extern const IPoint FRUIT_RIGHT_TPOS;
        extern const FPoint FRUIT_POS;
    }

    namespace GUI {
        // path to skin images
        extern const std::string SKINS_PATH;
    }
}


// note: namespaces have no effect on defines, because preprocessor doesn't understand C++

// pixel size of a tile, is best kept as a multiple of 8
extern const int TILE_SIZE;

// map sizes in tiles
#define MAP_WIDTH 28
#define MAP_HEIGHT 31

#define MAX_ACTION_COUNT 4

// size of ghost/pacman
#define PLAYER_SIZE (2.0 * TILE_SIZE * 0.8)

#define GHOST_COUNT 4
#define PLAYER_COUNT (GHOST_COUNT + 1)

// player indices
extern const int PLAYER_PACMAN;

// ghost indices (+1 to convert to player index)
#define GHOST_BLINKY 0
#define GHOST_PINKY 1
#define GHOST_INKY 2
#define GHOST_CLYDE 3
