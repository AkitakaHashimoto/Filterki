#define _USE_MATH_DEFINES
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <config.h>
#include <array>
#include <vector>
#include <cmath>

std::vector<float> generateKernel(float sigma, int radius)
{
	std::vector<float> kernel{};
	auto sum = 0.0F;

	for (auto row = -radius; row <= radius; row++)
	{
		for (auto col = -radius; col <= radius; col++)
		{
			auto gaussianVal = static_cast<float>((1.0 / (2 * M_PI * sigma * sigma)) * exp(-(row * row + col * col) / (2 * sigma * sigma)));
			sum += gaussianVal;
			kernel.push_back(gaussianVal);
		}
	}

	const auto scaleFactor = 1.0F / sum;

	for (auto& k : kernel)
	{
		k *= scaleFactor;
	}

	return kernel;
}

int main()
{
	sf::Texture tex{};
	const auto pathImage = GetPathData() / "images" / "rumble.jpg";
	tex.loadFromFile(pathImage.string());
	sf::Sprite sprite{};
	sprite.setTexture(tex);

	sf::Shader shader{};
	const auto texWidth{ static_cast<float>(sprite.getTexture()->getSize().x) };
	const auto texHeight{ static_cast<float>(sprite.getTexture()->getSize().y) };

	const auto pathShaderFrag = GetPathData() / "shaders" / "blurGaussian2D.frag";

	shader.loadFromFile(pathShaderFrag.string(), sf::Shader::Fragment);
	shader.setUniform("texture", sf::Shader::CurrentTexture);
	shader.setUniform("width", texWidth);
	shader.setUniform("height", texHeight);
	constexpr auto radius = 5;
	constexpr auto sigma = 5.5;
	constexpr auto kernelRowSize = (1 + 2 * radius);
	constexpr auto kernelSize = kernelRowSize * kernelRowSize;
	const auto kernel = generateKernel(sigma, radius);
	//shader.setUniformArray("kernel", arr, 9);
	const float* p = &kernel[0];
	shader.setUniformArray("kernel", p, kernelSize);
	shader.setUniform("radius", radius);


	sf::RenderWindow window(sf::VideoMode(sprite.getTexture()->getSize().x, sprite.getTexture()->getSize().y), "SFML works!");

	window.clear();
	window.draw(sprite, &shader);
	window.display();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	return 0;
}

