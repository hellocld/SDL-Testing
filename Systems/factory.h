// 
// Program:		factory.h
// Author:		Chris Langford
// Date:		06/27/14
// Description:		The Factory is in charge of starting SDL2, creating a
// 			Window and Renderer, loading and creating our Sprite,
// 			and in the end closing everything down appropriately.
//

#include "../CLD-ECS/system.h"
#include <SDL2/SDL.h>

namespace SDL_Testing {
	class Factory : public CLD_ECS::System {
		public:
			void init();
			void update();
			void shutdown();

			//entity to store the Window and Renderer in
			int entityWindow;
			//entity to store the sprite in
			int entitySprite;
			//entity to link to the Utility entity
			int entityUtility;
	};
}
