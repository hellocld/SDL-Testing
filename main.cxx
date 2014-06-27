// 
// Program:		main.cxx
// Author:		Chris Langford
// Date:		06/27/14
// Description:		A simple program to test SDL2 with cldECS
//

#include <SDL2/SDL.h>

int main (int argc, char[] argv) {
	//just quick-pasted this from the Factory; that shouldn't be
	//initializing SDL; keeping it here makes it easier to quit when things
	//don't even start
	//initialize SDL2
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		//SDL_Init failed, so spit out an error to the terminal and set
		//the ProgramStatus component in the programUtility entity to
		//"ABORT"
		std::cerr<<"SDL_Init ERROR: "<<SDL_GetError()<<std::endl;
		return 1;
	}
}
