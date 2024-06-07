#include "game.h"
#include <iostream>

Game::Game(): m_window("Tut", sf::Vector2u(800,600)) {
    //textureHolder.load(TextureID::Snake, "assets/images/whisp.png");

    //sf::Texture& snakeTexture = textureHolder.get(TextureID::Snake);

}

Game::~Game() {}


void Game::Update(){
    m_window.Update();

}

void Game::HandleInput(){
    std::cout<<"";
}

void Game::Render(){
    m_window.BeginDraw();
    //m_window.Draw(m_snakeSprite);
    m_window.EndDraw();
}

Window* Game::GetWindow(){
    return &m_window;
}

sf::Time Game::GetElapsed(){ return m_elapsed; }

void Game::RestartClock(){ m_elapsed += m_clock.restart(); }

