#pragma once

#include <memory>
#include <array>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
//#include <SFML/Audio.hpp>
#include "Game.h"
#include "State.h"
#include "Snake.h"

//This is the Gameplay state in which the game logic is made
class GamePlay : public State
{
private:
    std::shared_ptr<Tools> TOOLS;
    sf::Sprite m_grass;
    sf::Sprite m_food;
    std::array<sf::Sprite, 4> m_walls;
    Snake m_snake;

    sf::Text m_scoreText;
    int m_score;

    sf::Vector2f m_snakeDirection;
    sf::Time m_elapsedTime;

    bool m_isPaused;

    //sf::SoundBuffer buf1; //sound buffer
    //sf::Sound collision;

public:
    GamePlay(std::shared_ptr<Tools>& Tools);
    ~GamePlay();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Render() override;
    void Pause() override;
    void Start() override;


};
