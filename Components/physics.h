// 
// Program:		physics.h
// Author:		Chris Langford
// Date:		07/06/2014
// Description:		Basic physics component used by the physics system
//


#ifndef PHYSICS_H
#define PHYSICS_H

#include "..CLD-ECS/component.h"

namespace SDL_Testing {
	class Physics : public CLD_ECS::Component {
		public:
			CLD_Util::Objects::vec2d velocity;
	}
}

#endif

