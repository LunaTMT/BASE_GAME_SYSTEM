#include "game.h"


Game::Game(): m_window("Tut", sf::Vector2u(800,600)) {
    gCoordinator.Init();

    
    gCoordinator.RegisterComponent<Gravity>();
    gCoordinator.RegisterComponent<RigidBody>();
    gCoordinator.RegisterComponent<Transform>();
    gCoordinator.RegisterComponent<Rendering>();

    m_physicsSystem = gCoordinator.RegisterSystem<PhysicsSystem>();
    m_renderSystem  = gCoordinator.RegisterSystem<RenderSystem>();

    Signature physicsSignature;
	physicsSignature.set(gCoordinator.GetComponentType<Gravity>());
	physicsSignature.set(gCoordinator.GetComponentType<RigidBody>());
	physicsSignature.set(gCoordinator.GetComponentType<Transform>());
    gCoordinator.SetSystemSignature<PhysicsSystem>(physicsSignature);



    Signature renderSignature;
	renderSignature.set(gCoordinator.GetComponentType<Rendering>());
    gCoordinator.SetSystemSignature<RenderSystem>(renderSignature);



	std::default_random_engine generator;
	std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
	std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
	std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
	std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);

    std::uniform_real_distribution<float> randVelocity(-10.0f, 10.0f);
    std::uniform_real_distribution<float> randAcceleration(-5.0f, 5.0f);

    for (int _ = 0; _ < 10; ++_) 
    {
        u_int32_t entity = gCoordinator.CreateEntity();
        float scale = randScale(generator);

        gCoordinator.AddComponent(
            entity,
            Gravity{
                sf::Vector2f(0.0f, randGravity(generator))
            });

        gCoordinator.AddComponent(
            entity,
            RigidBody{
                sf::Vector2f(randVelocity(generator), randVelocity(generator)),
                sf::Vector2f(randAcceleration(generator), randAcceleration(generator))
            });

        gCoordinator.AddComponent(
            entity,
            Transform{
                sf::Vector2f(randPosition(generator), randPosition(generator)),
                randRotation(generator),
                sf::Vector2f(scale, scale)
            });

        gCoordinator.AddComponent(
            entity, 
            Rendering{}); 
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

    m_renderSystem->Render(m_window.GetRenderWindow());
    



    m_window.EndDraw();
}

Window* Game::GetWindow(){
    return &m_window;
}

sf::Time Game::GetElapsed(){ return m_elapsed; }

void Game::RestartClock(){ m_elapsed += m_clock.restart(); }

