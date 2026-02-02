#pragma once
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>

class Rocket
{
public:
    Rocket(sf::Vector2f m_init_pos = {100.0f, 0.0f}, sf::Vector2f m_init_velocity = {0.0f, 0.0f}, sf::Vector2f m_init_thrust = {0.0f, 0.0f});
    void update(float dt);
    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f  m_position;
    sf::Vector2f m_velocity;
    sf::Vector2f m_acceleration;
    sf::Vector2f m_thrust;

    float m_mass = 10.0f;
    float m_engineForce = 250.0f;

    sf::CircleShape m_visual;
};

