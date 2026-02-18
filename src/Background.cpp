#include <Background.hpp>
#include <random>

Background::Background()
{
    std::mt19937 gen(42);

    // --- Star layer ---
    {
        std::uniform_real_distribution<float> dx(-4000.f, 4000.f);
        std::uniform_real_distribution<float> dy(-4000.f, 4000.f);
        std::uniform_real_distribution<float> db(150.f, 255.f);
        std::uniform_real_distribution<float> dr(0.5f,   2.0f);

        for (int i = 0; i < 400; ++i)
        {
            float r = dr(gen);
            sf::CircleShape star(r);
            star.setOrigin({r, r});
            star.setPosition({dx(gen), dy(gen)});
            const auto b = static_cast<std::uint8_t>(db(gen));
            star.setFillColor(sf::Color(b, b, b));
            m_stars.push_back(std::move(star));
        }
    }

    // --- Cloud layer ---
    // Positions are in cloud-layer space; with CLOUD_PARALLAX = 0.3 this
    // covers the gameplay altitude range (rocket y: 0 → 600).
    {
        std::uniform_real_distribution<float> dx(-2000.f, 2000.f);
        std::uniform_real_distribution<float> dy(-300.f,  150.f);
        std::uniform_real_distribution<float> dr(20.f,    55.f);
        std::uniform_real_distribution<float> dsx(2.5f,   4.5f);

        for (int i = 0; i < 60; ++i)
        {
            float r = dr(gen);
            sf::CircleShape cloud(r);
            cloud.setOrigin({r, r});
            cloud.setPosition({dx(gen), dy(gen)});
            cloud.setScale({dsx(gen), 0.5f});
            cloud.setFillColor(sf::Color(220, 230, 255, 190));
            m_clouds.push_back(std::move(cloud));
        }
    }

    // --- Ground layer (world space, parallax = 1.0) ---
    m_ground.setSize({8000.f, 400.f});
    m_ground.setPosition({-4000.f, 600.f});
    m_ground.setFillColor(sf::Color(34, 139, 34));
}

void Background::draw(sf::RenderWindow& window, sf::Vector2f camera_pos) const
{
    const sf::View default_view = window.getDefaultView();

    // Stars — slowest
    sf::View star_view = default_view;
    star_view.setCenter(camera_pos * STAR_PARALLAX);
    window.setView(star_view);
    for (const auto& star : m_stars)
        window.draw(star);

    // Clouds — medium
    sf::View cloud_view = default_view;
    cloud_view.setCenter(camera_pos * CLOUD_PARALLAX);
    window.setView(cloud_view);
    for (const auto& cloud : m_clouds)
        window.draw(cloud);

    // Ground — fastest (world speed); drawn in world coordinates
    sf::View world_view = default_view;
    world_view.setCenter(camera_pos);
    window.setView(world_view);
    window.draw(m_ground);
}
