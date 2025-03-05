#include "GamePlay.h"
#include "GameOver.h"
#include "PauseGame.h"

#include <SFML/Window/Event.hpp>

#include <stdlib.h>
#include <time.h>

GamePlay::GamePlay(std::shared_ptr<Tools>& Tools)
    : TOOLS(Tools),
    m_score(0),
    m_snakeDirection({ 16.f, 0.f }),
    m_elapsedTime(sf::Time::Zero),
    m_isPaused(false)
{
    srand(time(nullptr));

    /*if (!buf1.loadFromFile("assetes/sound/TAKE.wav"))
    {
        std::cout << "not loaded" << "\n";
    }
    collision.setBuffer(buf1);*/
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
    TOOLS->asset->AddTexture(GRASS, "assetes/textures/GRASS.png", true);
    TOOLS->asset->AddTexture(FOOD, "assetes/textures/FOOD.png");
    TOOLS->asset->AddTexture(WALL, "assetes/textures/WALL.png", true);
    TOOLS->asset->AddTexture(SNAKE, "assetes/textures/SNAKE.png");

    m_grass.setTexture(TOOLS->asset->GetTexture(GRASS));
    m_grass.setTextureRect(TOOLS->window->getViewport(TOOLS->window->getDefaultView()));

    for (auto& wall : m_walls)
    {
        wall.setTexture(TOOLS->asset->GetTexture(WALL));
    }

    m_walls[0].setTextureRect({ 0, 0, (int)TOOLS->window->getSize().x, 16 });
    m_walls[1].setTextureRect({ 0, 0, (int)TOOLS->window->getSize().x, 16 });
    m_walls[1].setPosition(0, TOOLS->window->getSize().y - 16);

    m_walls[2].setTextureRect({ 0, 0, 16, (int)TOOLS->window->getSize().y });
    m_walls[3].setTextureRect({ 0, 0, 16, (int)TOOLS->window->getSize().y });
    m_walls[3].setPosition(TOOLS->window->getSize().x - 16, 0);

    m_food.setTexture(TOOLS->asset->GetTexture(FOOD));
    m_food.setPosition(TOOLS->window->getSize().x / 2, TOOLS->window->getSize().y / 2);

    m_snake.Init(TOOLS->asset->GetTexture(SNAKE));

    m_scoreText.setFont(TOOLS->asset->GetFont(MAIN_FONT));
    m_scoreText.setString("Score : " + std::to_string(m_score));
    m_scoreText.setCharacterSize(15);
}

void GamePlay::ProcessInput()
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
            sf::Vector2f newDirection = m_snakeDirection;
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                newDirection = { 0.f, -16.f };
                break;
            case sf::Keyboard::Down:
                newDirection = { 0.f, 16.f };
                break;
            case sf::Keyboard::Left:
                newDirection = { -16.f, 0.f };
                break;
            case sf::Keyboard::Right:
                newDirection = { 16.f, 0.f };
                break;
            case sf::Keyboard::Escape:
                TOOLS->states->Add(std::make_unique<PauseGame>(TOOLS));
                break;

            default:
                break;
            }

            if (std::abs(m_snakeDirection.x) != std::abs(newDirection.x) ||
                std::abs(m_snakeDirection.y) != std::abs(newDirection.y))
            {
                m_snakeDirection = newDirection;
            }
        }
    }
}

void GamePlay::Update(const sf::Time& deltaTime)
{
    if (!m_isPaused)
    {
        m_elapsedTime += deltaTime;

        if (m_elapsedTime.asSeconds() > 0.1)
        {
            for (auto& wall : m_walls)
            {
                if (m_snake.IsOn(wall))
                {
                    TOOLS->states->Add(std::make_unique<GameOver>(TOOLS), true);
                    break;
                }
            }

            if (m_snake.IsOn(m_food))
            {
                //collision.play();
                m_snake.Grow(m_snakeDirection);

                int x = 0, y = 0;
                x = rand() % 1000,100;
                y = rand() % 600,100;

                m_food.setPosition(x, y);
                m_score += 1;
                m_scoreText.setString("Score : " + std::to_string(m_score));
            }
            else
            {
                m_snake.Move(m_snakeDirection);
            }

            if (m_snake.IsSelfIntersecting())
            {
                TOOLS->states->Add(std::make_unique<GameOver>(TOOLS), true);
            }

            m_elapsedTime = sf::Time::Zero;
        }
    }
}

void GamePlay::Render()
{
    TOOLS->window->clear();
    TOOLS->window->draw(m_grass);

    for (auto& wall : m_walls)
    {
        TOOLS->window->draw(wall);
    }
    TOOLS->window->draw(m_food);
    TOOLS->window->draw(m_snake);
    TOOLS->window->draw(m_scoreText);

    TOOLS->window->display();
}

void GamePlay::Pause()
{
    m_isPaused = true;
}

void GamePlay::Start()
{
    m_isPaused = false;
}