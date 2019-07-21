#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Sprite.h"
#include "flower.h"
#include <time.h> 
#include <stdio.h>
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
	/*
	image[0] = al_load_bitmap("0.png");
	image[1] = al_load_bitmap("1.png");
	image[2] = al_load_bitmap("2.png");
	image[3] = al_load_bitmap("3.png");
	image[4] = al_load_bitmap("4.png");
	image[5] = al_load_bitmap("5.png");
	image[6] = al_load_bitmap("6.png");
	image[7] = al_load_bitmap("7.png");
	image[8] = al_load_bitmap("8.png");
	image[9] = al_load_bitmap("9.png");
	image[10] = al_load_bitmap("10.png");
	*/

	for (int n=0; n < maxframe; n++)
	{
		//sprintf_s(s,"%d.png", n);
		sprintf_s(s,"f%d.png", n);
		image[n] = al_load_bitmap(s);

		al_convert_mask_to_alpha(image[n], al_map_rgb(255, 255, 255));
	}

	width = 50;
	height = 50;
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