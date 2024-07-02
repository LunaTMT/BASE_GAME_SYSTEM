#include "window.h"
#include "types.hpp"

#include "physics_system.hpp"
#include "render_system.hpp"

#include "globals.hpp"

#include "willow.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>
#include <chrono>

class Game
{
public:
    Game();
    ~Game();

    void HandleInput();
    void Update();
    void Render();

    void Run();

    Window* GetWindow();

    sf::Time GetElapsed();
    void RestartClock();

    

private:
    

    Window m_window;
    sf::Clock m_clock;
    sf::Time m_elapsed;

    std::shared_ptr<PhysicsSystem> m_physicsSystem;
    std::shared_ptr<RenderSystem>  m_renderSystem;

    sf::RectangleShape m_rectangle;

    //Used for fixed time step (dt)
    sf::Time m_timePerFrame = sf::seconds(1.0f / 60.0f);
    sf::Time m_timeSinceLastUpdate = sf::Time::Zero;

    //ResourceHolder<sf::Texture, TextureID> textureHolder;
    //ResourceHolder<sf::Sound, SoundID> soundHolder;

    //experiments
    Willow m_willow;
    

    // Load a font
    sf::Font m_font;
    sf::Text m_fps_text;
    int m_fps = 0;


    sf::Texture m_dvd_texture;  


};