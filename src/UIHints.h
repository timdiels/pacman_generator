/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class Sounds;

class UIHints
{
public:
    UIHints(Sounds* snd);

    void ate_dot();
    void ate_energizer();
    void ate_ghost();
    void ate_pacman();
    void ghosts_no_longer_vulnerable();

private:
    Sounds *snd;
};