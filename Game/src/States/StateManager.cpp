#include "States/StateManager.h"

#include "States/IState.h"

#include "SFML/Graphics/RenderTarget.hpp"

StateManager::StateManager() :
	mStates(),
	mPendingState(),
	mPendingAction(Action::None)
{}

StateManager::~StateManager() {
	ClearStates();
}

void StateManager::ClearStates() {
	for (auto iter = std::rbegin(mStates); iter != std::rend(mStates); ++iter)
		(*iter)->Exit();

	mStates.clear();
}

void StateManager::PushState(std::unique_ptr<IState> state) {
	if (state) {
		mPendingState = std::move(state);
		mPendingAction = Action::Push;
	}
}

void StateManager::PopState() {
	if (!std::empty(mStates))
		mPendingAction = Action::Pop;
}

void StateManager::ClearAndSetState(std::unique_ptr<IState> state) {
	if (state) {
		mPendingState = std::move(state);
		mPendingAction = Action::Set;
	}
}

void StateManager::ProcessStateChange() {
	switch (mPendingAction) {
	case StateManager::Action::Push:
		OnPushState();
		break;

	case StateManager::Action::Pop:
		OnPopState();
		break;

	case StateManager::Action::Set:
		OnSetState();
		break;
	}

	mPendingAction = Action::None;
}

bool StateManager::Input() {
	if (!std::empty(mStates))
		return mStates.back()->Input();

	return false;
}

void StateManager::Update() {
	for (const auto& state : mStates)
		state->Update();
}

void StateManager::Render(sf::RenderTarget* const renderTarget) {
	for (const auto& state : mStates)
		state->Render(renderTarget);
}

void StateManager::OnPushState() {
	if (mPendingState) {
		mPendingState->Enter();
		mStates.push_back(std::move(mPendingState));
	}
}

void StateManager::OnPopState() {
	if (!std::empty(mStates)) {
		mStates.back()->Exit();
		mStates.pop_back();
	}
}

void StateManager::OnSetState() {
	if (mPendingState) {
		ClearStates();
		OnPushState();
	}
}

IState* StateManager::GetCurrentState() {
	if (!std::empty(mStates))
		return mStates.back().get();

	return nullptr;
}
