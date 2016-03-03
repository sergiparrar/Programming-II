// ----------------------------------------------------------------
// Awesome simple game with SDL
// http://wiki.libsdl.org/APIByCategory
// ----------------------------------------------------------------

#include "stdlib.h"
#include "string.h"

#include "SDL\include\SDL.h"
#include "SDL_image\include\SDL_image.h"
// TODO 1: Add SDL_mixer library
// You need to add the include file (.h)
// The library (.lib) and make sure all .dll
// are in the executable's folder. Everything 
// is in the folder file already.
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

// Globals --------------------------------------------------------
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define SCROLL_SPEED 5
#define SHIP_SPEED 3
#define NUM_SHOTS 32
#define SHOT_SPEED 5
#define MAX_KEYS 300
#define SPRITE_SIZE 32

enum KEY_STATE
{
	KEY_IDLE,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

struct projectile
{
	int x, y;
	bool alive;
};

struct globals
{
	SDL_Window* window;
	SDL_Surface* w_surface;
	SDL_Renderer* renderer;
	SDL_Texture* background;
	int background_width;
	SDL_Texture* ship;
	int ship_x;
	int ship_y;
	SDL_Texture* shot;
	SDL_Texture* missil;
	projectile shots[NUM_SHOTS];
	projectile mshots[NUM_SHOTS];
	int last_shot;
	bool missilfire, fire, up, down, left, right;
	KEY_STATE* keyboard;
	// TODO 4:
	// Add pointers to store music and the laser fx
	Mix_Music *music;
	Mix_Chunk *laserfx;
	int scroll;
} g;

// ----------------------------------------------------------------
void Start()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	// Create window --
	g.window = SDL_CreateWindow("Super Awesome Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	g.w_surface = SDL_GetWindowSurface(g.window);

	// Create renderer --
	g.renderer = SDL_CreateRenderer(g.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(g.renderer, 0, 0, 0, 255);

	// Load image lib --
	IMG_Init(IMG_INIT_PNG);
	g.background = SDL_CreateTextureFromSurface(g.renderer, IMG_Load("background.png"));
	g.ship = SDL_CreateTextureFromSurface(g.renderer, IMG_Load("ship.png"));
	g.shot = SDL_CreateTextureFromSurface(g.renderer, IMG_Load("shot.png"));
	g.missil = SDL_CreateTextureFromSurface(g.renderer, IMG_Load("sprites.png"));
	SDL_QueryTexture(g.background, NULL, NULL, &g.background_width, NULL);

	// Create mixer --
	// TODO 2:
	// Initialize the audio library 
	// Check https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC7
	// load support for the OGG sample/music formats
	int flags = MIX_INIT_OGG;
	int initted = Mix_Init(flags);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	// TODO 5:
	// Load music.ogg and play it. Store the pointer to it.
	// Load the laser.wav file and store a pointer to it
	g.music = Mix_LoadMUS("music.ogg");
	Mix_PlayMusic(g.music, -1);
	g.laserfx = Mix_LoadWAV("laser.wav");

	// Init other vars --
	g.scroll = 0;
	g.ship_x = 100;
	g.ship_y = SCREEN_HEIGHT / 2;
	g.missilfire = g.fire = g.up = g.down = g.left = g.right = false;
	g.last_shot = 0;
	g.keyboard = (KEY_STATE*)malloc(sizeof(KEY_STATE) * MAX_KEYS);
	memset(g.keyboard, KEY_IDLE, MAX_KEYS);
}

// ----------------------------------------------------------------
void Finish()
{
	// TODO 6:
	// Stop and free the music and fx
	Mix_HaltMusic();
	Mix_FreeMusic(g.music);
	Mix_FreeChunk(g.laserfx);
	
	// TODO 3:
	// Close the audio library
	Mix_CloseAudio();

	SDL_DestroyTexture(g.background);
	SDL_DestroyTexture(g.ship);
	IMG_Quit();
	SDL_DestroyRenderer(g.renderer);
	SDL_DestroyWindow(g.window);
	SDL_Quit();
	free(g.keyboard);
}

// ----------------------------------------------------------------
bool CheckInput()
{
	SDL_PumpEvents();
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	// cyle keyboard keys
	for(int i = 0; i < MAX_KEYS; ++i)
	{	
		if(keys[i] == 1)
			g.keyboard[i] = (g.keyboard[i] == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
		else
			g.keyboard[i] = (g.keyboard[i] == KEY_REPEAT || g.keyboard[i] == KEY_DOWN) ? KEY_UP : KEY_IDLE;
	}

	if(g.keyboard[SDL_SCANCODE_ESCAPE] == KEY_DOWN)
		return false;

	g.up = g.keyboard[SDL_SCANCODE_UP] == KEY_REPEAT;
	g.down = g.keyboard[SDL_SCANCODE_DOWN] == KEY_REPEAT;
	g.left = g.keyboard[SDL_SCANCODE_LEFT] == KEY_REPEAT;
	g.right = g.keyboard[SDL_SCANCODE_RIGHT] == KEY_REPEAT;
	g.fire = g.keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN;
	g.missilfire = g.keyboard[SDL_SCANCODE_LCTRL] == KEY_DOWN;

	return true;
}

// ----------------------------------------------------------------
void MoveStuff()
{
	// Calc new ship position
	// TODO 8: move the ship
	// Knowing the booleans up/down/left/right
	// hold true if the player is trying to move in that direction
	// calc player's next position (stored in g.x and g.y)

	while (g.up){
		g.up = false;
		if (g.ship_y >= 0)
			g.ship_y -= SHIP_SPEED;
		if (g.ship_y < 0) g.ship_y = 0;
	}
	while (g.down){
		g.down = false;
		if (g.ship_y <= SCREEN_HEIGHT - 64)
			g.ship_y += SHIP_SPEED;
		if (g.ship_y > SCREEN_HEIGHT - 64) g.ship_y = SCREEN_HEIGHT - 64;
	}
	while (g.left){
		g.left = false;
		if (g.ship_x >= 0)
			g.ship_x -= SHIP_SPEED;
		if (g.ship_x < 0) g.ship_x = 0;
	}
	while (g.right){
		g.right = false;
		if (g.ship_x <= SCREEN_WIDTH - 64)
			g.ship_x += SHIP_SPEED;
		if (g.ship_x > SCREEN_WIDTH - 64) g.ship_x = SCREEN_WIDTH - 64;
	}

	if(g.fire)
	{
		g.fire = false;
		Mix_PlayChannel(1, g.laserfx, 0);

		if(g.last_shot == NUM_SHOTS)
			g.last_shot = 0;

		g.shots[g.last_shot].alive = true;
		g.shots[g.last_shot].x = g.ship_x + 32;
		g.shots[g.last_shot].y = g.ship_y;
		g.last_shot++;
	}
	if (g.missilfire)
	{
		g.missilfire = false;
		Mix_PlayChannel(1, g.laserfx, 0);

		if (g.last_shot == NUM_SHOTS)
			g.last_shot = 0;

		g.mshots[g.last_shot].alive = true;
		g.mshots[g.last_shot].x = g.ship_x + 32;
		g.mshots[g.last_shot].y = g.ship_y;
		g.last_shot++;
	}


	for(int i = 0; i < NUM_SHOTS; ++i)
	{
		if(g.mshots[i].alive)
		{
			if(g.mshots[i].x < SCREEN_WIDTH)
				g.mshots[i].x += SHOT_SPEED;
			else
				g.mshots[i].alive = false;
		}
		if (g.shots[i].alive)
		{
			if (g.shots[i].x < SCREEN_WIDTH)
				g.shots[i].x += SHOT_SPEED;
			else
				g.shots[i].alive = false;
		}
	}
}

// ----------------------------------------------------------------
void Draw()
{
	// Clear screen to black
	SDL_RenderClear(g.renderer);

	SDL_Rect target;
	SDL_Rect sprite;

	// Draw the background and scroll --
	// TODO 9: scroll the background
	// you should move target.x over time
	// Remember that you have to draw the
	// background twice to fake repetition
	if (g.scroll >= g.background_width) g.scroll = 0;
	target.x = -g.scroll;
	target.y = 0;
	target.w = g.background_width;
	target.h = SCREEN_HEIGHT;

	SDL_RenderCopy(g.renderer, g.background, NULL, &target);

	target.x = g.background_width - g.scroll;
	SDL_RenderCopy(g.renderer, g.background, NULL, &target);

	g.scroll += SCROLL_SPEED;

	// Draw the ship --
	target.x = g.ship_x;
	target.y = g.ship_y;
	target.w = 64;
	target.h = 64;
	SDL_RenderCopy(g.renderer, g.ship, NULL, &target);

	// Draw lasers --
	target.w = 64;
	target.h = 64;

	for(int i = 0; i < NUM_SHOTS; ++i)
	{
		if(g.shots[i].alive)
		{
			target.x = g.shots[i].x;
			target.y = g.shots[i].y;
			SDL_RenderCopy(g.renderer, g.shot, NULL, &target);
		}
	}

	// Draw missil --
	//Position in the sprite
	sprite.x = SPRITE_SIZE * 2;
	sprite.y = SPRITE_SIZE * 7;
	sprite.w = SPRITE_SIZE;
	sprite.h = SPRITE_SIZE;

	target.w = 64;
	target.h = 64;

	SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

	for (int i = 0; i < NUM_SHOTS; ++i)
	{
		if (g.mshots[i].alive)
		{
			target.x = g.mshots[i].x;
			target.y = g.mshots[i].y;
			SDL_RenderCopyEx(g.renderer, g.missil, &sprite, &target, NULL, NULL, flip);
		}
	}

	// Finally present framebuffer
	SDL_RenderPresent(g.renderer);
}

// ----------------------------------------------------------------
int main(int argc, char* argv[])
{
	Start();

	while(CheckInput())
	{
		MoveStuff();
		Draw();
	}

	Finish();
	return(EXIT_SUCCESS);
}

// TODO 7: Play the laser fx 
// (you need to find where this should happen)
