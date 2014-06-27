//
// Program:		texture.h
// Author:		Chris Langford
// Date:		06/27/14
// Description:		Component to store a texture copied to the Window by SDL
//

#include "../CLD-ECS/component.h"
#include <SDL2/SDL.h>

namespace SDL_Testing {
	class Texture : public CLD_ECS::Component {
		public:
			SDL_Texture* sdlTex = nullptr;
	};
}
