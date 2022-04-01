#include <filterki/filterki.h>
#include <config.h>

std::vector<float> Filterki::generateKernel(float sigma, int radius)
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

Filterki::Filterki(sf::RenderWindow& renderWindow)
{
	this->gui.setTarget(renderWindow);

	const auto pathImage = GetPathData() / "images" / "rumble.jpg";
	this->tex.loadFromFile(pathImage.string());
	this->sprite.setTexture(tex);

	const auto texWidth{ static_cast<float>(this->sprite.getTexture()->getSize().x) };
	const auto texHeight{ static_cast<float>(this->sprite.getTexture()->getSize().y) };

	const auto pathShaderFrag = GetPathData() / "shaders" / "blurGaussian2D.frag";

	this->shader.loadFromFile(pathShaderFrag.string(), sf::Shader::Fragment);
	this->shader.setUniform("texture", sf::Shader::CurrentTexture);
	this->shader.setUniform("width", texWidth);
	this->shader.setUniform("height", texHeight);

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
	childWindow->add(canvas, "canvas");
	childWindow->getRenderer()->setBackgroundColor(sf::Color{ 88, 88, 88, 88 });
	//childWindow->getRenderer()->setTitleBarHeight(0.0f);

	auto sliderSigma = this->gui.get<tgui::Slider>("Slider1");
	auto sliderRadius = this->gui.get<tgui::Slider>("Slider2");
	sliderRadius->onValueChange([this](float val) {
		auto window = this->gui.get<tgui::ChildWindow>("ChildWindow1");
		auto canvas = window->get<tgui::Canvas>("canvas");
		auto sliderSigma = this->gui.get<tgui::Slider>("Slider1");
		const auto radius = static_cast<int>(val);
		const auto sigma = sliderSigma->getValue();
		const auto kernelRowSize = (1 + 2 * radius);
		const auto kernelSize = kernelRowSize * kernelRowSize;
		const auto kernel = this->generateKernel(sigma, radius);
		const float* p = &kernel[0];

		canvas->clear();
		this->shader.setUniformArray("kernel", p, kernelSize);
		this->shader.setUniform("radius", radius);
		canvas->draw(sprite, &shader);
		canvas->display();
		});

	sliderSigma->onValueChange([this](float val) {
		auto window = this->gui.get<tgui::ChildWindow>("ChildWindow1");
		auto canvas = window->get<tgui::Canvas>("canvas");
		auto sliderRadius = this->gui.get<tgui::Slider>("Slider2");
		const auto radius = static_cast<int>(sliderRadius->getValue());
		const auto sigma = val;
		const auto kernelRowSize = (1 + 2 * radius);
		const auto kernelSize = kernelRowSize * kernelRowSize;
		const auto kernel = this->generateKernel(sigma, radius);
		const float* p = &kernel[0];

		canvas->clear();
		this->shader.setUniformArray("kernel", p, kernelSize);
		this->shader.setUniform("radius", radius);
		canvas->draw(sprite, &shader);
		canvas->display();
		});
}

void Filterki::handleEvent(const sf::Event& event)
{
	this->gui.handleEvent(event);
}

void Filterki::draw()
{
	this->gui.draw();
}


