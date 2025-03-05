#pragma once
#include <memory>
#include <SFML/Graphics/Text.hpp>
#include "State.h"
#include "Game.h"

//this is the main menu class the first class that the plyer interacts with
class MainMenu : public State
{
private:
    std::shared_ptr<Tools> TOOLS;
    sf::Text GameTitle;
    sf::Text PlayButton;
    sf::Text ExitButton;

    bool PlaySelected; //button select
    bool PlayPressed; //button pressed

    bool ExitSelected;//button select
    bool ExitPressed; //button pressed

public:
    MainMenu(std::shared_ptr<Tools>& Tools);
    ~MainMenu();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Render() override;
};

