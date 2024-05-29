#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>


#include "game.h"

int main(int argc, char** argv){
    Game game;
    while(!game.GetWindow()->IsDone()){
        game.HandleInput();
        game.Update();
        game.Render();
        game.RestartClock();
    }
}

