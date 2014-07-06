// 
// Program:		physicsEngine.cxx
// Author:		Chris Langford
// Date:		07/06/2014
// Description:		A simple physics engine to move objects around and check
// 			for collisions
//

#include "physicsEngine.h"
#include "../Components/box.h"
#include "../Components/physics.h"
#include "../CLD-Util/Objects/vector.h"
#include "../CLD-Util/Objects/box.h"
#include "../CLD-Util/Collision/collision-aabb.h"
#include <vector>

//-----------------------------------------------------------------------------
// Initialization
//-----------------------------------------------------------------------------

void SDL_Testing::PhysicsEngine::init() {
	//get a vector of all entities in the Library
	std::vector<int> allEntities = library->allEntityIDs();
	
	//get the Utility and Window 
	for(std::vector<int>::iterator i = allEntities.begin(); i < allEntities.end(); ++i) {
		if(library->hasComponent<SDL_Testing::Utility>(*i)){
			entityUtility = *i;
			std::cerr<<"entityUtility ID == "<<entityUtility<<std::endl;
		}
	}
	
	//get all entities with a physics component
	for(std::vector<int>::iterator i = allEntities.begin(); i < allEntities.end(); ++i) {
		if(library->hasComponent<SDL_Testing::Physics>(*i)){
			entitiesPhysics.push_back(*i);
		}
	}
}

//-----------------------------------------------------------------------------
// Update
//-----------------------------------------------------------------------------

void SDL_Testing::PhysicsEngine::update() {
	//one by one, go through entitiesPhysics
	for(std::vector<int>::iterator i = entitiesPhysics::begin(); i < entitiesPhysics.end(); ++i) {
		//check the physics type
		switch (library->getComponent<SDL_Testing::Physics>(*i)->type) {
			case BALL:
				//if it's the ball, we need to check it's
				//movement for collisions with WALLs
				for(std::vector<int>::iterator w = entitiesPhysics::begin(); i < entitiesPhysics.end(); ++w) {
					//make a vector for registering
					//collision normals
					CLD_Util::Objects::vec2d normal;

					//check if w is a WALL type
					if(library->getComponent<SDL_Testing::Physics>(*w)->type == WALL) {
						float collisionTime = aabbSweepCheck(library->getComponent<SDL_Testing::Box>(*i)->box, library->getComponent<SDL_Testing::Physics>(*i)->velocity,
									library->getComponent<SDL_Testing::Box>(*w)->box, normal);

						//if collisionTime is less than
						//1, a collision occured
						if(collisionTime < 1) {
							//move the box to the
							//point of collision
							
						}
					}
				}
				break;
			case PARTICLE:
				//just move it, since particles don't react to
				//physics stuff in this demo

		}
	}
}

//-----------------------------------------------------------------------------
// Shutdown
//-----------------------------------------------------------------------------

void SDL_Testing::PhysicsSystem::shutdown() {
	//nada
}
