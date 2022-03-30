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
#include <TGUI/Gui.hpp>
#include <TGUI/Widgets/ChildWindow.hpp>
#include <TGUI/Widgets/Canvas.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Signal.hpp>

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

void sliderValueChanged(float value)
{
	std::cout << "Value is: " << value << std::endl;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Filterki");
	tgui::Gui gui(window);

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


	//sf::RenderWindow window(sf::VideoMode(sprite.getTexture()->getSize().x, sprite.getTexture()->getSize().y), "SFML works!");
	/*sf::RenderWindow window(sf::VideoMode(1920, 1080), "Filterki");

	tgui::Gui gui(window);*/

	const auto pathLayout = GetPathData() / "layout" / "form.txt";
	gui.loadWidgetsFromFile(pathLayout.string());
	auto childWindow = gui.get<tgui::ChildWindow>("ChildWindow1");
	const auto size = childWindow->getSize();
	tgui::Canvas::Ptr canvas = tgui::Canvas::create();
	canvas->setSize({ texWidth, texHeight });
	canvas->clear();
	canvas->draw(sprite, &shader);
	canvas->display();
	canvas->setPosition((size.x / 2) - canvas->getSize().x / 2.f, (size.y / 2) - canvas->getSize().y / 2.f);
	childWindow->add(canvas);
	childWindow->getRenderer()->setBackgroundColor(sf::Color{ 88, 88, 88, 88 });
	//childWindow->getRenderer()->setTitleBarHeight(0.0f);

	auto slider1 = gui.get<tgui::Slider>("Slider1");
	slider1->connect("ValueChanged", [&childWindow, &canvas, &shader, &sprite](float val) {
		const auto radius = static_cast<int>(val);
		constexpr auto sigma = 5.5;
		const auto kernelRowSize = (1 + 2 * radius);
		const auto kernelSize = kernelRowSize * kernelRowSize;
		const auto kernel = generateKernel(sigma, radius);
		//shader.setUniformArray("kernel", arr, 9);
		const float* p = &kernel[0];

		canvas->clear();
		shader.setUniformArray("kernel", p, kernelSize);
		shader.setUniform("radius", radius);
		canvas->draw(sprite, &shader);
		canvas->display();
		});

	auto val = 0.0f;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			gui.handleEvent(event);
		}

		// Pass the event to all the widgets.
		gui.handleEvent(event);

		window.clear(sf::Color{ 32, 32, 32, 255 });
		gui.draw();

		window.display();
	}

	return 0;
}

