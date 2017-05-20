#include <SFML/Graphics.hpp>

using namespace sf;

float offsetX=0, offsetY=0;

const int H = 30;
const int W = 133;

String TileMap[H] = {
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"000000000000000000000000000000000000000ZrZ0000000000000000000000000000000000                                  0000000000000000000Zr0",
"000000000000000000000000000000000000000ZZZ0000000000000000000000000000000000                                  0000000000000000000ZZ0",
"0                                                    PP                                                                P           0",
"0r                    r                             PP r                                                               P           0",
"0ww                                                PP                                                                  P          P0",
"0          r   PPP                      P          PP       PPPP     Pnnn       P             P                      r P         P 0",
"0        PPPPP              r                       PP r                                 P         P    r           PPPP     PP    0",
"0     P                   PPPPP                      PPPP          P      P  P      P                   P   P                      0",
"0                   r                P                                       wqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqw             PP       0",
"0r                PPPPP                                          P           wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww   P                  0",
"0P  P                                       P                                                               Z       r  r           0",
"0                         w  r    P                         PP                            r          r      Z       PPPPP          0",
"0    P                    w            r                   PPPP                                             Z                      0",
"0               ww        w           PP         P        PPPPPP                          w          w      Z                      0",
"0      P        ww        wrrw     P                 P   PPPPPPPP      w    w                              rw  P   r      P       r0",
"qqqqqqqwwwwwwqqqwwqqqwwwwwwwwwqqqqqqqqqqqqqqqqqqqqqqqqqqqwwwwwwwwwwwwwwwqqqqw         w       w   w      wwwwqqqqqqPPPPPPPPqqqqqqPPq",
"qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqwwwwwwwwwwwqqqqqqqwwwwwqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq",
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
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
	rect = FloatRect(6*32,8*32,40,50);
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
	  		if (TileMap[i][j]=='P' || TileMap[i][j]=='0'|| TileMap[i][j]=='w' || TileMap[i][j]=='n' || TileMap[i][j]=='a') 					{ 
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

		 	if (TileMap[i][j]=='r' || TileMap[i][j]=='Z'){ 
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
	
	Texture t, m, f;
	t.loadFromFile("fang.png");
	m.loadFromFile("wq.png");
	f.loadFromFile("fon.png");

	Texture menu1,menu2;
	menu1.loadFromFile("1.png");
    	menu2.loadFromFile("2.png");

	Sprite menu1(menu1),menu2(menu2);

	bool Menu=1;
	int MenuNum=0;
	menu1.setPosition(200,150);
	menu2.setPosition(200,200);
	
	Sprite tile(m),sBackground(f);

	while(Menu)
	{	  
	menu1.setColor(Color::White);
	menu2.setColor(Color::Red);
	MenuNum=0;
	game.draw(sBackground);

	if (IntRect(200,150,300,50).contains(Mouse::getPosition(game))){
		menu1.setColor(Color::Red);
		MenuNum=1;
	}
       	if (IntRect(200,200,300,50).contains(Mouse::getPosition(game))){
		menu3.setColor(Color::Red);
		MenuNum=2;
	}
	if (Mouse::isButtonPressed(Mouse::Left)){
		if (MenuNum==1) Menu=false;
		if (MenuNum==2) {
			game.close();
			Menu=false;
		}

	     }   
	game.draw(menu1);
        game.draw(menu2);
	game.display();
	}

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

		if ((p.rect.left>300) && (p.rect.left<3930)) offsetX = p.rect.left - 300;
        	offsetY = p.rect.top - 200;

		game.draw(sBackground);
		for (int i=0; i<H; i++)
		for (int j=0; j<W ; j++){ 
			if (TileMap[i][j]=='0') tile.setTextureRect(IntRect(416,128,32,32));
			if (TileMap[i][j]=='P') tile.setTextureRect(IntRect(416,128,32,32));
			if (TileMap[i][j]=='w') tile.setTextureRect(IntRect(416,128,32,32));
			if (TileMap[i][j]=='r') tile.setTextureRect(IntRect(160,256,32,32));
			if (TileMap[i][j]=='q') tile.setTextureRect(IntRect(160,128,32,32));
			if (TileMap[i][j]=='a') tile.setTextureRect(IntRect(160,128,32,32));
			if (TileMap[i][j]==' ') continue;
			tile.setPosition(j*32-offsetX,i*32 - offsetY) ;
		        game.draw(tile);
	       	 }
		game.draw(p.sprite);
		game.display();
	}
	return 0;
}
	
