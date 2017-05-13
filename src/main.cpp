#include <SFML/Graphics.hpp>

using namespace sf;

int ground = 304;
const int H = 13;
const int W = 40;

String TileMap[H] = {

"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                                B     B",
"B                                B 0   B",
"B                                B BB  B",
"B                                B     B",
"B                          0  BBBB 0 BBB",
"B0                   0    BBB    B BB  B",
"BBB                 BBB          B0    B",
"B      BB      BB                BB    B",
"B     B  B     BB          0           B",
"B 0  B    B    BB         BB           B",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

}; 
class PLAYER {

public:

float dx,dy;
FloatRect rect;
bool onGround;
Sprite sprite;
float currentFrame;

PLAYER(Texture &image){
	sprite.setTexture(image);
	rect = FloatRect(7*32,9*32,40,50);
	dx=dy=0.1;
	currentFrame = 0;
   }
void update(float time){	
	rect.left += dx * time;
	if (!onGround) dy=dy+0.0005*time;
	rect.top += dy*time;
	onGround=false;
	currentFrame += 0.005*time;
	if (currentFrame > 6) currentFrame -=6 ;
	if (dx>0) sprite.setTextureRect(IntRect(40*int(currentFrame),244,40,50));
	if (dx<0) sprite.setTextureRect(IntRect(40*int(currentFrame)+40,244,-40,50));
	if (rect.top > ground){
		rect.top = ground;
		dy=0;
		onGround = true;
	}
	sprite.setPosition(rect.left, rect.top);
	dx=0;
   }
};

int main(){
	RenderWindow game(VideoMode(600, 400), "Game");
	
	Texture t;
	t.loadFromFile("fang.png");
	float currentFrame = 0;
	PLAYER p(t);
	Clock clock;
	RectangleShape rectangle( Vector2f(32,32));
	while (game.isOpen()){
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time/700;
		Event event;
		while(game.pollEvent(event)){
			if (event.type == Event::Closed)
				game.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))p.dx = -0.1;
		if (Keyboard::isKeyPressed(Keyboard::Right))p.dx = 0.1;
		if (Keyboard::isKeyPressed(Keyboard::Up)) 
		if (p.onGround){
				p.dy=-0.35;
				p.onGround=false;
			}
		p.update(time);
		game.clear(Color::White);
		for (int i=0; i<H; i++)
		for (int j=0; j<W ; j++){ 
			if (TileMap[i][j]=='B') rectangle.setFillColor(Color::Green);
			if (TileMap[i][j]=='0') rectangle.setFillColor(Color::Red);
			if (TileMap[i][j]==' ') continue;
			rectangle.setPosition(j*32,i*32) ; 
		        game.draw(rectangle);
	       	 }
		game.draw(p.sprite);
		game.display();
	}
	return 0;
}

