// 
// Program:		utility.h
// Author:		Chris Langford
// Date:		06/27/14
// Description:		Basic utility component. Used by World and System to
// 			control the main loop
//

#ifndef UTILITY_H
#define UTILITY_H

#include "../CLD-ECS/component.h"

namespace SDL_Testing {
	class Utility : public CLD_ECS::Component {
		public:
			//enums for all possible program states
			enum states {INIT, UPDATE, SHUTDOWN, ABORT};
			//the actual state
			states programState;
	};
}

#endif
