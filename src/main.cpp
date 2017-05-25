#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

float offsetX=0, offsetY=0;

const int H = 28;
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
"0                                                    PP                                       r                        P           0",
"0r                    r                             PP r                                                               P           0",
"0ww                                                PP                                                                  P          P0",
"0          r   PPP                      P          PP       PPPP     Pnnn       P             P                      r P         P 0",
"0        PPPPP              r                       PP r                            r    P         P    r           PPPP     PP    0",
"0     P                   PPPPP                      PPPP          P      P  P      P                   P   P                      0",
"0                   r                P                                       wqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqw             PP       0",
"0r                PPPPP                                          P           wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww   P                  0",
"0P  P                                       P                                                               Z       r   r          0",
"0                         w  r    P                         PP                            r          r      Z       PPPPP          0",
"0    P                    w            r                   PPPP                                             Z                      0",
"0               ww        w           PP         P        PPPPPP                          w          w      Z                      0",
"0      P    w   ww   w    wrrw     P                 P   PPPPPPPP      w    w                              rw  P   P  r   P       r0",
"qqqqqqqwwwwwwqqqwwqqqwwwwwwwwwqqqqqqqqqqqqqqqqqqqqqqqqqqqwwwwwwwwwwwwwwwqqqqw         w       w   w      wwwwqqqqqqPPPPPPPPqqqqqqPPP",
"qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqwwwwwwwwwwwqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq",
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
};

class PLAYER {
public:
	int n, l;
	float dx,dy,currentFrame;
	bool onGround;
	Sprite sprite;
	FloatRect rect;

	PLAYER(Texture &image){
		sprite.setTexture(image);
		rect = FloatRect(10*32,15*32,40,50);
		dx=dy=0.1;
		currentFrame = 0;
  }

	int update(float time, int& n){
		rect.left += dx * time;
		l = Collision(0, n);

		if (!onGround) dy=dy+0.0005*time;
		rect.top += dy*time;
		onGround=false;
		l = Collision(1, n);

		if (l==7) return 7;
		if (l==5) return 5;

		currentFrame += 0.005*time;
		if (currentFrame > 6) currentFrame -=6 ;

		if (dx>0) sprite.setTextureRect(IntRect(40*int(currentFrame),244,40,50));
		if (dx<0) sprite.setTextureRect(IntRect(40*int(currentFrame)+40,244,-40,50));

		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
		dx=0;
		return 0;
  }

	int Collision(int dir, int& n){
		int ret = 0;
		for (int i = rect.top/32 ; i<(rect.top+rect.height)/32 && i >=0 && i <= 32; i++){
		for (int j = rect.left/32; j<(rect.left+rect.width)/32 ; j++){
	  	if (TileMap[i][j]=='P' || TileMap[i][j]=='0'|| TileMap[i][j]=='w' || TileMap[i][j]=='n' || TileMap[i][j]=='a'){
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
				n = n-1;
				TileMap[i][j] = ' ';
				std::cout << n << '\n';
				if (n==0) return 7;
	    }
			if (TileMap[i][j]=='Z')TileMap[i][j]=' ';
			if (TileMap[i][j]=='q'){
				return 5;
				break;
			}
		}
	}
			return ret;
	}
};

int main(){
	int n = 25;
	int flagRun = 1;
	RenderWindow game(VideoMode(600, 400), "Game");
	Font font;
  	font.loadFromFile("sansation.ttf");

	Texture t, m, f;
		t.loadFromFile("fang.png");
		m.loadFromFile("wq.png");
		f.loadFromFile("fon.png");

	Texture menu1,menu2;
		menu1.loadFromFile("1.png");
    menu2.loadFromFile("2.png");

	Text dead;
   	dead.setFont(font);
  	dead.setCharacterSize(50);
   	dead.setPosition(200.f, 150.f);
   	dead.setColor(Color::White);
   	dead.setString("You dead!");

	Text start;
    start.setFont(font);
  	start.setCharacterSize(20);
  	start.setPosition(160.f, 300.f);
		start.setColor(Color::White);
  	start.setString("<press space to start the game>");

	Sprite tile(m),sBackground(f);
	Sprite m1(menu1),m2(menu2);
	int flagEnd = 0;
	label:
	bool Menu = true, life = true;
	int MenuNum=0, z;
	m1.setPosition(200,150);
	m2.setPosition(200,200);

	while(Menu){
		m1.setColor(Color::White);
		m2.setColor(Color::White);
		game.draw(sBackground);

		if (IntRect(200,150,300,50).contains(Mouse::getPosition(game))){
			m1.setColor(Color::Red);
			MenuNum = 1;
		}
    if (IntRect(200,200,300,50).contains(Mouse::getPosition(game))){
			m2.setColor(Color::Red);
			MenuNum = 2;
		}
		if (Mouse::isButtonPressed(Mouse::Left)){
			if (MenuNum==1){
				Menu = false;
				life = true;
			}
			if (MenuNum == 2) {
				game.close();
				Menu = false;
			}
		}
		if(flagEnd == 1) {
			dead.setPosition(200.f, 80.f);
			game.draw(dead);
			flagEnd = 0;
		} else if (flagEnd == 2){
			dead.setPosition(200.f, 80.f);
			dead.setString("You Win!");
			game.draw(dead);
			flagEnd = 0;
		}
		game.draw(m1);
  	game.draw(m2);
		game.display();
	}

	float currentFrame = 0;
	int text;
	PLAYER p(t);
	Clock clock;
	while (game.isOpen()){
		Event event;
		while(game.pollEvent(event)){
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)){
				game.close();
				break;}
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Space)){
				life=true;
					}
			}
			while (life == true){
				float time = clock.getElapsedTime().asMicroseconds();
				clock.restart();
				time = time/700;
				if (Keyboard::isKeyPressed(Keyboard::Left))p.dx = -0.1;
				if (Keyboard::isKeyPressed(Keyboard::Right))p.dx = 0.1;
				if (Keyboard::isKeyPressed(Keyboard::Up)){
					if (p.onGround){
						p.dy=-0.35;
						p.onGround=false;
					}
				}
				z = p.update(time, n);
				if (z == 7) {
					life = false;
					text = 1;
				}
				if (z == 5) {
					life = false;
					text = 2;
				}
				if ((p.rect.left>300) && (p.rect.left<3930)) offsetX = p.rect.left - 300;
        offsetY = p.rect.top - 200;

				if (life == true){
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
				}
				else {
					if (text == 1) {
						game.draw(sBackground);
						dead.setString("You Win!");
						game.draw(dead);
						game.draw(start);
						flagEnd = 2;
					}
					if (text == 2) {
						game.draw(sBackground);
						game.draw(dead);
						game.draw(start);
						flagEnd = 1;
						goto label;
					}
				}
				game.display();
		}
	}
	return 0;
}
