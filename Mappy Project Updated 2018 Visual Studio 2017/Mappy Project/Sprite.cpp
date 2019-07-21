
#include "Sprite.h"

Sprite::Sprite()
{
	image=NULL;
}

Sprite::~Sprite()
{
	al_destroy_bitmap(image);
}

void Sprite::InitSprites(int width, int height)
{
	x = 80;
	y = 240;


	maxFrame = 5;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 137.8;
	frameHeight = 130;
	animationColumns = 5;
	animationDirection = 1;

	image = al_load_bitmap("butterfly.png");
	al_convert_mask_to_alpha(image, al_map_rgb(255,255,255));
	al_convert_mask_to_alpha(image, al_map_rgb(253, 253, 253));
}

void Sprite::UpdateSprites(int width, int height, int dir)
{
	int oldx = x;
	int oldy = y;

	if(dir == 1){ //right key
		animationDirection = 1; 
		x+=3; 
		if (++frameCount > frameDelay)
		{
			frameCount=0;
			if (++curFrame > maxFrame)
				curFrame=1;
		}
	} else if (dir == 0){ //left key
		animationDirection = 0; 
		x-=3; 
		if (++frameCount > frameDelay)
		{
			frameCount=0;
			if (++curFrame > maxFrame)
				curFrame=1;
		}
	}
	else if (dir == 2) { //up key
		animationDirection = 2;
		y -= 3;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > maxFrame)
				curFrame = 1;
		}
	}
	else if (dir == 3) { //down key
		y += 3;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > maxFrame)
				curFrame = 1;
		}
	}
	

	//check for collided with foreground tiles
	if (animationDirection == 0)
	{ 
		if (collided(x, y + frameHeight)) { //collision detection to the left
			x = oldx; 
			y= oldy;
		}

	}
	else if (animationDirection == 1)
	{ 
		if (collided(x + frameWidth, y + frameHeight)) { //collision detection to the right
			x = oldx; 
			y= oldy;
		}
	}
	else if (animationDirection == 2)
	{
		if (collided(x, y)) { //collision detection up
			x = oldx;
			y = oldy;
		}
	}
	else if (animationDirection == 3)
	{
		if (collided(x, y + frameHeight)) { //collision detection down
			x = oldx;
			y = oldy;
		}
	}
}

bool Sprite::CollisionEndBlock()
{
	if (endValue(x + frameWidth/2, y + frameHeight + 5))
		return true;
	else
		return false;
}

void Sprite::DrawSprites(int xoffset, int yoffset)
{
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;

	if (animationDirection == 1) {
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, ALLEGRO_FLIP_HORIZONTAL);
	}
	else if (animationDirection == 0) {
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	}
	else 
		al_draw_bitmap_region(image, 0, 0, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);

	

	/*if (animationDirection == 0) { //if going left
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, ALLEGRO_FLIP_HORIZONTAL);
	}else if (animationDirection == 1) //rigth
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	else if (animationDirection == 2) // up
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	else // down
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);*/
}