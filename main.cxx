// 
// Program:		main.cxx
// Author:		Chris Langford
// Date:		06/27/14
// Description:		A simple program to test SDL2 with cldECS
//

#include "../CLD-ECS/world.h"
#include "Components/utility.h"
#include "Systems/factory.h"
#include "Systems/input.h"
#include "Systems/render.h"
#include <SDL2/SDL.h>

int main (int argc, char* argv[]) {
	//initialize SDL2
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		//SDL_Init failed, so spit out an error to the terminal  and
		//quit
		std::cerr<<"SDL_Init ERROR: "<<SDL_GetError()<<std::endl;
		return 1;
	}

	//if all is well, create a new World
	CLD_ECS::World sdltest;

	//create a Utility entity
	int entityUtility = sdltest.createEntity();
	sdltest.addComponent(entityUtility, new SDL_Testing::Utility());
	sdltest.getComponent<SDL_Testing::Utility>(entityUtility)->programState = SDL_Testing::Utility::UPDATE;

	//add the factory and render systems
	sdltest.addSystem(new SDL_Testing::Factory());
	sdltest.addSystem(new SDL_Testing::Input());
	sdltest.addSystem(new SDL_Testing::Render());

	//initialize the systems
	sdltest.systemsInit();

	//if nothing is wrong, update the systems
	while(sdltest.getComponent<SDL_Testing::Utility>(entityUtility)->programState != SDL_Testing::Utility::ABORT){
		if(sdltest.getComponent<SDL_Testing::Utility>(entityUtility)->programState == SDL_Testing::Utility::UPDATE)
			std::cerr<<"-programState == UPDATE\n";
		sdltest.systemsUpdate();
	}
	std::cerr<<"-programState == ABORT\n";
	//all done with updating, so shutdown
	sdltest.systemsShutdown();
	
	//shutdown SDL since we're all done
	SDL_Quit();
	return 0;
}
