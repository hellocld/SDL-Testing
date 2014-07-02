// 
// Program:		input.h
// Author:		Chris Langford
// Date:		06/29/14
// Description:		Simple system to handle the closeout button (for now)
// 

#ifndef INPUT_H
#define INPUT_H

#include "../CLD-ECS/system.h"

namespace SDL_Testing {
	class Input : public CLD_ECS::System {
		public:
			void init();
			void update();
			void shutdown();

			//entity to store the Window and Renderer in
			int entityWindow;
			//entity to link to the Utility entity
			int entityUtility;
	};
}

#endif
