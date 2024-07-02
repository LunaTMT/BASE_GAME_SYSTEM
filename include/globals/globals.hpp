// globals.hpp
#pragma once

#include "coordinator.hpp"
#include "resource_handler.hpp"
#include "textureID.hpp"
#include "soundID.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Declare and define the global Coordinator using inline
inline Coordinator g_coordinator;

inline ResourceHolder<sf::Texture, TextureID> g_textureHolder;
inline ResourceHolder<sf::Sound, SoundID> g_soundHolder;

inline unsigned int WINDOW_WIDTH = 800;
inline unsigned int WINDOW_HEIGHT = 600;