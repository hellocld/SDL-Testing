// 
// Program:		render.h
// Author:		Chris Langford
// Date:		06/28/14
// Description:		The Render system simply finds any renderable objects
// 			copies them to the screen
//

#include "render.h"
#include "../Components/texture.h"
#include "../Components/box.h"
#include "../Components/utility.h"
#include "../Components/window.h"
#include "../CLD-Util/Tools/boxTools.h"
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
//-----------------------------------------------------------------------------
// Initialization
//-----------------------------------------------------------------------------

void SDL_Testing::Render::init() {
	std::cerr<<"...Render Init...\n";
	//get a vector of all entities in the Library
	std::vector<int> allEntities = library->allEntityIDs();
	
	//get the Utility and Window 
	for(std::vector<int>::iterator i = allEntities.begin(); i < allEntities.end(); ++i) {
		if(library->hasComponent<SDL_Testing::Utility>(*i)){
			entityUtility = *i;
			std::cerr<<"entityUtility ID == "<<entityUtility<<std::endl;
		}
		if(library->hasComponent<SDL_Testing::Window>(*i)){
			entityWindow = *i;
			std::cerr<<"entityWindow ID == "<<entityWindow<<std::endl;
		}
	};
	
	//iterate through all entities in the Library
	for(std::vector<int>::iterator i = allEntities.begin(); i < allEntities.end(); ++i) {
		//check to see if entity i has a position, texture and box component
		if(library->hasComponent<SDL_Testing::Texture>(*i) && library->hasComponent<SDL_Testing::Box>(*i)) {
			//if so, add it to entitiesRender
			entitiesRender.push_back(*i);
			std::cerr<<"Entity ID "<<*i<<" added to entitiesRender\n";
		}
	}
}

//-----------------------------------------------------------------------------
// Update
//-----------------------------------------------------------------------------

void SDL_Testing::Render::update() {
	std::cerr<<"...Render Update...\n";
	//just in case something went wrong and we already aborted, return
	if(library->getComponent<SDL_Testing::Utility>(entityUtility)->programState == SDL_Testing::Utility::states::ABORT)
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
		//create a SDL_Rect from the box
		SDL_Rect tempRect;
		CLD_Util::Objects::Box tempBox = library->getComponent<SDL_Testing::Box>(*i)->box;
		tempRect.x = tempBox.x;
		tempRect.y = tempBox.y;
		tempRect.w = tempBox.w;
		tempRect.h = tempBox.h;
		//copy the texture to the renderer
		if(SDL_RenderCopy(library->getComponent<SDL_Testing::Window>(entityWindow)->sdlRenderer, library->getComponent<SDL_Testing::Texture>(*i)->sdlTex, NULL, &tempRect) != 0) {
			//something went wrong, ABORT
			std::cerr<<"SDL_RenderCopy() ERROR: "<<SDL_GetError()<<std::endl;
			library->getComponent<SDL_Testing::Utility>(entityUtility)->programState = SDL_Testing::Utility::states::ABORT;
			return;
		}
	}
	//update the screen
	std::cerr<<"...Render Updating the Screen...\n";
	SDL_RenderPresent(library->getComponent<SDL_Testing::Window>(entityWindow)->sdlRenderer);
	std::cerr<<"...Render Screen Updated...\n";
}

//-----------------------------------------------------------------------------
// Shutdown
//-----------------------------------------------------------------------------

void SDL_Testing::Render::shutdown() {
	std::cerr<<"...Render Shutdown (does nothing)...\n";
	//doesn't do anything
}
