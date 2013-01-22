/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Constants.h"

namespace PACMAN {
    namespace SPECIFICATION {
        const int TICK_RATE = 60;

        const double NORMAL_PACMAN_SPEED = 0.8;
        const double ENERGETIC_PACMAN_SPEED = 0.9;
        const double GHOST_TUNNEL_SPEED = 0.4;
        const double GHOST_VULNERABLE_SPEED = 0.5;
        const double ELROY2_SPEED = 0.85;
        const double ELROY1_SPEED = 0.8;
        const double GHOST_NORMAL_SPEED = 0.75;

        const int VULNERABLE_TICKS = 6 * TICK_RATE;
        const int FRUIT_TICKS = 10 * TICK_RATE;
        const double FULL_SPEED = 9.5 / TICK_RATE;

        const unsigned int MAX_FOOD_COUNT = 244u;

        const IPoint FRUIT_LEFT_TPOS(13, 17);
        const IPoint FRUIT_RIGHT_TPOS(14, 17);
        const FPoint FRUIT_POS(14 * TILE_SIZE, 17.5 * TILE_SIZE);

        const int MAX_TICKS_BETWEEN_GHOST_RELEASE = 4 * TICK_RATE;  // 4 seconds
    }

    namespace GUI {
        const std::string SKINS_PATH = "./skins/minimal/";
    }
}

const int TILE_SIZE = 20;
const int PLAYER_PACMAN = 0;
