#include <SFML/Graphics.hpp>

using namespace sf;

int main(){
	RenderWindow game(VideoMode(600, 400), "Game");
	
	Texture t;
	t.loadFromFile("fang.png");
	float currentFrame = 0;
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
		if (Keyboard::isKeyPressed(Keyboard::Left)){
			s.move(-0.05,0);
			currentFrame += 0.003;
	  		if (currentFrame > 6) currentFrame -=6 ;
			s.setTextureRect(IntRect(40*int(currentFrame)+40,244,-40,50));
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)){
			s.move(0.05,0);
			currentFrame += 0.003;
	  		if (currentFrame > 6) currentFrame -=6 ;
			s.setTextureRect(IntRect(40*int(currentFrame),244,40,50));
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) s.move(0,-0.1);
		if (Keyboard::isKeyPressed(Keyboard::Down)) s.move(0,0.1);
		game.clear(Color::White);
		game.draw(s);
		game.display();
	}
	return 0;
}

