/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

//////////////////////////////////////////////////////
// Pacman version 4
// Started September 5, 2008
// using C++ & SDL
// ported to linux with attempt at crossplatform compatibility
//////////////////////////////////////////////////////

#include "Game.h"
#include "gui/GUI.h"
#include "Log.h"
#include "tests/Tests.h"
#include <sstream>

#include "Constants.h"

using namespace PACMAN;
using namespace MODEL;
using TEST::test;

using std::string;
using std::cout;

int main( int argc, char** argv ) {
    std::string str="";

    try {
        for (int i = 1;i<argc;i++) {
            str=argv[i];
            if (str=="--help") {
                std::cout << "pacman usage:\n\ncommandline arguments\n--help:\t\tshow this message\n"
                        << "ingame\nesc/q:\tquit\narrows:\tmovement\n"
                        << "n:\tnew game\n"
                        << "f:\ttoggle fps display\n";
                return 0;
            }
            else if (str == "--test") {
                std::istringstream str(argv[i+1]);
                int index;
                str >> index;
                test(index-1);
                return 0;
            }
            else
                std::cerr << "unrecognized commandline option\n";
        }

        srand( (unsigned int)time(NULL) );

        logtxt.setFilename(".pacman_sdl");

        Game game;
        GUI::GUI gui(game);
        shared_ptr<UIHints> uihints = gui.create_uihints();

        //main loop
        while (gui.emptyMsgPump()) {
            gui.render();

            Action actions[PLAYER_COUNT] = {0, 0, 0, 0, 0};
            game.step(actions, uihints);
        }

        //shutdown
        logtxt.print( "Shutdown" );
    }
    catch (const std::exception& e) {
        logtxt.log_exception(e);
        return 1;
    }

    return 0;
}