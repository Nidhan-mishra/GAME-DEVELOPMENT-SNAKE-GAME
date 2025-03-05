#include "PauseGame.h"

#include <SFML/Window/Event.hpp>

PauseGame::PauseGame(std::shared_ptr<Tools>& Tools)
    : TOOLS(Tools)
{
}

PauseGame::~PauseGame()
{
}

void PauseGame::Init()
{
    // Title
    PausedText.setFont(TOOLS->asset->GetFont(MAIN_FONT));
    PausedText.setString("PAUSED");
    PausedText.setOrigin(PausedText.getLocalBounds().width / 2,PausedText.getLocalBounds().height / 2);
    PausedText.setPosition(TOOLS->window->getSize().x / 2.1,TOOLS->window->getSize().y / 2);

}

void PauseGame::ProcessInput()
{
    sf::Event event;
    while (TOOLS->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            TOOLS->states->PopAll();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                TOOLS->states->PopCurrent();
                break;
            }
            default:
            {
                break;
            }
            }
        }
    }
}

void PauseGame::Update(const sf::Time& deltaTime)
{
}

void PauseGame::Render()
{
    TOOLS->window->draw(PausedText);
    TOOLS->window->display();
}