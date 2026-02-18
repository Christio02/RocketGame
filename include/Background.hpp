#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Background
{
public:
    Background();
    void draw(sf::RenderWindow& window, sf::Vector2f camera_pos) const;

private:
    std::vector<sf::CircleShape>    m_stars;
    std::vector<sf::CircleShape>    m_clouds;
    sf::RectangleShape              m_ground;

    // Fraction of camera movement each layer inherits (0 = fixed, 1 = world)
    static constexpr float STAR_PARALLAX  = 0.05f;
    static constexpr float CLOUD_PARALLAX = 0.30f;
};
