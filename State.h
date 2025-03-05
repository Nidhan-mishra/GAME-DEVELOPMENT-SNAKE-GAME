#pragma once

#include <SFML/System/Time.hpp>
#include <iostream>
//This the States class
class State
{
public:
 State() {};
 virtual ~State() {};

virtual void Init() = 0;
virtual void ProcessInput() = 0;
virtual void Update(const sf::Time& deltaTime) = 0;
virtual void Render() = 0;

//pause and start functions.
 virtual void Pause() {};
 virtual void Start() {};
};


