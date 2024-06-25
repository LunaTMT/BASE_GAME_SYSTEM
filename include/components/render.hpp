#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <random>

struct Rendering {
    sf::RectangleShape rectangle; // Declare sf::RectangleShape member
    
    Rendering()  
    {
        // Random number generation setup
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> randCol(0, 255); // Range for RGB values (0-255)
        std::uniform_int_distribution<int> randSize(1, 50); 

        // Generate random color
        sf::Color randomColor(randCol(gen), randCol(gen), randCol(gen));
        rectangle.setFillColor(randomColor); // Set random color to the rectangle

        rectangle.setSize(sf::Vector2f(randSize(gen), randSize(gen)));
    }
};


/*
#pragma once


struct Rendering {
    sf::RectangleShape rectangle; // Declare sf::RectangleShape member
    
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> dis; // Range for RGB values (0-255)

    Rendering() :  rectangle(sf::Vector2f(200, 100)), gen(rd()), dis(0, 255) {
        // Generate random RGB values
        sf::Color randomColor(dis(gen), dis(gen), dis(gen));
        rectangle.setFillColor(randomColor);
    }
};
*/