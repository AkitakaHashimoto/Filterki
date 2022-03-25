#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <config.h>

int main()
{
	sf::Texture tex{};
	const auto pathImage = GetPathData() / "images" / "irene.png";
	tex.loadFromFile(pathImage.string());
	sf::Sprite sprite{};
	sprite.setTexture(tex);

	sf::Shader shader{};
	const auto texWidth{ static_cast<float>(sprite.getTexture()->getSize().x) };
	const auto texHeight{ static_cast<float>(sprite.getTexture()->getSize().y) };

	const auto pathShaderFrag = GetPathData() / "shaders" / "sobel.frag";
	//const auto pathShaderVert = GetPathData() / "shaders" / "sobel.vert";
	//shader.loadFromFile(pathShaderVert.string(), sf::Shader::Vertex);
	shader.loadFromFile(pathShaderFrag.string(), sf::Shader::Fragment);
	shader.setUniform("texture", sf::Shader::CurrentTexture);
	shader.setUniform("width", texWidth);
	shader.setUniform("height", texHeight);

	sf::RenderWindow window(sf::VideoMode(sprite.getTexture()->getSize().x, sprite.getTexture()->getSize().y), "SFML works!");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(sprite, &shader);
		window.display();
	}

	return 0;
}

