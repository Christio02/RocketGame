#include <Rocket.hpp>
#include <Game.hpp>
#include <iostream>

Rocket::Rocket(sf::Vector2f m_init_pos, sf::Vector2f m_init_velocity, sf::Vector2f m_init_thrust)
    : m_position(m_init_pos), m_velocity(m_init_velocity), m_thrust(m_init_thrust), m_gen(std::random_device{}()),
      m_dist_x(-25.f, 25.f), m_dist_y(50.f, 100.f), m_sprite(m_texture)


{
    if (!m_texture.loadFromFile("assets/rocket.png"))
    {
        std::cerr << "Error: could not load rocket texture" << std::endl;
    }

    m_sprite.setTexture(m_texture, true);

    const sf::Vector2u textureSize = m_texture.getSize();

    m_sprite.setOrigin({static_cast<float>(textureSize.x) / 2.f, static_cast<float>(textureSize.y) / 2.f});

    m_sprite.setScale({0.1f, 0.1f});
}

void Rocket::update(const float dt)
{
    const float half_height = (m_texture.getSize().y / 2.0f) * m_sprite.getScale().y;

    const float current_total_mass = m_structural_mass + m_fuel_mass;
    sf::Vector2f netForce = current_total_mass * sf::Vector2f(0, Game::gravity);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && m_fuel_mass > 0)
    {
        // burn fuel
        m_fuel_mass -= m_fuel_burn_rate * dt; // mass decreases over timew
        if (m_fuel_mass < 0) m_fuel_mass = 0; // keep positive
        // Thrust force = u * |dm/dt|
        const float thrust_magnitude = m_exhaust_veloctiy * m_fuel_burn_rate;
        const sf::Vector2f thrust_y = {0, -thrust_magnitude};

        netForce += thrust_y;

        for (int i = 0; i < 6; i++)
        {
            float random_x = m_dist_x(m_gen);
            float random_y = m_dist_x(m_gen);


            particles.emplace_back(Particle(sf::Vector2f({m_position.x, m_position.y + half_height * 0.5f}),
                                            sf::Vector2f({random_x, random_y})));
        }
    }

    for (auto it = particles.begin(); it != particles.end();)
    {
        if (it->isDead())
        {
            it = particles.erase(it);
        }
        else
        {
            it->update(dt);
            ++it;
        }
    }

    const sf::Vector2f rocket_acc = netForce / current_total_mass; // calculate acceleration

    m_velocity = m_velocity + rocket_acc * dt; // euler integration, get current velocity
    m_position = m_position + m_velocity * dt; // current pos
    m_sprite.setPosition(m_position);


    if (m_position.y >= 600)
    {
        m_position.y = 600;
        m_velocity = {0.f, 0.f};
    }
}

void Rocket::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);

    for (const Particle& p : particles)
    {
        p.draw(window);
    }
}
