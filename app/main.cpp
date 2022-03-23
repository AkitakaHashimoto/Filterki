#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <config.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
	sf::Texture tex{};
	const auto path = GetPathData() + "/Rumble.jpg";
	tex.loadFromFile(path);
	sf::Sprite sprite{};
	sprite.setTexture(tex);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}

