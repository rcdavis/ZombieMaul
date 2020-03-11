
#ifndef _DEBUG_UTILS_H_
#define _DEBUG_UTILS_H_

#include "Capsule.h"
#include "Circle.h"

namespace sf
{
	class RenderTarget;
	class Color;
}

void DrawCapsule(sf::RenderTarget* const renderTarget, const Capsule& capsule, const sf::Color& color);

#endif // !_DEBUG_UTILS_H_
