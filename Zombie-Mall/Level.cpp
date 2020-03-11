
#include "Level.h"

#include "Game.h"

#include "MathUtils.h"
#include "Circle.h"

#include "DebugUtils.h"

Level::Level(Game& game) :
	mCollisionBounds(),
	mGame(game),
	mBGImage(),
	mWidth(0.0f),
	mHeight(0.0f)
{}

Level::~Level() {}

bool Level::LoadLevel()
{
	// TODO: Should be loaded from file and not hard coded.
	auto image = mGame.GetTextureManager().LoadTexture("Resources/Textures/MallMap.png");
	if (image)
	{
		mBGImage.setTexture(*image);
	}

	mWidth = 1600.0f;
	mHeight = 1200.0f;

	mCollisionBounds = CreateCollisionBounds();

	return true;
}

void Level::HandleCollision(Entity* const entity) const
{
	for (const auto& capsule : mCollisionBounds)
	{
		const sf::Vector2f closestPoint = ClosestPointOnALine(capsule.GetStart(), capsule.GetEnd(), entity->GetPosition());
		const Circle testCircle(closestPoint, capsule.GetRadius());
		const Circle entityCircle(entity->GetPosition(), 32.0f);

		if (CircleCollision(testCircle, entityCircle))
		{
			const sf::Vector2f vecDistance = entityCircle.GetPosition() - testCircle.GetPosition();
			const sf::Vector2f testToEntity = Normalize(vecDistance);
			const float pushBackDist = (entityCircle.GetRadius() + testCircle.GetRadius()) - VectorLength(vecDistance);

			entity->Move(testToEntity * pushBackDist);
		}
	}
}

void Level::Render(sf::RenderTarget* const renderTarget)
{
	renderTarget->draw(mBGImage);

#ifdef DEBUG_RENDER
	for (const auto& capsule : mCollisionBounds)
	{
		DrawCapsule(renderTarget, capsule, sf::Color::Green);
	}
#endif // DEBUG_RENDER
}

std::vector<Capsule> Level::CreateCollisionBounds() const
{
	std::vector<Capsule> bounds;

	// Benches
	bounds.push_back(Capsule(sf::Vector2f(600.0f, 200.0f), sf::Vector2f(600.0f, 280.0f), 30.0f));
	bounds.push_back(Capsule(sf::Vector2f(645.0f, 405.0f), sf::Vector2f(720.0f, 405.0f), 30.0f));
	bounds.push_back(Capsule(sf::Vector2f(900.0f, 405.0f), sf::Vector2f(980.0f, 405.0f), 30.0f));
	bounds.push_back(Capsule(sf::Vector2f(1013.0f, 200.0f), sf::Vector2f(1013.0f, 280.0f), 30.0f));

	// Hotdog stands
	bounds.push_back(Capsule(sf::Vector2f(767.0f, 188.0f), sf::Vector2f(767.0f, 265.0f), 45.0f));
	bounds.push_back(Capsule(sf::Vector2f(767.0f, 265.0f), sf::Vector2f(855.0f, 250.0f), 45.0f));

	// Walls
	bounds.push_back(Capsule(sf::Vector2f(540.0f, 880.0f), sf::Vector2f(1050.0f, 880.0f), 40.0f));
	bounds.push_back(Capsule(sf::Vector2f(540.0f, 880.0f), sf::Vector2f(540.0f, 1175.0f), 40.0f));
	bounds.push_back(Capsule(sf::Vector2f(1050.0f, 880.0f), sf::Vector2f(1050.0f, 1175.0f), 40.0f));

	// World WALLS
	bounds.push_back(Capsule(sf::Vector2f(165.0f, 10.0f), sf::Vector2f(1420.0f, 10.0f), 40.0f));
	bounds.push_back(Capsule(sf::Vector2f(165.0f, 10.0f), sf::Vector2f(165.0f, 1000.0f), 40.0f));
	bounds.push_back(Capsule(sf::Vector2f(165.0f, 1020.0f), sf::Vector2f(10.0f, 1020.0f), 40.0f));
	bounds.push_back(Capsule(sf::Vector2f(10.0f, 1020.0f), sf::Vector2f(10.0f, 1230.0f), 40.0f));
	bounds.push_back(Capsule(sf::Vector2f(10.0f, 1220.0f), sf::Vector2f(1595.0f, 1220.0f), 35.0f));
	bounds.push_back(Capsule(sf::Vector2f(1420.0f, 10.0f), sf::Vector2f(1420.0f, 1020.0f), 40.0f));
	bounds.push_back(Capsule(sf::Vector2f(1420.0f, 1020.0f), sf::Vector2f(1595.0f, 1020.0f), 40.0f));
	bounds.push_back(Capsule(sf::Vector2f(1595.0f, 1020.0f), sf::Vector2f(1595.0f, 1230.0f), 40.0f));

	return bounds;
}