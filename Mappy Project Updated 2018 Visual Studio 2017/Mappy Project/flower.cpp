#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Sprite.h"
#include <time.h> 
#include <stdio.h>
#include "flower.h"
#include <iostream>
using namespace std;

void flower::drawSprite()
{
	if (live) {
		//randomly creates a new color
		int r = rand() % 255;
		int g = rand() % 255;
		int b = rand() % 255;
		al_draw_tinted_bitmap(image[curframe], al_map_rgba_f(r, g, b, 1), x, y, 0);
	}
}


void flower::growFlower(int WIDTH, int HEIGHT)
{
	if (!live)
	{
		if (rand() % 500 == 0)
		{
			live = true;
			x = rand() %  (WIDTH) - width;
			y = rand() % (HEIGHT - height);

		}
	}
}



flower::flower()
{
	collision = false;
	//load the animated sprite
	char s[80];
	maxframe = 11;
	for (int n = 0; n < 11; n++)
	{
		sprintf_s(s, "%d.png", n);
		image[n] = al_load_bitmap(s);

		//al_convert_mask_to_alpha(image[n], al_map_rgb(255, 255, 255));
	}
	width = al_get_bitmap_width(image[0]);
	height = al_get_bitmap_height(image[0]);
	curframe = 0;
	framedelay = 5;
	framecount = 0;
}

flower::~flower()
{
	for (int i = 0; i < maxframe; i++)
		al_destroy_bitmap(image[i]);
}

void flower::Collision(Sprite &Player)
{
	if(live)
	{
		if (x - width < Player.getX() + Player.getWidth() &&
			x + width > Player.getX() - Player.getWidth() &&
			y - height < Player.getY() + Player.getHeight() &&
			y + height > Player.getY() - Player.getHeight())
		{
			live = false;
			//collision = true; 
			Player.updateScore();
		}
		else if (x < 0)
		{
			live = false;
		}
	}

}