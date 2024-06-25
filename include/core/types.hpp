#pragma once
#include <bitset>
#include <cstdint> // Ensure <cstdint> is included for fixed-width integer types

// Type alias for Entity
using Entity = std::uint32_t;
static constexpr Entity MAX_ENTITIES = 5000; // Maximum number of entities

// Type alias for ComponentType
using ComponentType = std::uint8_t;
static constexpr ComponentType MAX_COMPONENTS = 32; // Maximum number of component types

// Signature type for entities
using Signature = std::bitset<MAX_COMPONENTS>;



