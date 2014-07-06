//
// Program:		box.h
// Author:		Chris Langford
// Date:		07/06/14
// Description:		A basic Box component
//

#ifndef BOX_H
#define BOX_H

#include "../CLD-Util/Objects/box.h"

namespace SDL_Testing {
	class Box : public CLD_ECS::Component {
		public:
			CLD_Util::Objects::Box box;
	};
}

#endif
