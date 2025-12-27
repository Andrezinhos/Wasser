#include <iostream>
#include "Players.hpp" 
#include "Booster.hpp" 
#include "states.hpp" 
#include <string>

void Players::runBoost(){
    Booster b;
    state.clearScreen();
    while(true){
                std::string title = R"( ____  _____     _______ ____  
|  _ \|_ _\ \   / / ____|  _ \
| |_) || | \ \ / /|  _| | |_) |
|  _ < | |  \ V / | |___|  _ < 
|_| \_\___|  \_/  |_____|_| \_\
Powered by Wasser Boost
)"; 
        std::cout << title;
        std::cout << "=================================\n";
        std::cout << "enter the commands\n";
        std::cout << "--------------------\n";
        std::cout << "> ";
        std::string cmd;
        std::cin >> cmd;
        
        if (cmd == "play" || cmd == "."){
            std::string song;
            std::cout << "Type the name: ";
            std::cin >> song;
            state.clearScreen();
            b.play(song);
        }
        else if (cmd == "replay" || cmd == ","){
            state.clearScreen();
            b.replay();
        }
        else if (cmd == "stop" || cmd == ";"){
            state.clearScreen();
            b.stop();
        }
        else if (cmd == "exit" || cmd == "!"){
            state.clearScreen();
            break;
        }
    }
}