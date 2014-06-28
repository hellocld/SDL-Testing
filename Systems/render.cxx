// 
// Program:		render.h
// Author:		Chris Langford
// Date:		06/28/14
// Description:		The Render system simply finds any renderable objects
// 			copies them to the screen
//

#include "render.h"
#include <SDL2/SDL.h>

//-----------------------------------------------------------------------------
// Initialization
//-----------------------------------------------------------------------------

void SDL_Testing::Render::init() {
	//get a vector of all entities in the Library
	std::vector<int> allEntities = library->allEntityIDs();
	
	//get the Utility and Window entities
	for(std::vector<int>::iterator i = allEntities().begin; i < allEntities().end; ++i) {
		if(library->hasComponent<SDL_Testing::Utility>(i))
			entityUtility = i;
		if(library->hasComponent<SDL_Testing::Window>(i))
			windowUtility = i;
	};
	
	//iterate through all entities in the Library
	for(std::vector<int>::iterator i = allEntities.begin(); i < allEntities.end(); ++i) {
		//check to see if entity i has a position and texture component
		if(library->hasComponent<SDL_Testing::Texture>(i) && library->hasComponent<SDL_Testing::Position>) {
			//if so, add it to entitiesRender
			entitiesRender.push_back(i);
		}
	}
}

//-----------------------------------------------------------------------------
// Update
//-----------------------------------------------------------------------------

void SDL_Testing::Render::update() {
	//just in case something went wrong and we already aborted, return
	if(library->getComponent<SDL_Testing::Utility>(entityUtility)->programState = SDL_Testing::Utility::states::ABORT)
		return;

	//clear the window
	if(SDL_RenderClear(library->getComponent<SDL_Testing::Window>(entityWindow)->sdlRenderer) != 0) {
		//something went wrong; report and ABORT
		std::cerr<<"SDL_RenderClear() ERROR: "<<SDL_GetError()<<std::endl;
		library->getComponent<SDL_Testing::Utility>(entityUtility)->programState = SDL_Testing::Utility::states::ABORT;
		return;
	}
	//iterate through all renderable entities
	for(std::vector<int>::iterator i = entitiesRender.begin(); i < entitiesRender.end(); ++i) {
		//copy the texture to the renderer
		if(SDL_RenderCopy(library->getComponent<SDL_Testing::Window>(entityWindow)-sdlRenderer, library->getComponent<SDL_Testing::Texture>(i)->sdlTex, NULL, NULL) != 0) {
			//something went wrong, ABORT
			std::cerr<<"SDL_RenderCopy() ERROR: "<<SDL_GetError()<<std::endl;
			library->getComponent<SDL_Testing::Utility(entityUtility)->programState = SDL_Testing::Utility::states::ABORT;
			return;
		}
	}
}

//-----------------------------------------------------------------------------
// Shutdown
//-----------------------------------------------------------------------------

void SDL_Testing::Render::shutdown() {
	//doesn't do anything
}
