#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <time.h> 
#include <stdio.h>
#include "flower.h"

#include <iostream>
using namespace std;

void flower::drawSprite()
{
	//randomly creates a new color
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;
	al_draw_tinted_bitmap(image[curframe], al_map_rgba_f(r, g, b, 1), x, y, 0);
}

/*void flower::updatesprite()
{
	//update x position
	if (++xcount > xdelay)
	{
		xcount = 0;
		x += xspeed;
	}

	//update y position
	if (++ycount > ydelay)
	{
		ycount = 0;
		y += yspeed;
	}


	if (framecount++ > framedelay)
	{
		framecount = 0;
		curframe++;
		if (curframe >= maxframe)
			curframe = 0;
	}
}*/

/*
void flower::bouncesprite(int SCREEN_W, int SCREEN_H)
{
	//simple screen bouncing behavior
	if (x < 0)
	{
		x = 0;
		xspeed = rand() % 2 + 4;
		animdir *= -1;
	}

	else if (x > SCREEN_W - width)
	{
		x = SCREEN_W - width;
		xspeed = rand() % 2 - 6;
		animdir *= -1;
	}

	if (y < 0)
	{
		y = 0;
		yspeed = rand() % 2 + 4;
		animdir *= -1;
	}

	else if (y > SCREEN_H - height)
	{
		y = SCREEN_H - height;
		yspeed = rand() % 2 - 6;
		animdir *= -1;
	}

}
*/

void flower::load_animated_sprite(int size, int w, int h, int power)
{

	collision = false;
	//load the animated sprite
	char s[80];
	maxframe = size;
	for (int n = 0; n < size; n++)
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
	x = rand() % w;
	y = rand() % h;
	cout << x << " " << y << endl;
	//set up specialty Power
	for (int x = 0; x < 4; x++)
		specialityPower[x] = false;
	//0=Spining, 1= Scared, 2=Baby, 3=Freeze
	switch (power)
	{
	case 0:
		specialityPower[0] = true;
		break;
	case 1:
		specialityPower[1] = true;
		break;
	case 2:
		specialityPower[2] = true;
		break;
	case 3:
		specialityPower[3] = true;
		break;
	}

}

flower::~flower()
{
	for (int i = 0; i < maxframe; i++)
		al_destroy_bitmap(image[i]);
}

void flower::Collision(flower s[], int size, int e, int w, int h)
{
	for (int i = 0; i < size; i++)
	{
		if (i != e) {
			if (x >= s[i].getX() - w && x <= s[i].getX() + w) {
				if (y >= s[i].getY() - h && y <= s[i].getY() + h) {

					x = rand() % (w - width);
					y = rand() % (h - height);
					collision = true;

				}

			}

		}
	}

}