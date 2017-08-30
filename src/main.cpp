// #include <SDL2/SDL.h> //SDL (multimedia)
#include <iostream> //std IO
#include <cstring>
#include <string>
#include <getopt.h>
#include "screen.h"
#include "cpu.h"



int main(int argc, char** args){

	std::string rom_name;
    int c;
    bool debug = false;
    //process command line//////////////////////////////////////////////////////////
    while (1) {
        static struct option long_options[] = {
                { "rom", required_argument, 0, 'r' },
                { "debug", no_argument, 0, 'd'},
                { 0,0,0,0 }
            };
            /*getopt_long stores the option index here*/
            int option_index = 0;
            c = getopt_long(argc, args, "r:d",long_options, &option_index);

            //detect the end of the options
            if (c == -1) break;
 
            switch (c) {
            case 0: //if this option set a flag, do nothing else now
                if (long_options[option_index].flag != 0) break;
                break;
            case 'r':{
            	
            	rom_name = std::string(optarg);
                break;
            }

            case 'd':{
                debug = true;
                break;
            }

            default:
                std::cerr << "You dun goofed\n";
                return 1;
                break;
            }
    }// end while loop
    ///end getopt //////////////////////////////////////////////////////////////////

	GB_CPU gb_cpu(rom_name, debug);
	gb_cpu.reset();

    //Event handler
    SDL_Event e;
	// //load rom
	// //initialize machine
	GB_Screen gb_screen;





	bool quit = false;
	//main loop
	while(!quit){

        
        // //Handle events on queue
	    while(SDL_PollEvent(&e)){
            gb_cpu.tick();
	        // User requests quit
	        if( e.type == SDL_QUIT ){
	            quit = true;
	            }
	    }

	}

	return 0;

}