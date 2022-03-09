#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "constants.h"
#include <filesystem>
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"
using namespace std;

//Globals
SDL_Window* g_window = nullptr;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;
SDL_Renderer* g_renderer = nullptr;
//SDL_Texture* g_texture = nullptr;
//Texture2D* g_texture = nullptr;




//Function prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
//SDL_Texture* LoadTextureFromFile(string path);
//void FreeTexture();






int main(int argc, char* args[])
{
	//check if sdl was setup correctly
	if (InitSDL())
	{

		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
		//set the time
		g_old_time = SDL_GetTicks();


		bool quit = false;

		//game loop
		while (!quit)
		{
			Render();
			quit = Update();
		}

	}

	CloseSDL();

	return 0;
}

bool InitSDL()
{
	//Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//setup passed so create window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

		if (g_renderer != nullptr)
		{
			//init PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
			
			////load the background texture
			//g_texture = new Texture2D(g_renderer);
			//if (!g_texture->LoadFromFile("Images/test.bmp"))
			//{
			//	return false;
			//}

		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}

		//did the window get created?
		if (g_window == nullptr)
		{
			//window failed
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
		return true;
	}
}

void CloseSDL()
{
	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	////clear the texture
	//FreeTexture();
	
	//destroy the game screen manager
	delete game_screen_manager;
	game_screen_manager = nullptr;
	
	//release the renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

	//release the texture
	//delete g_texture;
	//g_texture = nullptr;


	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool Update()
{

	Uint32 new_time = SDL_GetTicks();


	//Event handler
	SDL_Event e;
	
	//get events
	SDL_PollEvent(&e);

	//handle the events
	switch (e.type)
	{
		//click the X to quit
	case SDL_QUIT:
		return true;
		break;
	}
	
	game_screen_manager->Update(((float)new_time - g_old_time) / 1000.0f, e);

	g_old_time = new_time;

	return false;
}

void Render()
{
	//Clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	//g_texture->Render(Vector2D(), SDL_FLIP_NONE);

	game_screen_manager->Render();

	//update the screen
	SDL_RenderPresent(g_renderer);

}

//SDL_Texture* LoadTextureFromFile(string path)
//{
//	//remove memory used for a previous texture
//	FreeTexture();
//
//	SDL_Texture* p_texture = nullptr;
//
//	//load the image
//	SDL_Surface* p_surface = IMG_Load(path.c_str());
//	if (p_surface != nullptr)
//	{
//		//create the texture from the pixels on the surface
//		p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
//		if (p_texture == nullptr)
//		{
//			cout << "Unable to create texture from surface. Error: " << SDL_GetError();
//		}
//		SDL_FreeSurface(p_surface);
//
//	}
//	else
//	{
//		cout << "Unable to create texture from surface. Error: " << IMG_GetError();
//	}
//
//	//return the texture
//	return p_texture;
//
//}

//void FreeTexture()
//{
//	//check if texture exists before removing it
//	if (g_texture != nullptr)
//	{
//		SDL_DestroyTexture(g_texture);
//		g_texture = nullptr;
//	}
//}