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
	std::uniform_real_distribution<float> randPosition(0.0, 400.0f);
	std::uniform_real_distribution<float> randRotation(0.0f, 360.0f);
	std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
	std::uniform_real_distribution<float> randGravity(-1.0f, 1.0f);

    std::uniform_real_distribution<float> randVelocity(-5.0, 5.0f);
    std::uniform_real_distribution<float> randAcceleration(-2.0f, 2.0f);


    for (int _ = 0; _ < 100; ++_) 
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
                //sf::Vector2f(randPosition(generator), randPosition(generator)),
                sf::Vector2f(400, 300),
                0.0f, //randRotation(generator),
                sf::Vector2f(randScale(generator), randScale(generator))
            });

        gCoordinator.AddComponent(
            entity, 
            Rendering{}); 
    }


    if (!m_font.loadFromFile("assets/fonts/Quicksand-Bold.otf")) {
        std::cerr << "Error loading font" << std::endl;
    }


    m_fps_text.setFont(m_font); // Set the font
    m_fps_text.setString(std::to_string(m_fps));
    m_fps_text.setCharacterSize(64); // Set the character size in pixels
    m_fps_text.setFillColor(sf::Color::White); // Set the text color
    m_fps_text.setPosition(400.f, 300.f); // Set the position


}

Game::~Game() {}

void Game::Update() {
    /*
    Rendering and Logic Update Desynchronization:

    In many game engines, rendering and game logic (physics, AI, etc.) are decoupled and operate independently. 
    The game logic typically updates at a fixed time step (e.g., every 0.01 seconds), 
    while rendering can happen as fast as possible, often driven by the frame rate (e.g., 60 frames per second).

    For example.

    Window is updated as fast as possible

    The physics system is updated at fixed time interval, in this instance m_timePerFrame which is just 1/60.
    for every game loop we work out the time that has passed since the last one (m_timeSinceLastUpdate)

    lets say it is 0.001
    we would update our window but not our physics system as it should only update every 1/60 (0.1666...)
    so we pass over it

    Consider that a frame may sometimes take three times the average delta time. This
    can lead to severe mistakes in the game logic, for example, when a player moves
    three times the distance and passes through a wall he would normally collide with.
    
    we always give the same delta time to the update function, no matter what happens for our physics system.
    This ensures that the example above does not happen
    
    */

    // Update the window (assuming m_window.Update() handles rendering and input)
    m_window.Update();
    //m_physicsSystem->Update(0.1);
          
    // Accumulate elapsed time
    m_timeSinceLastUpdate += m_clock.restart();

    // Update physics in fixed steps
    while (m_timeSinceLastUpdate >= m_timePerFrame) {
        m_physicsSystem->Update(m_timePerFrame.asSeconds()); 
        m_timeSinceLastUpdate -= m_timePerFrame;
    }
}



void Game::HandleInput(){
  
}

void Game::Render(){
    m_window.BeginDraw();

    //m_window.Draw(m_fps_text);
    m_renderSystem->Render(m_window.GetRenderWindow());
    

    m_window.EndDraw();
}

void Game::Run(){
    while(!m_window.IsDone()){
        HandleInput();
        Update();
        Render();
    }

}


Window* Game::GetWindow(){
    return &m_window;
}

sf::Time Game::GetElapsed(){ return m_elapsed; }

void Game::RestartClock(){ m_elapsed += m_clock.restart(); }

