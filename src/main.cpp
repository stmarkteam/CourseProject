#include <SFML/Graphics.hpp>

using namespace sf;

int main(){
	RenderWindow game(VideoMode(600, 400), "Game");
	
	Texture t;
	t.loadFromFile("fang.png");

	Sprite s;
	s.setTexture(t);
	s.setTextureRect(IntRect(0,244,40,50));
	s.setPosition(50,100);

	while (game.isOpen()){
		Event event;
		while(game.pollEvent(event)){
			if (event.type == Event::Closed)
				game.close();
		}

		game.clear(Color::White);
		game.draw(s);
		game.display();
	}
	return 0;
}

