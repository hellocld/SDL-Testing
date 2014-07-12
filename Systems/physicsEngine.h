// 
// Program:		physicsEngine.h
// Author:		Chris Langford
// Date:		07/06/2014
// Description:		A simple physics engine to move objects around and check
// 			for collisions
//

#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include "../CLD-ECS/system.h"
#include <vector>

namespace SDL_Testing {
	class PhysicsEngine : public CLD_ECS::System {
		public:
			void init();
			void update();
			void shutdown();

			int entityUtility;
			std::vector<int> entitiesPhysics;
			unsigned int currentTime = 0;
			unsigned int oldTime = 0;
	};
}

#endif
