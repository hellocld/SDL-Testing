//
// Program:		position.h
// Author:		Chris Langford
// Date:		06/27/14
// Description:		A basic 2d position component. Just contains x and y values.
//

#ifndef POSITION_H
#define POSITION_H

#include "../CLD-ECS/component.h"

namespace SDL_Testing {
	class Position : public CLD_ECS::Component {
		public:
			float x;
			float y;
	};
}

#endif
