#include <Background.hpp>
#include <random>

Background::Background()
{
    std::mt19937 gen(42);

    // --- Sky gradient (two layered rectangles) ---
    m_sky.setSize({8000.f, 8000.f});
    m_sky.setPosition({-4000.f, -7400.f});
    m_sky.setFillColor(sf::Color(10, 10, 40));       // deep space blue

    m_sky_horizon.setSize({8000.f, 300.f});
    m_sky_horizon.setPosition({-4000.f, 300.f});
    m_sky_horizon.setFillColor(sf::Color(60, 80, 160, 180)); // lighter near horizon

    // --- Stars ---
    {
        std::uniform_real_distribution<float> dx(-4000.f, 4000.f);
        std::uniform_real_distribution<float> dy(-4000.f, 200.f);
        std::uniform_real_distribution<float> db(150.f, 255.f);
        std::uniform_real_distribution<float> dr(0.4f, 2.0f);
        for (int i = 0; i < 500; ++i)
        {
            float r = dr(gen);
            sf::CircleShape star(r);
            star.setOrigin({r, r});
            star.setPosition({dx(gen), dy(gen)});
            const auto b = static_cast<std::uint8_t>(db(gen));
            // slight color tint variation
            star.setFillColor(sf::Color(b, b, static_cast<std::uint8_t>(std::min(255, (int)b + 30))));
            m_stars.push_back(std::move(star));
        }
    }

    // --- Clouds (multi-puff) ---
    {
        std::uniform_real_distribution<float> dx(-2000.f, 2000.f);
        std::uniform_real_distribution<float> dy(-200.f, 100.f);
        std::uniform_real_distribution<float> dr(15.f, 35.f);
        std::uniform_real_distribution<float> d_puffs(3, 6);
        std::uniform_real_distribution<float> d_offset(-30.f, 30.f);

        for (int i = 0; i < 40; ++i)
        {
            Cloud cloud;
            float base_x = dx(gen);
            float base_y = dy(gen);
            float base_r = dr(gen);
            int puff_count = static_cast<int>(d_puffs(gen));

            for (int p = 0; p < puff_count; ++p)
            {
                float r = base_r * (0.6f + 0.5f * (p == 0 ? 1.f : 0.6f));
                sf::CircleShape puff(r);
                puff.setOrigin({r, r});
                float offset_x = p * (base_r * 1.0f) + d_offset(gen) * 0.3f;
                float offset_y = d_offset(gen) * 0.4f;
                puff.setPosition({base_x + offset_x, base_y + offset_y});
                puff.setFillColor(sf::Color(235, 240, 255, 200));
                cloud.puffs.push_back(std::move(puff));
            }
            m_clouds.push_back(std::move(cloud));
        }
    }

    // --- Ground ---
    m_ground.setSize({8000.f, 400.f});
    m_ground.setPosition({-4000.f, 600.f});
    m_ground.setFillColor(sf::Color(34, 120, 34));   // green grass

    m_ground_strip.setSize({8000.f, 18.f});
    m_ground_strip.setPosition({-4000.f, 600.f});
    m_ground_strip.setFillColor(sf::Color(20, 80, 20)); // darker edge line

    // --- Grass blades along the top of the ground ---
    {
        std::uniform_real_distribution<float> dx(-4000.f, 4000.f);
        std::uniform_real_distribution<float> dh(6.f, 18.f);
        std::uniform_real_distribution<float> dw(2.f, 4.f);
        for (int i = 0; i < 600; ++i)
        {
            sf::RectangleShape blade;
            float h = dh(gen);
            blade.setSize({dw(gen), h});
            blade.setPosition({dx(gen), 600.f - h});
            blade.setFillColor(sf::Color(50, 160, 50));
            m_grass_blades.push_back(std::move(blade));
        }
    }
}

void Background::draw(sf::RenderWindow& window, sf::Vector2f camera_pos) const
{
    const sf::View default_view = window.getDefaultView();

    // Sky — fixed background
    sf::View sky_view = default_view;
    sky_view.setCenter(camera_pos * 0.0f);
    window.setView(sky_view);
    window.draw(m_sky);
    window.draw(m_sky_horizon);

    // Stars — slowest parallax
    sf::View star_view = default_view;
    star_view.setCenter(camera_pos * STAR_PARALLAX);
    window.setView(star_view);
    for (const auto& star : m_stars)
        window.draw(star);

    // Clouds — medium parallax
    sf::View cloud_view = default_view;
    cloud_view.setCenter(camera_pos * CLOUD_PARALLAX);
    window.setView(cloud_view);
    for (const auto& cloud : m_clouds)
        for (const auto& puff : cloud.puffs)
            window.draw(puff);

    // Ground — world speed
    sf::View world_view = default_view;
    world_view.setCenter(camera_pos);
    window.setView(world_view);
    window.draw(m_ground);
    for (const auto& blade : m_grass_blades)
        window.draw(blade);
    window.draw(m_ground_strip);
}
