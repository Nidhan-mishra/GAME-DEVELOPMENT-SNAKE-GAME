#pragma once
#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

//This is the assetes class
class Assets
{
private:
    std::map<int, std::unique_ptr<sf::Texture>> textureS;
    std::map<int, std::unique_ptr<sf::Font>>FontS;
 public:
 Assets();
 ~Assets();

 //functions 
void AddTexture(int id, const std::string& FilePath, bool wantRepeated = false); //ADD TEXTURE function
void AddFont(int id, const std::string& filePath); //ADD FONT function

//accesores
 const sf::Texture& GetTexture(int id) const; //get function
 const sf::Font& GetFont(int id) const; //getfunction
};


