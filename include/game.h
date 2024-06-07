#include "window.h"
#include "resource_handler.hpp"
#include "textureID.hpp" 
#include "soundID.hpp"
#include <SFML/Audio.hpp>


class Game
{
public:
    Game();
    ~Game();

    void HandleInput();
    void Update();
    void Render();

    Window* GetWindow();

    sf::Time GetElapsed();
    void RestartClock();

    ResourceHolder<sf::Texture, TextureID> textureHolder;
    ResourceHolder<sf::Sound, SoundID> soundHolder;

private:

    Window m_window;
    sf::Clock m_clock;
    sf::Time m_elapsed;


    
};
