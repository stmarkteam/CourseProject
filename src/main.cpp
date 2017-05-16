#include <SFML/Graphics.hpp>

using namespace sf;

float offsetX=0, offsetY=0;
int ground = 304;
const int H = 13;
const int W = 40;

String TileMap[H] = {

"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                                B     B",
"B                                  0   B",
"B                                  BB  B",
"B                                      B",
"B                          0  BBBB 0 BBB",
"B0                   0    BBB    B BB  B",
"BBB                 BBB          B0    B",
"B      BB      BB                BB    B",
"B     B        BB          0           B",
"B 0  B         BB         BB           B",
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
	Collision(0);
	if (!onGround) dy=dy+0.0005*time;
	rect.top += dy*time;
	onGround=false;
	Collision(1);
	currentFrame += 0.005*time;
	if (currentFrame > 6) currentFrame -=6 ;
	if (dx>0) sprite.setTextureRect(IntRect(40*int(currentFrame),244,40,50));
	if (dx<0) sprite.setTextureRect(IntRect(40*int(currentFrame)+40,244,-40,50));
	if (rect.top > ground){
		rect.top = ground;
		dy=0;
		onGround = true;
	}
	sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
	dx=0;
   }

void Collision(int dir){
	for (int i = rect.top/32 ; i<(rect.top+rect.height)/32; i++)
		for (int j = rect.left/32; j<(rect.left+rect.width)/32; j++){ 
	  		if (TileMap[i][j]=='B'){ 
	        		if ((dx>0) && (dir==0)) rect.left =  j*32 -  rect.width; 
				if ((dx<0) && (dir==0)) rect.left =  j*32 + 32;	
				if ((dy>0) && (dir==1)){
					rect.top = i*32 - rect.height;
					dy=0;
					onGround=true;
				}

				if ((dy<0) && (dir==1)){
					rect.top = i*32 + 32;
					dy=0;
				}
			}

		 	if (TileMap[i][j]=='0'){ 
				TileMap[i][j]=' ';
	                } 	
  		}
	}
};

int main(){
	RenderWindow game(VideoMode(600, 400), "Game");
	
	Texture t, m;
	t.loadFromFile("fang.png");
	m.loadFromFile("wq.png");
	Sprite tile(m);
	float currentFrame = 0;
	PLAYER p(t);
	Clock clock;
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
		if (Keyboard::isKeyPressed(Keyboard::Up)){ 
			if (p.onGround){
				p.dy=-0.35;
				p.onGround=false;
			}
		}
		p.update(time);

		if (p.rect.left>300) offsetX = p.rect.left - 300;
        	offsetY = p.rect.top - 200;

		game.clear(Color::White);
		for (int i=0; i<H; i++)
		for (int j=0; j<W ; j++){ 
			if (TileMap[i][j]=='B') tile.setTextureRect(IntRect(160,32,32,32));
			if (TileMap[i][j]=='0') tile.setTextureRect(IntRect(160,256,32,32));
			if (TileMap[i][j]==' ') continue;
			tile.setPosition(j*32-offsetX,i*32 - offsetY) ;
		        game.draw(tile);
	       	 }
		game.draw(p.sprite);
		game.display();
	}
	return 0;
}
	
