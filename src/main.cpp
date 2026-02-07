#include <SFML/Graphics.hpp>
#include <Rocket.hpp>

int main()
{
	unsigned int width = 800;
	unsigned int height = 600;
	sf::RenderWindow window(sf::VideoMode({width, height}), "SFML works!");

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	sf::Vector2i position(desktop.size.x / 2 - width / 2, desktop.size.y / 2 - height / 2);

	window.setPosition(position);

	sf::Clock clock;

	Rocket myRocket({400.0f, 20.f}, {0, 0}, {0, 0});

	while (window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		window.clear();
		myRocket.update(dt);
		myRocket.draw(window);
		window.display();
	}
}
