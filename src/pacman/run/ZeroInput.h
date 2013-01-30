/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "Input.h"

namespace PACMAN {
    namespace RUN {

        /*
         * Alwas returns Action 0
         */
        class ZeroInput : public Input
        {
        public:
            ::PACMAN::MODEL::Action get_action(int player_index, const ::PACMAN::MODEL::IntermediateGameState& state);
        };

    }
}
