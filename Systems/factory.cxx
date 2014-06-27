// 
// Program:		factory.cxx
// Author:		Chris Langford
// Date:		06/27/14
// Description:		The Factory is in charge of starting SDL2, creating a
// 			Window and Renderer, loading and creating our Sprite,
// 			and in the end closing everything down appropriately.
//

#include "factory.h"
//-----------------------------------------------------------------------------
// Initiation
//-----------------------------------------------------------------------------
void SDL_Testing::Factory::init() {
	//find our utility entity created by the World; we'll need it in case an
	//error occurs or user input is recieved
	for(std::vector<int>::iterator i = library->allEntityIDs().begin; i < library->allEntityIDs().end; ++i) {
		if(library->hasComponent<SDL_Testing::Utility>(i))
			entityUtility = i;
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
	library->getComponent<SDL_Testing::Window>(entityWindow)->sdlRenderer = SDL_CreateRenderer(library->getComponent<SDL_Testing::Window(entityWindow)->sdlWindow, -1, 0);
	//check to make sure this worked
	if(library->getComponent<SDL_Testing::Window>(entityWindow)->sdlRenderer == NULL) {
		//creating the window failed, so report the error, set
		//ProgramStatus to "ABORT", and return from init()
		std::cerr<<"SDL_CreateRenderer() ERROR: "<<SDL_GetError()<<std::endl;
		library->getComponent<SDL_Testing::Utility>(entityUtility)->programState = SDL_Testing::Utility::states::ABORT;
		return;
	}
	
	//if creating the window and renderer was successfull, it's time to
	//create the sprite entity and load it's texture
	int entitiySprite = library->createEntity();
	library->addComponent(entitySprite, new SDL_Testing::Position());
	library->addComponent(entitySprite, new SDL_Testing::Texture());
	//set the position x & y to 0, 0
	library->getComponent<SDL_Testing::Position>(entitySprite)->x = 0;
	library->getComponent<SDL_Testing::Position>(entitySprite)->y = 0;
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
	if(library->getComponent<SDL_Testing::Texture(entitySprite)->sdlTex == 0) {
		//something went wrong, so report it and return from init()
		std::cerr<<"SDL_CreateTextureFromSurface() ERROR: "<<SDL_GetError()<<std::endl;
		library->getComponent<SDL_Testing::Utility>(entityUtility)->programState = SDL_Testing::Utility::states::ABORT;
		return;
	}

	//and that should be it!
}


