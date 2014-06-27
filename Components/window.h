// 
// Program:		window.h
// Author:		Chris Langford
// Date:		06/27/14
// Description:		Stores the SDL Window variables. Might want to break
// 			this up a bit in the future, but for now this should be
// 			fine.
//

#include "../CLD-ECS/component.h"
#include <SDL2/SDL.h>

namespace SDL_Testing {
	class Window : public CLD_ECS::Component {
		public:
			SDL_Window* sdlWindow = nullptr;
		       	SDL_Renderer* sdlRenderer = nullptr;
	};
}
