#include "Utils/Debug.h"

#include <array>

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Vertex.hpp"

namespace Debug {
	void DrawCapsule(sf::RenderTarget* const renderTarget, const Capsule& capsule, const sf::Color& color) {
		const sf::Vector2f offset(capsule.radius, capsule.radius);

		sf::CircleShape start(capsule.radius);
		start.setPosition(capsule.start - offset);
		start.setFillColor(color);
		renderTarget->draw(start);

		sf::CircleShape end(capsule.radius);
		end.setPosition(capsule.end - offset);
		end.setFillColor(color);
		renderTarget->draw(end);

		const std::array line = {
			sf::Vertex {
				.position = capsule.start,
				.color = color
			},
			sf::Vertex {
				.position = capsule.end,
				.color = color
			}
		};
		renderTarget->draw(std::data(line), std::size(line), sf::PrimitiveType::Lines);
	}
}
