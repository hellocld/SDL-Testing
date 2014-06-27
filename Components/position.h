//
// Program:		position.h
// Author:		Chris Langford
// Date:		06/27/14
// Description:		A basic 2d position component. Just contains x and y values.
//

#include "../CLD-ECS/component.h"

namespace SDL_Testing {
	class Position : public CLD_ECS::Component {
		public:
			float x;
			float y;
	};
}

