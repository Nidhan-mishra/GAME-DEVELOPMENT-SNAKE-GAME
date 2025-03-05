#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "Game.h"

class PauseGame : public State
{

private:
    std::shared_ptr<Tools> TOOLS;
    sf::Text PausedText;

public:
    PauseGame(std::shared_ptr<Tools>& Tools);
    ~PauseGame();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Render() override;

};
