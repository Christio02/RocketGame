#include <SFML/Graphics.hpp>
#include <Rocket.hpp>
#include <Background.hpp>

int main()
{
	unsigned int width = 800;
	unsigned int height = 600;
	sf::RenderWindow window(sf::VideoMode({width, height}), "SFML works!");
	sf::View camera = window.getDefaultView();
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	sf::Vector2i position(desktop.size.x / 2 - width / 2, desktop.size.y / 2 - height / 2);

	window.setPosition(position);

	sf::Clock clock;

	Rocket myRocket({400.0f, 20.f}, {0, 0}, {0, 0});
	Background background;

	while (window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		window.clear(sf::Color(10, 10, 30));
		myRocket.update(dt);
		camera.setCenter(myRocket.getPosition());
		background.draw(window, myRocket.getPosition());
		window.setView(camera);
		myRocket.draw(window);
		window.display();
	}
}
