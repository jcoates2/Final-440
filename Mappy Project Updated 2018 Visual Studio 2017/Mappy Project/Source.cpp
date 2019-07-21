#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "SpriteSheet.h"
#include "mappy_A5.h"
#include <iostream>
using namespace std;

int collided(int x, int y);  //Tile Collision
bool endValue( int x, int y ); //End Block with the User Value = 8
int main(void)
{
	const int WIDTH = 900;
	const int HEIGHT = 480; //original 480
	bool keys[] = {false, false, false, false, false};
	enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};
	//variables
	bool done = false;
	bool render = false;
	//Player Variable
	Sprite player;
	int score = 0;



	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_SAMPLE* music;
	ALLEGRO_BITMAP* intro = NULL;
	ALLEGRO_BITMAP* end = NULL;

	//add a timer
	time_t currentTime = NULL;// current time and start time for collision
	time_t startTime = NULL;
	//program init
	if(!al_init())										//initialize Allegro
		return -1;

	//install audio - al_install audio also came up as false
	/*
	if (!al_install_audio()) {
		cout << "yikes";
		return -1;
	}
	if (!al_init_acodec_addon()) {
		cout << "gosh";
		return -1;
	}
	if (!al_reserve_samples(1)) {
		cout << "seriously";
		return -1;
	}
	//music = al_load_sample("rainbow.aiff");
	music = al_load_sample("backgroundMusic.wav");

	if (!music) {
		cout << "does not work";
		exit(9);
	}
	*/

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if (!display)	//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	//draw the intro 
	intro = al_load_bitmap("Intro.png");
	end = al_load_bitmap("End.png");
	al_draw_bitmap(intro, WIDTH/4, 0, 0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_rest(3);

	player.InitSprites(WIDTH,HEIGHT);
	//add the front 
	ALLEGRO_FONT* hop = al_load_font("BunnyHopper.ttf", 50, 0);


	int xOff = 0;
	int yOff = 0;
	if (MapLoad("forrest.FMP", 1))
		return -5;
	

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	//draw the background tiles
	MapDrawBG(xOff,yOff, 0, 0, WIDTH-1, HEIGHT-1);

	//draw foreground tiles
	MapDrawFG(xOff,yOff, 0, 0, WIDTH-1, HEIGHT-1, 0);
	player.DrawSprites(0,0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
	//set up levels
	bool levelOver = false;
	//start timer
	startTime = time(NULL);

	//al_play_sample(music, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
	while(!done)
	{
		currentTime = time(NULL);

		//check if current level is over
		if (levelOver)
		{
			startTime = 0;
			currentTime = 0;
			levelOver = false;	
		}

		//check if timer is over
		if (currentTime - startTime >= 60) {
			done = true;
		}

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;
			if(keys[UP])
				player.UpdateSprites(WIDTH, HEIGHT, 2);
			else if(keys[DOWN])
				player.UpdateSprites(WIDTH, HEIGHT, 3);
			else if(keys[LEFT])
				player.UpdateSprites(WIDTH,HEIGHT,0);
			else if(keys[RIGHT])
				player.UpdateSprites(WIDTH,HEIGHT,1);
			
			if (player.CollisionEndBlock()) {
				//cout << "Next Level\n";
				//levelOver = true;
			}
			render = true;

		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}
		if(render && al_is_event_queue_empty(event_queue) && currentTime - startTime < 60)
		{
			render = false;

			//update the map scroll position
			xOff = player.getX()+player.getWidth() - WIDTH/2 ;
			yOff = player.getY()+player.getHeight()   - HEIGHT/2 ;

			//avoid moving beyond the map edge
			if (xOff < 0) xOff = 0;

			if (xOff > (mapwidth * mapblockwidth - WIDTH))
				xOff = mapwidth * mapblockwidth - WIDTH;
			if (yOff < 0) 
				yOff = 0;
			if (yOff > (mapheight * mapblockheight - HEIGHT)) 
				yOff = mapheight * mapblockheight - HEIGHT;

			//draw the background tiles
			MapDrawBG(xOff,yOff, 0, 0, WIDTH, HEIGHT);

			//draw foreground tiles
			MapDrawFG(xOff,yOff, 0, 0, WIDTH, HEIGHT, 0);
			
			player.DrawSprites(xOff, yOff);
			//draw timer and score
			al_draw_textf(hop, al_map_rgb(153,0,153), 20, 430, ALLEGRO_ALIGN_LEFT, "Flower Score: ", score);
			al_draw_textf(hop, al_map_rgb(153, 0, 153), WIDTH / 2, 430, ALLEGRO_ALIGN_CENTRE, "You have 60 seconds: %d", (currentTime- startTime));
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
		
	}
	//draw the conclustion
	al_draw_bitmap(end, WIDTH / 4, 0, 0);
	al_draw_textf(hop, al_map_rgb(153, 0, 153), 20, 430, ALLEGRO_ALIGN_LEFT, "Final Score: ", score);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_rest(3);

	al_clear_to_color(al_map_rgb(0, 0, 0));

	MapFreeMem();
	al_destroy_bitmap(intro);
	al_destroy_bitmap(end);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);	
	//destroy our display object

	return 0;
}



int collided(int x, int y)
{
	BLKSTR *blockdata;
	blockdata = MapGetBlock(x/mapblockwidth, y/mapblockheight);
	return blockdata->tl;
}

bool endValue( int x, int y )
{

	BLKSTR* data;
	data = MapGetBlock( x/mapblockwidth, y/mapblockheight );

	if( data->user1 == 10 )
	{
		return true;
	}else
		return false;
}