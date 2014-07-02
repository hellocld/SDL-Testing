// 
// Program:		render.h
// Author:		Chris Langford
// Date:		06/28/14
// Description:		The Render system simply finds any renderable objects
// 			copies them to the screen
//
#ifndef RENDER_H
#define RENDER_H

#include "../CLD-ECS/system.h"
#include <vector>

namespace SDL_Testing {
	class Render : public CLD_ECS::System {
		public:
			void init();
			void update();
			void shutdown();
			
			//vector of renderable entities
			std::vector<int> entitiesRender;	
			//ID of the window entity
			int entityWindow;
			//entity to link to the Utility entity
			int entityUtility;
	};
}

#endif
