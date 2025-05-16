#include "Engine.h"
#include "Particle.h"
using namespace sf;
using namespace st;

Engine::Engine()
{
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    m_Window.create(VideoMode(resolution.x, resolution.y), "Particles!", Style::Fullscreen);
}

void Engine::run()
{
    Clock clock;

    //Time dt= clock.restart();
    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete. Starting engine..." << endl;

    while(m_Window.isOpen())
    {
        Time dt= clock.restart();
        m_GameTimeTotal += dt;

        float dtAsSeconds = dt.dtAsSeconds();
        
        input();
        update(dtAsSeconds);
        draw();
    }
}

void Engine::input()
{
    Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == Event::KeyPressed)
        {
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                m_Window.close();
            }
        }
        if (event.type == Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == Mouse::Left)//create loop to construct 5 particles
            {
                cout << "Left Mouse Button was pressed" << endl;
                for (int i = 0; i < 5; i++)
                {
                    int numPoints = (rand() % 26) + 25;
                    Particle p(m_Window, numPoints, )
                }
            }
        }
    }
}

void Engine::update(float dtAsSeconds)
{
    for (int i = 0; i < m_particles.size();)
    {
        if (m_particles[i].getTTL() > 0.0) // if getttl() > 0.0
        {
            m_particles[i].update(dtAsSeconds);
            i++;
        }
        else // erase the element its pointing to
        {
            m_particles.erase(m_particles.begin() + i);
            //i--;
        }

    }
}

void Engine::draw()
{
    m_Window.clear();
    ///loop through each Particle in m_particles
    for (int i = 0; i < m_particles.size(); i++)
    {
        m_Window.draw(m_particles[i]);
    }
    m_Window.display();
}