// 
// Program:		factory.cxx
// Author:		Chris Langford
// Date:		06/27/14
// Description:		The Factory is in charge of starting SDL2, creating a
// 			Window and Renderer, loading and creating our Sprite,
// 			and in the end closing everything down appropriately.
//

#include "factory.h"
#include "../Components/utility.h"
#include "../Components/window.h"
#include "../Components/position.h"
#include "../Components/texture.h"
#include "../Components/box.h"
#include "../Components/physics.h"
#include "../CLD-Util/Objects/box.h"

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

//-----------------------------------------------------------------------------
// Initiation
//-----------------------------------------------------------------------------

void SDL_Testing::Factory::init() {
	//find our utility entity created by the World; we'll need it in case an
	//error occurs or user input is recieved
	for(std::vector<int>::iterator i = library->allEntityIDs().begin(); i < library->allEntityIDs().end(); ++i) {
		if(library->hasComponent<SDL_Testing::Utility>(*i))
			entityUtility = *i;
	};
	
	//create an entity to store the Window and Renderer in
	entityWindow = library->createEntity();

	//add the window component to it
	library->addComponent(entityWindow, new SDL_Testing::Window());
	
	//create the SDL_Window and SDL_Renderer in entityWindow
	library->getComponent<SDL_Testing::Window>(entityWindow)->sdlWindow = SDL_CreateWindow("SDL Testing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	//check to make sure this worked
	if(library->getComponent<SDL_Testing::Window>(entityWindow)->sdlWindow == NULL) {
		//creating the window failed, so report the error, set
		//ProgramStatus to "ABORT", and return from init()
		std::cerr<<"SDL_CreateWindow() ERROR: "<<SDL_GetError()<<std::endl;
		library->getComponent<SDL_Testing::Utility>(entityUtility)->programState = SDL_Testing::Utility::states::ABORT;
		return;
	}
	library->getComponent<SDL_Testing::Window>(entityWindow)->sdlRenderer = SDL_CreateRenderer(library->getComponent<SDL_Testing::Window>(entityWindow)->sdlWindow, -1, 0);
	//check to make sure this worked
	if(library->getComponent<SDL_Testing::Window>(entityWindow)->sdlRenderer == NULL) {
		//creating the window failed, so report the error, set
		//ProgramStatus to "ABORT", and return from init()
		std::cerr<<"SDL_CreateRenderer() ERROR: "<<SDL_GetError()<<std::endl;
		library->getComponent<SDL_Testing::Utility>(entityUtility)->programState = SDL_Testing::Utility::states::ABORT;
		return;
	}
	
	//if creating the window and renderer was successful, it's time to
	//create the sprite entity 
	entitySprite = library->createEntity();
	//give it a box component to describe it's location and size
	library->addComponent(entitySprite, new SDL_Testing::Box(CLD_Util::Objects::Box(0, 0, 8, 8)));
	//give it a physics component
	library->addComponent(entitySprite, new SDL_Testing::Physics());
	library->addComponent(entitySprite, new SDL_Testing::Texture());
	//create a temporary surface to use for creating the Texture
	SDL_Surface* tempSurf = SDL_LoadBMP("cldECS_logo.bmp");
	if(tempSurf == NULL) {
		//couldn't load the bitmap, so report it and return from init()
		std::cerr<<"SDL_LoadBMP() ERROR: "<<SDL_GetError()<<std::endl;
		library->getComponent<SDL_Testing::Utility>(entityUtility)->programState = SDL_Testing::Utility::states::ABORT;
		return;
	}
	//use tempSurf to create the texture for entitySprite
	library->getComponent<SDL_Testing::Texture>(entitySprite)->sdlTex = SDL_CreateTextureFromSurface(library->getComponent<SDL_Testing::Window>(entityWindow)->sdlRenderer, tempSurf);
	if(library->getComponent<SDL_Testing::Texture>(entitySprite)->sdlTex == 0) {
		//something went wrong, so report it and return from init()
		std::cerr<<"SDL_CreateTextureFromSurface() ERROR: "<<SDL_GetError()<<std::endl;
		library->getComponent<SDL_Testing::Utility>(entityUtility)->programState = SDL_Testing::Utility::states::ABORT;
		return;
	}

	//free tempSurface, as we're no longer using it
	SDL_FreeSurface(tempSurf);

}

//-----------------------------------------------------------------------------
// Update
//-----------------------------------------------------------------------------

void SDL_Testing::Factory::update() {
	//don't do anything
}

//-----------------------------------------------------------------------------
// Shutdown
//-----------------------------------------------------------------------------


void SDL_Testing::Factory::shutdown() {
	//destroy the sprite
	SDL_DestroyTexture(library->getComponent<SDL_Testing::Texture>(entitySprite)->sdlTex);
	library->destroyEntity(entitySprite);
	//destroy the renderer
	SDL_DestroyRenderer(library->getComponent<SDL_Testing::Window>(entityWindow)->sdlRenderer);
	//destroy the window
	SDL_DestroyWindow(library->getComponent<SDL_Testing::Window>(entityWindow)->sdlWindow);
	library->destroyEntity(entityWindow);
}
