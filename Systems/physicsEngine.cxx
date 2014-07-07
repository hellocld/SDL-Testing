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
				//create a "counter" for movement occuring during this frame
				float moveTime = 1;
				//collect all WALL objects
				std::vector<int> walls;
				for(std::vector<int>::iterator w = entitiesPhysics::begin(); w < entitiesPhysics.end(); ++w) {
					if(library->getComponent<SDL_Testing::Physics>(*w)->type == WALL)
						walls.push_back(*w);
				}
				//start a loop that checks for collisions so long as moveTime != 0
				while(moveTime > 0) {
					//iterate through each of the walls, checking for a collision between it and the BALL
					//store the ID of the WALL
					int nearestCollidingWall = wall[0];
					//store the time of collision (start at 1, which is no collision)
					float collisionTime = 1;
					//store the normals of the potential collision
					CLD_Util::Objects::vec2d normals;
					//loop through the walls
					for(std::vector<int>::iterator walls = wall::begin(); walls < wall::end(); ++walls) {
						//check for a collision; if one occurs in a shorter timespan than collisionTime currently stores, store the new time and the wall's ID
						float checkTime = CLD_Util::Collision_AABB::aabbSweepCheck(library->getComponent<SDL_Testing::Box>(*i)->box,
								library->getComponent<SDL_Testing::Physics>(*i)->velocity * moveTime,
								library->getComponent<SDL_Testing::Box>(*walls)->box,
								normals);
						if(checkTime < collisionTime) {
							collisionTime = checkTime;
							nearestCollidingWall = (*walls);
						}
					}
					//if collisionTime == 1 (no collision), move the ball the remainder of moveTime
					if(collisionTime == 1) {
						CLD_Util::Tools::boxMove(library->getComponent<SDL_Testing::Box>(*i)->box, library->getComponent<SDL_Testing::Physics>(*i)->velocity * moveTime);
						//set moveTime to 0, so the loop ends
						moveTime = 0;
					} else {
						//now that we have the nearest collision and collisionTime, we move the ball to the collisionTime, adjust the velocity based on the collision, and subtract collisionTime from moveTime
						CLD_Util::Tools::boxMove(library->getComponent<SDL_Testing::Box>(*i)->box, library->getComponent<SDL_Testing::Physics>(*i)->velocity * collisionTime);
						moveTime -= collisionTime;
					}

					//this will repeat over and over until all collisions have been accounted for
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
