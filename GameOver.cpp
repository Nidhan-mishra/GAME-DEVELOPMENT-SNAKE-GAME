#include "GameOver.h"
#include "GamePlay.h"

#include <SFML/Window/Event.hpp>

GameOver::GameOver(std::shared_ptr<Tools>& Tools)
    : TOOLS(Tools), RetrySelected(true),
    RetryPressed(false), ExitSelected(false),
    ExitPressed(false)
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
    // Title
    GameOverTitle.setFont(TOOLS->asset->GetFont(MAIN_FONT));
    GameOverTitle.setString("Game Over");
    GameOverTitle.setOrigin(GameOverTitle.getLocalBounds().width / 2,GameOverTitle.getLocalBounds().height / 2);
    GameOverTitle.setPosition(TOOLS->window->getSize().x / 2,TOOLS->window->getSize().y / 2 - 150.f);

    // Play Button
    Retry.setFont(TOOLS->asset->GetFont(MAIN_FONT));
    Retry.setString("RETRY");
    Retry.setOrigin(Retry.getLocalBounds().width / 2,Retry.getLocalBounds().height / 2);
    Retry.setPosition(TOOLS->window->getSize().x / 2.1,TOOLS->window->getSize().y / 2 - 55.f);
    Retry.setCharacterSize(50);

    // Exit Button
    Exit.setFont(TOOLS-> asset->GetFont(MAIN_FONT));
    Exit.setString("EXIT");
    Exit.setOrigin(Exit.getLocalBounds().width / 2, Exit.getLocalBounds().height / 2);
    Exit.setPosition(TOOLS->window->getSize().x / 2.1,TOOLS->window->getSize().y / 2 + 55.f);
    Exit.setCharacterSize(50);
}

void GameOver::ProcessInput()
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
            case sf::Keyboard::Up:
            {
                if (!RetrySelected)
                {
                    RetrySelected = true;
                    ExitSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                if (!ExitSelected)
                {
                    RetrySelected = false;
                    ExitSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                RetryPressed = false;
                ExitPressed = false;

                if (RetrySelected)
                {
                    RetryPressed = true;
                }
                else
                {
                    ExitPressed = true;
                }

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
//update
void GameOver::Update(const sf::Time& deltaTime)
{
    if (RetrySelected)
    {
        Retry.setFillColor(sf::Color::Green);
        Exit.setFillColor(sf::Color::White);
    }
    else
    {
        Exit.setFillColor(sf::Color::Red);
        Retry.setFillColor(sf::Color::White);
    }

    if (RetryPressed)
    {
        TOOLS->states->Add(std::make_unique<GamePlay>(TOOLS), true);
    }
    else if (ExitPressed)
    {
        TOOLS->states->PopAll();
    }
}
//draw
void GameOver::Render()
{
    TOOLS->window->clear(sf::Color::Black);
    TOOLS->window->draw(GameOverTitle);
    TOOLS->window->draw(Retry);
    TOOLS->window->draw(Exit);
    TOOLS->window->display();
}