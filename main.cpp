#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>


#include "game.h"

int main(int argc, char** argv){
    Game game;
    
    try{    
        game.Run();
    } catch (...) {
        std::cout << "" << std::endl;
    }
}

