// 
// Program:		physicsEngine.cxx
// Author:		Chris Langford
// Date:		07/06/2014
// Description:		A simple physics engine to move objects around and check
// 			for collisions
//

#include "physicsEngine.h"
#include "../Components/utility.h"
#include "../Components/box.h"
#include "../Components/physics.h"
#include "../CLD-Util/Objects/vector.h"
#include "../CLD-Util/Objects/box.h"
#include "../CLD-Util/Collision/collision-aabb.h"
#include "../CLD-Util/Tools/boxTools.h"
#include <vector>
#include <SDL2/SDL.h>

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
	for(std::vector<int>::iterator i = entitiesPhysics.begin(); i < entitiesPhysics.end(); ++i) {
		//check the physics type
		switch (library->getComponent<SDL_Testing::Physics>(*i)->type) {
			case SDL_Testing::Physics::Type::BALL:
				{
				//create a reference to the ball Box and Physics components
				//this should DRASTICALLY reduce the number of calls to library functions searching for Components
				std::cerr<<"...Acquiring Box and Physics components...\n";
				SDL_Testing::Box& ballBox = *(library->getComponent<SDL_Testing::Box>(*i));
				SDL_Testing::Physics& ballPhysics = *(library->getComponent<SDL_Testing::Physics>(*i));
				//set oldTime to currentTime
				oldTime = currentTime;
				//get the currentTime
				currentTime = SDL_GetTicks();
				//create a "counter" for movement occuring during this frame
				float moveTime = currentTime - oldTime;
				//collect all WALL objects
				std::cerr<<"...Acquiring Walls...\n";
				std::vector<int> walls;
				for(std::vector<int>::iterator w = entitiesPhysics.begin(); w < entitiesPhysics.end(); ++w) {
					if(library->getComponent<SDL_Testing::Physics>(*w)->type == SDL_Testing::Physics::Type::WALL)
						walls.push_back(*w);
				}
				//start a loop that checks for collisions so long as moveTime != 0
				while(moveTime > 0) {
					std::cerr<<"...Checking Collisions...\n";
					//iterate through each of the walls, checking for a collision between it and the BALL
					if(walls.size() > 0) {
						std::cerr<<"...Assigning Initial nearestCollidingWall...\n";
						//store the ID of the WALL
						int nearestCollidingWall = walls[0];
						//store the time of collision (start at 1, which is no collision)
						std::cerr<<"...Assigning Initial collisionTime...\n";
						float collisionTime = 1;
						//store the normals of the potential collision
						std::cerr<<"...Creating Initial normal...\n";
						CLD_Util::Objects::vec2d normal = CLD_Util::Objects::vec2d(0, 0);
						//loop through the walls
						for(std::vector<int>::iterator wallCheck = walls.begin(); wallCheck < walls.end(); ++wallCheck) {
							//check for a collision; if one occurs in a shorter timespan than collisionTime currently stores, store the new time and the wall's ID
							std::cerr<<"...Getting checkTime...\n";
							float checkTime = CLD_Util::Collision_AABB::aabbSweepCheck(ballBox.box,
									ballPhysics.velocity * moveTime,
									library->getComponent<SDL_Testing::Box>(*wallCheck)->box,
									normal);
							if(checkTime < collisionTime) {
								std::cerr<<"...Assigning checkTime and Wall...\n";
								collisionTime = checkTime;
								nearestCollidingWall = (*wallCheck);
							}
						}
						//if collisionTime == 1 (no collision), move the ball the remainder of moveTime
						if(collisionTime == 1) {
							CLD_Util::Tools::boxMove(ballBox.box, ballPhysics.velocity * moveTime);
							//set moveTime to 0, so the loop ends
							moveTime = 0;
						} else {
							//now that we have the nearest collision and collisionTime, we move the ball to the collisionTime, adjust the velocity based on the collision, and subtract collisionTime from moveTime
							CLD_Util::Tools::boxMove(ballBox.box, ballPhysics.velocity * collisionTime);
							moveTime -= collisionTime;
							//adjust the velocity based on the collision normal
							if((normal.x > 0 && ballPhysics.velocity.x < 0)||(normal.x < 0 && ballPhysics.velocity.x > 0))
								ballPhysics.velocity.x *= -1;
							if((normal.y > 0 && ballPhysics.velocity.y < 0)||(normal.y < 0 && ballPhysics.velocity.y > 0))
								ballPhysics.velocity.y *= -1;

						}
						//this will repeat over and over until all collisions have been accounted for
					} else {
						//there aren't any walls, so
						//move the ball
						CLD_Util::Tools::boxMove(ballBox.box, ballPhysics.velocity * moveTime);
						moveTime = 0;
					}
				}
				break;
				}
			case SDL_Testing::Physics::Type::PARTICLE:
				//just move it, since particles don't react to
				//physics stuff in this demo
				break;

		}
	}
}

//-----------------------------------------------------------------------------
// Shutdown
//-----------------------------------------------------------------------------

void SDL_Testing::PhysicsEngine::shutdown() {
	//nada
}
