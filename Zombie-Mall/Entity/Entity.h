
#ifndef _ENTITY_H_
#define _ENTITY_H_

namespace sf
{
	class RenderTarget;
}

class Entity
{
public:
	Entity();
	virtual ~Entity();

	Entity(const Entity&) = default;
	Entity& operator=(const Entity&) = default;

	virtual void Update();
	virtual void Render(sf::RenderTarget* renderTarget);

private:
	
};

#endif // !_ENTITY_H_
