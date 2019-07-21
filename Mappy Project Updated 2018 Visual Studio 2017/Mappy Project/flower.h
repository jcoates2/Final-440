#ifndef FLOWERH
#define FLOWERH
#include "Sprite.h"
class flower
{
public:
	~flower();
	flower();
	void Collision(Sprite &Player);
	void growFlower(int WIDTH, int HEIGHT); // randomly generates flowers
	void drawSprite();
	int getX() { return x; }
	int getY() { return y; }
private:
	int x, y;
	int width, height;
	bool collision;
	bool live;
	int curframe, maxframe, animdir;
	int framecount, framedelay;
	ALLEGRO_BITMAP* image[11];
};
#endif

