#include <SFML/Graphics.hpp>
#include <Windows.h>

int height = 800, width = 800,
	h = 50, w = 50;	

const int scale = 50;


struct Block
{
	int y = 0;
	int x = 0;
	float timer = 0;

	sf::Color color;
	sf::Sprite sprite;

} a[3];

sf::Sprite createSprite(std::string texturePath, sf::Color color) {
	sf::Sprite sprite;
	sf::Texture texture;

	texture.loadFromFile(texturePath);
	sprite.setTexture(texture);
	sprite.setColor(color);

	return sprite;
}

sf::Color generateColor() {
	int r = 200 + rand() % 255;
	int g = 200 + rand() % 255;
	int b = 200 + rand() % 255;

	sf::Color color(r, g, b);

	return color;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(height, width), "Dodger");

	srand(time(NULL));

	float delay = 0.3;
	sf::Clock clock;


	for (int i = 0; i < 3; i++) {
		a[i].color = generateColor();

		a[i].x = (1 + rand() % 15);
		a[i].y = -(1 + rand() % 15);
	}

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();

		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(200, 220, 230));
		for (int i = 0; i < 3; i++) {

			a[i].timer += time;

			a[i].sprite = createSprite("square.png", a[i].color);
			a[i].sprite.setPosition(a[i].x * scale, a[i].y * scale);
			
			if (a[i].y * scale >= height) {
				a[i].y = -(1 + rand() % 15);
			}
			if (a[i].y == -1) {
				a[i].x = (1 + rand() % 15);
				a[i].color = generateColor();
			}

			if (a[i].timer > delay)
			{
				a[i].y += 1;
				a[i].timer = 0;
			}

			window.draw(a[i].sprite);
		}
		
		window.display();
	}

	return 0;
}
