#include <SFML/Graphics.hpp>
#include <filterki/filterki.h>
#include <chrono>
#include <thread>

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
			{
				window.close();
			}

			// Pass the event to all the widgets.
			filterki.handleEvent(event);
		}

		window.clear(sf::Color{ 32, 32, 32, 255 });
		filterki.draw();
		window.display();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return 0;
}

