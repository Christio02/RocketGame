#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <vector>

class Background
{
public:
    Background();
    void draw(sf::RenderWindow& window, sf::Vector2f camera_pos) const;

private:
    struct Cloud {
        std::vector<sf::CircleShape> puffs;

    };

    std::vector<sf::CircleShape>    m_stars;
    std::vector<Cloud>    m_clouds;
    sf::RectangleShape              m_ground;
    sf::RectangleShape              m_ground_strip;   // darker ground
    std::vector<sf::RectangleShape> m_grass_blades;
    sf::RectangleShape              m_sky;
    sf::RectangleShape              m_sky_horizon;    // lighter glow


    // fraction of camera movement each layer inherits (0 = fixed, 1 = world)
    static constexpr float STAR_PARALLAX  = 0.05f;
    static constexpr float CLOUD_PARALLAX = 0.30f;
};
