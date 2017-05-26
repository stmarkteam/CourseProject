#include "function.h"
#include "map.h"

float offsetX=0, offsetY=0;

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
				TileMap[i][j] = '1';
				std::cout << n << '\n';
				if (n==0) return 7;
	    }
			if (TileMap[i][j]=='Z')TileMap[i][j]='2';
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
	int n = 25, z;
	int flagRun = 1;
	RenderWindow game(VideoMode(800, 500), "Game");
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
   	dead.setPosition(290.f, 200.f);
   	dead.setColor(Color::White);
   	dead.setString("You dead!");

	Sprite tile(m),sBackground(f);
	Sprite m1(menu1),m2(menu2);
	int flagEnd = 0;
	label:
	bool Menu = true, life = true;
	m1.setPosition(310,200);
	m2.setPosition(310,250);

	while(Menu){
		int MenuNum=0;
		m1.setColor(Color::White);
		m2.setColor(Color::White);
		game.draw(sBackground);

		if (IntRect(310,200,180,50).contains(Mouse::getPosition(game))){
			m1.setColor(Color::Red);
			MenuNum = 1;
		}
    if (IntRect(310,250,110,50).contains(Mouse::getPosition(game))){
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
			game.draw(dead);
			game.display();
			for (long long i = 0; i < 1000000000; i++);
		} else if (flagEnd == 2){
			game.draw(dead);
			game.display();
			for (long long i = 0; i < 1000000000; i++);
		}
		flagEnd = 0;
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
        offsetY = p.rect.top - 250;

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
						if (TileMap[i][j]==' ' | TileMap[i][j]=='1' | TileMap[i][j]=='2') continue;
						tile.setPosition(j*32-offsetX,i*32 - offsetY) ;
		        game.draw(tile);
	       	 	}
					game.draw(p.sprite);
				}
				else {
					if (text == 1) {
						game.draw(sBackground);
						dead.setString("You win!");
						flagEnd = 2;
						n = 25;
						for (int i=0; i<H; i++)
						for (int j=0; j<W ; j++){
							if (TileMap[i][j]=='1') TileMap[i][j] ='r';
							if (TileMap[i][j]=='2') TileMap[i][j] ='Z';
							tile.setPosition(j*32-offsetX,i*32 - offsetY) ;
						}
						goto label;
					}
					if (text == 2) {
						game.draw(sBackground);
						dead.setString("You dead!");
						flagEnd = 1;
						n = 25;
						for (int i=0; i<H; i++)
						for (int j=0; j<W ; j++){
							if (TileMap[i][j]=='1') TileMap[i][j] ='r';
							if (TileMap[i][j]=='2') TileMap[i][j] ='Z';
							tile.setPosition(j*32-offsetX,i*32 - offsetY) ;
						}
						goto label;
					}
				}
				game.display();
		}
	}
	return 0;
}
