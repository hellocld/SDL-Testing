// 
// Program:		input.cxx
// Author:		Chris Langford
// Date:		06/29/14
// Description:		Simple system to handle the closeout button (for now)
// 

#include "input.h"
#include "../Components/utility.h"
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
//-----------------------------------------------------------------------------
// Initialization
//-----------------------------------------------------------------------------

void SDL_Testing::Input::init() {
	//get a vector of all entities in the Library
	std::vector<int> allEntities = library->allEntityIDs();
	
	//get the Utility
	for(std::vector<int>::iterator i = allEntities.begin(); i < allEntities.end(); ++i) {
		if(library->hasComponent<SDL_Testing::Utility>(*i)){
			entityUtility = *i;
			std::cerr<<"entityUtility ID == "<<entityUtility<<std::endl;
		}
	};
}

//-----------------------------------------------------------------------------
// Update
//-----------------------------------------------------------------------------

void SDL_Testing::Input::update() {
	//variable to hold events
	SDL_Event event;
	//start a loop to poll for events
	while(SDL_PollEvent(&event)){
		//all we want to do is see if someone clicked to close out the window
		if(event.type == SDL_WINDOWEVENT) {
			if(event.window.event == SDL_WINDOWEVENT_CLOSE) {
				//they clicked close, so ABORT
				std::cerr<<"SDL_WINDOWEVENT_CLOSE event triggered! ABORTing...\n";
				library->getComponent<SDL_Testing::Utility>(entityUtility)->programState = SDL_Testing::Utility::ABORT;
			}
		}
	}
}

//-----------------------------------------------------------------------------
// Shutdown
//-----------------------------------------------------------------------------

void SDL_Testing::Input::shutdown() {
	//nothing to do
}
