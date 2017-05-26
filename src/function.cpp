#include "function.h"

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
