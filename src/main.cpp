#include <SFML/Graphics.hpp>
#include <Rocket.hpp>

int main()
{
	sf::RenderWindow window( sf::VideoMode( { 200, 200 } ), "SFML works!" );

	sf::Clock clock;

	Rocket myRocket({100.0f, 20.f}, {0, 0}, {0, 0});

	while ( window.isOpen() )
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		window.clear();
		myRocket.update(dt);
		myRocket.draw(window);
		window.display();


	}
}
