#include "Game.h"
#include "MainMenu.h"

Game::Game() : TOOLS(std::make_shared<Tools>())
{
    TOOLS->window->create(sf::VideoMode(1280, 720), "Snake Game", sf::Style::Close);
    TOOLS->states->Add(std::make_unique<MainMenu>(TOOLS));
}

Game::~Game()
{
}

void Game::Run()
{
  /*  sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);*/

    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (TOOLS->window->isOpen())
    {
        timeSinceLastFrame += clock.restart();

        while (timeSinceLastFrame > TIME_PER_FRAME)
        {
            timeSinceLastFrame -= TIME_PER_FRAME;

            TOOLS->states->ProcessStateChange();

            if (!TOOLS->states->IsEmpty())
            {
                TOOLS->states->GetCurrent()->ProcessInput();
                TOOLS->states->GetCurrent()->Update(TIME_PER_FRAME);
                TOOLS->states->GetCurrent()->Render();
            }
            else
            {
                TOOLS->window->close();
            }
        }
    }
}
