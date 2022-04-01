#include <SFML/Graphics.hpp>
#include <filterki/filterki.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Filterki");
	Filterki filterki{ window };

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			filterki.handleEvent(event);
		}

		// Pass the event to all the widgets.
		filterki.handleEvent(event);

		window.clear(sf::Color{ 32, 32, 32, 255 });
		filterki.draw();
		window.display();
	}

	return 0;
}

