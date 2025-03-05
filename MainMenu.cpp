#include "MainMenu.h"
#include "GamePlay.h"

#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Tools>& Tools)
    : TOOLS(Tools), PlaySelected(true),
    PlayPressed(false), ExitSelected(false),
    ExitPressed(false)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
    TOOLS->asset->AddFont(MAIN_FONT, "assetes/Font/ka1.ttf");

    // Title
    GameTitle.setFont(TOOLS->asset->GetFont(MAIN_FONT));
    GameTitle.setString("Snake Game");
    GameTitle.setCharacterSize(100);
    GameTitle.setOrigin(GameTitle.getLocalBounds().width / 2,GameTitle.getLocalBounds().height / 2);

    GameTitle.setPosition(TOOLS->window->getSize().x / 2,TOOLS->window->getSize().y / 2 - 150.f);

    // Play Button
    PlayButton.setFont(TOOLS->asset->GetFont(MAIN_FONT));
    PlayButton.setString("PLAY");
    PlayButton.setOrigin(PlayButton.getLocalBounds().width / 2,
        PlayButton.getLocalBounds().height / 2);
    PlayButton.setPosition(TOOLS->window->getSize().x / 2.1,
        TOOLS->window->getSize().y / 2 - 20.f);
    PlayButton.setCharacterSize(50);

    // Exit Button
    ExitButton.setFont(TOOLS->asset->GetFont(MAIN_FONT));
    ExitButton.setString("Exit");
    ExitButton.setOrigin(ExitButton.getLocalBounds().width / 2,ExitButton.getLocalBounds().height / 2);
    ExitButton.setPosition(TOOLS->window->getSize().x / 2.1,TOOLS->window->getSize().y / 2 + 75.f);
    ExitButton.setCharacterSize(50);
}

void MainMenu::ProcessInput()
{
    sf::Event event;
    while (TOOLS->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            TOOLS->states->PopAll();
            ;
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
            {
                if (!PlaySelected)
                {
                    PlaySelected = true;
                    ExitSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                if (!ExitSelected)
                {
                    PlaySelected = false;
                    ExitSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                PlayPressed = false;
                ExitPressed = false;

                if (PlaySelected)
                {
                    PlayPressed = true;
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
void MainMenu::Update(const sf::Time& deltaTime)
{
    if (PlaySelected)
    {
        PlayButton.setFillColor(sf::Color::Green);
        ExitButton.setFillColor(sf::Color::White);
    }
    else
    {
        ExitButton.setFillColor(sf::Color::Red);
        PlayButton.setFillColor(sf::Color::White);
    }

    if (PlayPressed)
    {
        TOOLS->states->Add(std::make_unique<GamePlay>(TOOLS), true);
    }
    else if (ExitPressed)
    {
        TOOLS->states->PopAll();
    }
}
//render
void MainMenu::Render()
{
    TOOLS->window->clear(sf::Color::Black);
    TOOLS->window->draw(GameTitle);
    TOOLS->window->draw(PlayButton);
    TOOLS->window->draw(ExitButton);
    TOOLS->window->display();
}