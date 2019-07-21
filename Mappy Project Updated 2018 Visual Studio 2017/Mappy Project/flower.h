class flower
{
public:
	~flower();
	//void updatesprite();
	void bouncesprite(int SCREEN_W, int SCREEN_H);
	void load_animated_sprite(int size, int width, int height, int power);
	void Collision(flower s[], int size, int e, int w, int h);
	void drawSprite();
	int getX() { return x; }
	int getY() { return y; }


private:
	int x, y;
	int width, height;
	int xspeed, yspeed;
	int xdelay, ydelay;
	int xcount, ycount;
	bool specialityPower[4]; //0=Spining, 1= Scared, 2=Baby, 3=Freeze
	bool collision;
	bool paused;
	int angle = 0;
	int life = 0;
	int curframe, maxframe, animdir;
	int framecount, framedelay;
	ALLEGRO_BITMAP* image[4];
};

