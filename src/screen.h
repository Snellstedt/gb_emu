#include <SDL2/SDL.h> //sdl stuffs
#include <SDL/SDL_ttf.h> //sdl stuffs

#include <iostream> //std io stuffs cin cout
#include <cstdlib> //exit

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class GB_Screen{
public:

	//custom constructor
	GB_Screen(){

		//window we will be rendering to
		gWindow = NULL;

		//surface the window holds
		screenSurface = NULL;

		//The image we will load and show on the screen
		gHelloWorld = NULL;

		gRegInfo = NULL;

		textColor = {0,0,0};



		//initialize SDL
		if(SDL_Init(SDL_INIT_VIDEO) < 0){
			std::cerr << "SDL could not be initialized! Error: " << SDL_GetError() << '\n';
			exit(1);
		}
		//initialize font support
		if(TTF_Init() < 0){
			std::cerr << "SDL_TTF could not be initialized! Error: " << SDL_GetError() << '\n';
			exit(1);
		}

		//create window
		gWindow = SDL_CreateWindow("gb_emu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
					SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if(gWindow == NULL){
			std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << '\n';
			exit(1);
		}

		//get window surface
		screenSurface = SDL_GetWindowSurface(gWindow);

		//Load splash image
   		gHelloWorld = SDL_LoadBMP( "media/Tetris.bmp" );
	    if(!gHelloWorld){
	        std::cerr <<  "Unable to load image! SDL Error: " << SDL_GetError() << '\n';
	        exit(1);
	    }

	    	//debug stuff

	    TTF_Font * Sans = TTF_OpenFont("media/FreeSans.ttf", 24);
		//Fill the surface white
		SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
		

		//
		//Apply the image
        SDL_BlitSurface( gHelloWorld, NULL, screenSurface, NULL );		
		//Update the surface
		SDL_UpdateWindowSurface( gWindow );

		//Wait two seconds

	}

	void GB_render_frame(){
		//start screen at 

		//for each line
		

	}

	//custonm destructorreal
	~GB_Screen(){
	    //Deallocate surface
	    SDL_FreeSurface( gHelloWorld );
	    gHelloWorld = NULL;

	    //Destroy window
	    SDL_DestroyWindow( gWindow );
	    gWindow = NULL;

	    //Quit SDL subsystems
	    SDL_Quit();
	}

private:
	
	//window we will be rendering to
	SDL_Window * gWindow;

	//surface the window holds
	SDL_Surface * screenSurface;

	SDL_Surface* gHelloWorld;

	//holds register info
	SDL_Surface * gRegInfo;

	SDL_Color textColor;



};