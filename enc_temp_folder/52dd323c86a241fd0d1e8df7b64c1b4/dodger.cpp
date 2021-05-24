#include <SFML/Graphics.hpp>
#include <Windows.h>

int height = 800, width = 800,
	h = 50, w = 50,
	dir = 0;	

const int scale = 50;


struct Block
{
	int y = 0;
	int x = 0;
	float timer = 0;

	sf::Color color;
	sf::Sprite sprite;

} block[3], player;

sf::Sprite createSprite(std::string texturePath, sf::Color color) {
	sf::Sprite sprite;
	sf::Texture texture;

	texture.loadFromFile(texturePath);
	sprite.setTexture(texture);
	sprite.setColor(color);

	return sprite;
}

sf::Color generateColor() {
	int r = 0;
	int g = 0 + rand() % 100;
	int b = 0 + rand() % 100;
	int alfa = 50;

	sf::Color color(r, g, b, alfa);

	return color;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(height, width), "Dodger");

	srand(time(NULL));

	float delay = 0.3;
	sf::Clock clock;

	player.color = sf::Color(0, 0, 0);
	player.x = width / scale / 2;
	player.y = height / scale - 1;

	for (int i = 0; i < 3; i++) {
		block[i].color = generateColor();

		block[i].x = (1 + rand() % 15);
		block[i].y = -(1 + rand() % 15);
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

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Right) dir = 1;
				else if (event.key.code == sf::Keyboard::Left) dir = -1;
				player.x += dir;
			}
		}

		window.clear(sf::Color(200, 220, 230));

		player.sprite = createSprite("square.png", player.color);

		if (player.x * scale >= width) player.x = width / scale - 1;
		else if (player.x * scale <= 0) player.x = 0;
		
		player.sprite.setPosition(player.x * scale, player.y * scale);
		

		for (int i = 0; i < 3; i++) {

			block[i].timer += time;

			block[i].sprite = createSprite("square.png", block[i].color);
			block[i].sprite.setPosition(block[i].x * scale, block[i].y * scale);
			
			if (block[i].y * scale >= height) {
				block[i].y = -(1 + rand() % 15);
			}
			if (block[i].y == -1) {
				block[i].x = (1 + rand() % 15);
				block[i].color = generateColor();
			}

			if (block[i].timer > delay)
			{
				block[i].y += 1;
				block[i].timer = 0;
			}

			window.draw(block[i].sprite);
			window.draw(player.sprite);
		}
		

		



		window.display();
	}

	return 0;
}
