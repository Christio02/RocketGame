#pragma once
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>

#include "Particle.hpp"
#include <random>


class Rocket
{
public:
    Rocket(sf::Vector2f m_init_pos = {400.0f, 0.0f}, sf::Vector2f m_init_velocity = {0.0f, 0.0f},
           sf::Vector2f m_init_thrust = {0.0f, 0.0f});
    void update(float dt);
    void draw(sf::RenderWindow& window) const;

private:
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    sf::Vector2f m_acceleration;
    sf::Vector2f m_thrust;

    float m_structural_mass = 5.0f;
    float m_fuel_mass = 20.f; // fuel mass
    float m_exhaust_veloctiy = 10000.0f; // u = 2500 m/s
    float m_fuel_burn_rate = 0.5f;

    // generate random position for particles out of engine
    std::mt19937 m_gen;
    std::uniform_real_distribution<float> m_dist_x;
    std::uniform_real_distribution<float> m_dist_y;


    std::vector<Particle> particles;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
};

