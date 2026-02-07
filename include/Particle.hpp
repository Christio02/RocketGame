

#pragma once
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

class Particle
{
public:
    Particle(sf::Vector2f init_position, sf::Vector2f init_velocity);

    void update(float dt);
    void draw(sf::RenderWindow& window) const;
    bool isDead();

private :
    sf::Vector2f position;
    sf::Vector2f velocity;
    float time_to_live;
    sf::CircleShape shape;
};


