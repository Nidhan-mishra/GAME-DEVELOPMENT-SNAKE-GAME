#pragma once
#include "Assets.h"
#include "StateComp.h"

enum AssetID
{
    MAIN_FONT = 0,
    GRASS,
    FOOD,
    WALL,
    SNAKE
};

struct Tools
{
    std::unique_ptr<Assets> asset;
    std::unique_ptr<StateComp> states;
    std::unique_ptr<sf::RenderWindow> window;

    Tools()
    {
        asset = std::make_unique<Assets>();
        states = std::make_unique<StateComp>();
        window = std::make_unique<sf::RenderWindow>();
    }
};

class Game
{
public:
    Game();
    ~Game();

    void Run();

private:
    std::shared_ptr<Tools> TOOLS;
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
};

