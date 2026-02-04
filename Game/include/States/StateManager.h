#pragma once

#include <vector>
#include <memory>

namespace sf {
	class RenderTarget;
}

class IState;

class StateManager {
private:
	enum class Action : uint8_t {
		None,
		Push,
		Pop,
		Set
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

private:
	std::vector<std::unique_ptr<IState>> mStates;

	std::unique_ptr<IState> mPendingState;
	Action mPendingAction;
};
