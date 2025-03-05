#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "Game.h"

//This is the Gameover class that gets triggered when the game is over 
class GameOver : public State
{
private:
    std::shared_ptr<Tools> TOOLS;
    sf::Text GameOverTitle;
    sf::Text Retry;
    sf::Text Exit;

    bool RetrySelected;
    bool RetryPressed;

    bool ExitSelected;
    bool ExitPressed;

public:
    GameOver(std::shared_ptr<Tools>& Tools);
    ~GameOver();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Render() override;

};

