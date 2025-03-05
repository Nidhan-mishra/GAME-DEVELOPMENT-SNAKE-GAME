#include "Assets.h"
Assets::Assets()
{
}

Assets::~Assets()
{

}

void Assets::AddTexture(int id, const std::string& FilePath, bool wantRepeated)
{
    auto texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile(FilePath))
    {
        texture->setRepeated(wantRepeated);
        textureS[id] = std::move(texture);
    }
}

void Assets::AddFont(int id, const std::string& filePath)
{
    auto font = std::make_unique<sf::Font>();

    if (font->loadFromFile(filePath))
    {
       FontS[id] = std::move(font);
    }
}

const sf::Texture& Assets::GetTexture(int id) const
{
    return *(textureS.at(id).get());
}



const sf::Font& Assets::GetFont(int id) const
{
    return *(FontS.at(id).get());
    
}
