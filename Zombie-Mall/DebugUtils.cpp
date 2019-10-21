
#include "DebugUtils.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Vertex.hpp>

void DrawCapsule(sf::RenderTarget* renderTarget, const Capsule& capsule, const sf::Color& color)
{
	const sf::Vector2f offset(capsule.GetRadius(), capsule.GetRadius());

	sf::CircleShape start(capsule.GetRadius());
	start.setPosition(capsule.GetStart() - offset);
	start.setFillColor(color);
	renderTarget->draw(start);

	sf::CircleShape end(capsule.GetRadius());
	end.setPosition(capsule.GetEnd() - offset);
	end.setFillColor(color);
	renderTarget->draw(end);

	const sf::Vertex line[] =
	{
		sf::Vertex(capsule.GetStart(), color),
		sf::Vertex(capsule.GetEnd(), color)
	};
	renderTarget->draw(line, 2, sf::Lines);
}