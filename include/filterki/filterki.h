#define _USE_MATH_DEFINES
#include <string>
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <cmath>
#include <TGUI/Widgets/ChildWindow.hpp>
#include <TGUI/Widgets/Canvas.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Signal.hpp>

class Filterki
{
public:
	Filterki(sf::RenderWindow& renderWindow);
	void handleEvent(const sf::Event& event);
	void draw();

private:
	std::vector<float> generateKernel(float sigma, int radius) const;

	void loadImage();
	void loadShader();
	void loadGUI();

	sf::Shader shaderBlur{};
	sf::Shader shaderEdge{};
	tgui::Gui gui{};
	sf::Texture tex{};
	sf::Sprite sprite{};
};





