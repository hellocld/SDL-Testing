// 
// Program:		main.cxx
// Author:		Chris Langford
// Date:		06/27/14
// Description:		A simple program to test SDL2 with cldECS
//

#include "../CLD-ECS/world.h"
#include "Components/utility.h"
#include "Systems/factory.h"
#include "Systems/render.h"
#include <SDL2/SDL.h>

int main (int argc, char[] argv) {
	//initialize SDL2
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		//SDL_Init failed, so spit out an error to the terminal and set
		//the ProgramStatus component in the programUtility entity to
		//"ABORT"
		std::cerr<<"SDL_Init ERROR: "<<SDL_GetError()<<std::endl;
		return 1;
	}

	//if all is well, create a new World
	CLD_ECS::World sdltest;

	//create a Utility entity
	int entityUtility = sdltest.createEntity();
	sdltest.addComponent(sdltest, new SDL_Testing::Utility());

	//add the factory and render systems
	sdltest.addSystem(new SDL_Testing::Factory());
	sdltest.addSystem(new SDL_Testing::Render());

	//initialize the systems
	sdltest.systemsInit();

	//if nothing is wrong, update the systems
	while(sdltest.getComponent<SDL_Testing::Utility>(entityUtility)->programState != SDL_Testing::Utility::ABORT) {
		sdltest.systemsUpdate();
	}

	//all done with updating, so shutdown
	sdltest.systemsShutdown();

	return 0;
}
