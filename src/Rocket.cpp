#include <Rocket.hpp>
#include <Game.hpp>

Rocket::Rocket(sf::Vector2f m_init_pos, sf::Vector2f m_init_velocity, sf::Vector2f m_init_thrust)
    : m_position(m_init_pos), m_velocity(m_init_velocity), m_thrust(m_init_thrust)
{
    m_visual.setFillColor(sf::Color::Blue);
    m_visual.setRadius(10.f);
    m_visual.setOrigin({10.f, 10.f});

}

void Rocket::update(const float dt)
{
    sf::Vector2f netForce = m_mass * sf::Vector2f(0, Game::gravity);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        const sf::Vector2f thrust_y = {0, -m_engineForce};

        netForce += thrust_y;

    }

    const sf::Vector2f rocket_acc = netForce  / m_mass; // calculate acceleration

    m_velocity = m_velocity + rocket_acc * dt; // euler integration, get current velocity
    m_position = m_position + m_velocity * dt; // current pos
    m_visual.setPosition(m_position);

    if (m_position.y >= 200)
    {
        m_position.y = 200;
        m_velocity = {0.f, 0.f};
    }



}

void Rocket::draw(sf::RenderWindow& window)
{
    window.draw(m_visual);
}
