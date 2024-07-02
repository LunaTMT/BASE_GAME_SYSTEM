#!/bin/bash

# Compile the main.cpp file
g++ main.cpp -o main src/*.cpp src/sprites/*.cpp -Iinclude  -Iinclude/systems -Iinclude/core -Iinclude/core/scene -Iinclude/core/sprites  -Iinclude/core/ECS -Iinclude/core/ECS/components -Iinclude/core/ECS/managers -Iinclude/core/systems -Iinclude/globals -Iinclude/IDs  -lsfml-graphics -lsfml-window -lsfml-system

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Build successful. "
    ./main
else
    echo "Build failed."
fi

