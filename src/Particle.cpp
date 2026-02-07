//
// Created by chris on 07.02.2026.
//
#include <Particle.hpp>

Particle::Particle(sf::Vector2f init_position, sf::Vector2f init_veloctiy) : position(init_position),
                                                                             velocity(init_veloctiy)
{
    time_to_live = 0.5f;
    shape.setRadius(2.f);
    shape.setFillColor(sf::Color(255, 165, 0)); // RGB for orange
}

bool Particle::isDead()
{
    if (position.y >= 600 || time_to_live <= 0)
    {
        return true;
    }
    return false;
}

void Particle::update(const float dt)
{
    time_to_live -= dt;
    velocity = velocity + sf::Vector2f({0, 100}) * dt;
    position = position + velocity * dt;
    shape.setPosition(position);

    const float alpha = (time_to_live / 0.5f) * 255;


    sf::Color currentColor = shape.getFillColor();
    currentColor.a = static_cast<unsigned char>(alpha);
    shape.setFillColor(currentColor);
}


void Particle::draw(sf::RenderWindow& window) const
{
    window.draw(shape);
}
