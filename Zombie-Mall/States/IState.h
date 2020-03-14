
#ifndef _ISTATE_H_
#define _ISTATE_H_

namespace sf
{
	class RenderTarget;
}

class IState
{
public:
	virtual ~IState() {}

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual bool Input() = 0;
	virtual void Update() = 0;
	virtual void Render(sf::RenderTarget* const renderTarget) = 0;
};

#endif // !_ISTATE_H_
