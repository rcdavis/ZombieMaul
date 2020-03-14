
#ifndef _STATE_MANAGER_H_
#define _STATE_MANAGER_H_

#include <vector>
#include <memory>

#include "IState.h"

class StateManager
{
private:
	enum class State
	{
		PUSH,
		POP,
		SET,
		NONE
	};

public:
	StateManager();
	~StateManager();

	void ClearStates();

	void PushState(std::unique_ptr<IState> state);
	void PopState();
	void ClearAndSetState(std::unique_ptr<IState> state);

	void ProcessStateChange();

	bool Input();
	void Update();
	void Render(sf::RenderTarget* const renderTarget);

	IState* GetCurrentState();

private:
	StateManager(const StateManager&) = delete;
	StateManager& operator=(const StateManager&) = delete;

	void OnPushState();
	void OnPopState();
	void OnSetState();

	std::vector<std::unique_ptr<IState> > mStates;

	std::unique_ptr<IState> mPendingState;
	State mPendingChange;
};

#endif // !_STATE_MANAGER_H_
