#pragma once
#include <SFML/Graphics.hpp>
#include <bitset>

    
using Entity = std::uint32_t;
static constexpr Entity MAX_ENTITIES = 5000; // Make MAX_ENTITIES static constexpr

using ComponentType = std::uint8_t;
static constexpr ComponentType MAX_COMPONENTS = 32; // Make MAX_COMPONENTS static constexpr

using Signature = std::bitset<MAX_COMPONENTS>; // Use MAX_COMPONENTS as template argument