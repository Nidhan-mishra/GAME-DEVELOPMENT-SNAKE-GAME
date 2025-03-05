#include "Snake.h"

Snake::Snake() : Body(std::list<sf::Sprite>(4))
{
    Head = --Body.end();
    Tail = Body.begin();
}

Snake::~Snake()
{
}

void Snake::Init(const sf::Texture& texture)
{
    float x = 16.f;
    for (auto& piece : Body)
    {
        piece.setTexture(texture);
        piece.setPosition({ x, 16.f });
        x += 16.f;
    }
}

void Snake::Move(const sf::Vector2f& direction)
{
    Tail->setPosition(Head->getPosition() + direction);
    Head = Tail;
    ++Tail;

    if (Tail == Body.end())
    {
        Tail = Body.begin();
    }
}

bool Snake::IsOn(const sf::Sprite& other) const
{
    return other.getGlobalBounds().intersects(Head->getGlobalBounds());
}

void Snake::Grow(const sf::Vector2f& direction)
{
    sf::Sprite newPiece;
    newPiece.setTexture(*(Body.begin()->getTexture()));
    newPiece.setPosition(Head->getPosition() + direction);

    Head = Body.insert(++Head, newPiece);
}

bool Snake::IsSelfIntersecting() const
{
    bool flag = false;

    for (auto piece = Body.begin(); piece != Body.end(); ++piece)
    {
        if (Head != piece)
        {
            flag = IsOn(*piece);

            if (flag == true)
            {
                break;
            }
        }
    }

    return flag;
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& piece : Body)
    {
        target.draw(piece);
    }
}
