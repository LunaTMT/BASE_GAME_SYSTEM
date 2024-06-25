#include "game.h"
#include <iostream>

#include <random>
#include <chrono>



Game::Game(): m_window("Tut", sf::Vector2u(800,600)) {
    m_coordinator.Init();

    m_coordinator.RegisterComponent<Gravity>();
    m_coordinator.RegisterComponent<RigidBody>();
    m_coordinator.RegisterComponent<Transform>();

    m_physicsSystem = m_coordinator.RegisterSystem<PhysicsSystem>();

    Signature signature;
	signature.set(m_coordinator.GetComponentType<Gravity>());
	signature.set(m_coordinator.GetComponentType<RigidBody>());
	signature.set(m_coordinator.GetComponentType<Transform>());
	m_coordinator.SetSystemSignature<PhysicsSystem>(signature);

	std::vector<Entity> entities(MAX_ENTITIES);

	std::default_random_engine generator;
	std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
	std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
	std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
	std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);

	float scale = randScale(generator);

    for (auto& entity : entities)
    {
        entity = m_coordinator.CreateEntity();

        m_coordinator.AddComponent(
            entity,
            Gravity{
                sf::Vector2f(0.0f, randGravity(generator))
            });

        m_coordinator.AddComponent(
            entity,
            RigidBody{
                sf::Vector2f(0.0f, 0.0f),
                sf::Vector2f(0.0f, 0.0f)
            });

        m_coordinator.AddComponent(
            entity,
            Transform{
                sf::Vector2f(randPosition(generator), randPosition(generator)),
                sf::Vector2f(randPosition(generator), randPosition(generator)),
                sf::Vector2f(scale, scale)
            });
    }
}

Game::~Game() {}


void Game::Update(){

    sf::Time deltaTime = m_clock.restart();
    float dt = deltaTime.asSeconds();
    
    m_window.Update();
    m_physicsSystem->Update(dt);

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

