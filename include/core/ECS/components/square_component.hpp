#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <random>

struct RenderingSquare {
    sf::RectangleShape rectangle; // Declare sf::RectangleShape member
    
    RenderingSquare()  
    {
        // Random number generation setup
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> randCol(0, 255); // Range for RGB values (0-255)
        std::uniform_int_distribution<int> randSize(1, 50); 

        // Generate random color
        sf::Color randomColor(randCol(gen), randCol(gen), randCol(gen));
        rectangle.setFillColor(randomColor); // Set random color to the rectangle
        rectangle.setPosition(sf::Vector2f(300, 200));
        rectangle.setSize(sf::Vector2f(randSize(gen), randSize(gen)));
    }
};


