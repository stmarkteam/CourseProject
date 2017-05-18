#include <SFML/Graphics.hpp>

using namespace sf;

float offsetX=0, offsetY=0;

const int H = 19;
const int W = 133;

String TileMap[H] = {


"                                                                                                                                    ",
"                                        r                                  000000000000000000000000000000000000                   r ",
"0000000000000000000000000000000000000000ZZ0000000000000000000000000000000000                                  0000000000000000000ZZ0",
"0                                                     PP                                                            PPPP           0",
"0r                    r                              PPr                                                               PP          0",
"0ww                                                 PP                                                                 PP         P0",
"0          r   PPP                      P          PP       PPPP     Pnnn       P              P                     r P         P 0",
"0        PPPPP              r                       PP r                                 P         P    r           PPP      PP    0",
"0     P                   PPPPP                      PPPP          P      P  P      P                   P   P                      0",
"0                   r                P                                       wqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqw             PP       0",
"0r                PPPPP                                          P           wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww   P                  0",
"0P  P                                       P                                                               Z       r  r           0",
"0                         w  r    P                         PP                            r          r      Z      PPPPPP          0",
"0    P                    w            r                   PPPP                                             Z                      0",
"0               ww        w           PP         P        PPPPPP                          w          w      Z                     r0",
"0      P        ww        wrrw     P                 P   PPPPPPPP          ww                            w rw  P   r      P      PP0",
"qqqqqqqwwwwwwqqqwwqqqwwwwwwwwwqqqqqqqqqqqqqqqqqqqqqqqqqqqwwwwwwwwwwwwwwwqqqqw                            wwwwqqqqqqPPPPPPPPqqqqqqqqq",
"qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqwwwwwwwwwwwqqqqqqqwwwwwqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq",
"qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq",
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
	sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
	dx=0;
   }

void Collision(int dir){
	for (int i = rect.top/32 ; i<(rect.top+rect.height)/32; i++)
		for (int j = rect.left/32; j<(rect.left+rect.width)/32; j++){ 
	  		if (TileMap[i][j]=='P' || TileMap[i][j]=='0'|| TileMap[i][j]=='w' || TileMap[i][j]=='n'){ 
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

		 	if (TileMap[i][j]=='r'){ 
				TileMap[i][j]=' ';
	                } 	
			if (TileMap[i][j]=='q'){ 
				sprite.setColor(Color::Red);
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

		game.clear(Color::Black);
		for (int i=0; i<H; i++)
		for (int j=0; j<W ; j++){ 
			if (TileMap[i][j]=='0') tile.setTextureRect(IntRect(160,32,32,32));
			if (TileMap[i][j]=='P') tile.setTextureRect(IntRect(160,32,32,32));
			if (TileMap[i][j]=='r') tile.setTextureRect(IntRect(160,256,32,32));
			if (TileMap[i][j]=='q') tile.setTextureRect(IntRect(160,128,32,32));
			if (TileMap[i][j]==' ') continue;
			tile.setPosition(j*32-offsetX,i*32 - offsetY) ;
		        game.draw(tile);
	       	 }
		game.draw(p.sprite);
		game.display();
	}
	return 0;
}
	
