#pragma once

#include "Renderer/Animation.h"

class Identifier;

namespace AnimationManager {
	const Animation* Load(const Identifier& id);
}
