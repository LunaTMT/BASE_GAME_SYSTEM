#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>


#include "game.h"

int main(int argc, char** argv){
    Game game;
    
    try{    
        while(!game.GetWindow()->IsDone()){
            game.HandleInput();
            game.Update();
            game.Render();
            game.RestartClock();
        }
    } catch (...) {
        std::cout << "" << std::endl;
    }
}

