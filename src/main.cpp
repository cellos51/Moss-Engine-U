#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <iostream>
#include <map>
#include <romfs-wiiu.h>
#include <whb/proc.h>

#include "text.hpp"

#include "math.hpp"

#include "renderwindow.hpp"

#include "player.hpp"

#include "event.hpp"

#include "level.hpp"

//#include "ui.hpp"

#include "config.hpp" // this just has the screen size so if i change it i dont need to change it in every class

// random shit needed to be here to run
bool init();
SDL_Joystick* gGameController1 = NULL;
SDL_Joystick* gGameController2 = NULL;

// main window
RenderWindow window;
int zoomAmount = 0;

// textures
SDL_Texture* playerTex;
SDL_Texture* tileSet[14];

std::vector<Entity> walls; // literally just walls (for the level) (also why the fuck don't i make a seperete entity derived class for the level??? ahh fuck it)

Vector2 PlayerSpawn = Vector2(0,0);

bool load = init(); // this is the end of textures and windows OK NVM

Player plr1 (PlayerSpawn, window.loadTexture("romfs:/textures/player.png"), Vector2(64,64), 1);
Player plr2 (PlayerSpawn, window.loadTexture("romfs:/textures/dummy.png"), Vector2(64,64), 2);

bool init() // used to initiate things before using
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	SDL_StopTextInput();
	romfsInit();

	window.create("Moss Engine", SCREEN_WIDTH, SCREEN_HEIGHT); // name and size of application window

	// textures
	tileSet[0] = window.loadTexture("romfs:/textures/grass.png");
	tileSet[1] = window.loadTexture("romfs:/textures/dirt1.png");
	tileSet[2] = window.loadTexture("romfs:/textures/dirt2.png");
	tileSet[3] = window.loadTexture("romfs:/textures/dirt3.png");
	tileSet[4] = window.loadTexture("romfs:/textures/dirt4.png");
	tileSet[5] = window.loadTexture("romfs:/textures/dirt5.png");
	tileSet[6] = window.loadTexture("romfs:/textures/dirt6.png");
	tileSet[7] = window.loadTexture("romfs:/textures/dirt7.png");
	tileSet[8] = window.loadTexture("romfs:/textures/dirt8.png"); 
	tileSet[9] = window.loadTexture("romfs:/textures/dirt9.png");
	tileSet[10] = window.loadTexture("romfs:/textures/dirt10.png");
	tileSet[11] = window.loadTexture("romfs:/textures/dirt11.png");
	tileSet[12] = window.loadTexture("romfs:/textures/dirt12.png");
	tileSet[13] = window.loadTexture("romfs:/textures/dirt13.png");

	PlayerSpawn = Level::LoadLevel(Level::LoadFile("romfs:/levels/level1.lvl"), walls, window, tileSet);

	if ( SDL_NumJoysticks() == 1 )
	{
		gGameController1 = SDL_JoystickOpen( 0 );
	}
	else if ( SDL_NumJoysticks() > 1 )
	{
		gGameController1 = SDL_JoystickOpen( 0 );
		gGameController2 = SDL_JoystickOpen( 1 );
	}

	return true;
}

void gameLoop() // it runs forever
{
	if ( SDL_NumJoysticks() > 1 )
	{
		gGameController2 = SDL_JoystickOpen( 1 );
	}
	else 
	{
		gGameController2 = NULL;
	}

	if (SDL_NumJoysticks() == 1)
	{
		window.camera(plr1.transform, plr1.size);
	}
	else if (SDL_NumJoysticks() > 1)
	{
		window.camera(Vector2((plr1.transform.x + plr2.transform.x) / 2, (plr1.transform.y + plr2.transform.y) / 2), plr1.size);
	}
	

	if (Event::JoyDown(SDL_CONTROLLER_BUTTON_LEFTSTICK, 1) && window.zoom != 0.75)
	{
		window.zoom = window.zoom + 0.25;
	}
	else if (Event::JoyDown(SDL_CONTROLLER_BUTTON_START, 1) && window.zoom != 0)
	{
		window.zoom = window.zoom - 0.25;
	}

	plr1.update();

	if (SDL_NumJoysticks() > 1)
	{
		plr2.update();
	}
	

	for (Entity wall : walls)
	{
		plr1.getCol(wall);

		if (SDL_NumJoysticks() > 1)
		{
			plr2.getCol(wall);
		}
	}
}


void render() // honestly i feel like putting the stuff that is at the end of the gameloop in here
{
	window.clear();

	if (SDL_NumJoysticks() > 1)
	{
		window.render(plr2, true);
	}
	
	window.render(plr1, true);

	for (Entity wall : walls)
	{
		window.render(wall, true);
	}
	

	window.display();
}

int main(int argc, char* args[])
{
	while (WHBProcIsRunning()) // main game loop ran every frame
	{
		Time::Tick();
		Event::PollEvent();
		gameLoop();
		render();
	}
	window.quit(); // run when user asks to exit program
	return 0;
}