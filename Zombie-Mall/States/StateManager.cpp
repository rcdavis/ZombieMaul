
#include "StateManager.h"

#include <SFML/Graphics/RenderTarget.hpp>

StateManager::StateManager() :
	mStates(),
	mPendingState(),
	mPendingChange(State::NONE)
{}

StateManager::~StateManager() {}

void StateManager::ClearStates()
{
	for (auto iter = std::rbegin(mStates); iter != std::rend(mStates); ++iter)
	{
		(*iter)->Exit();
	}

	mStates.clear();
}

void StateManager::PushState(std::unique_ptr<IState> state)
{
	if (state)
	{
		mPendingState = std::move(state);
		mPendingChange = State::PUSH;
	}
}

void StateManager::PopState()
{
	if (!mStates.empty())
	{
		mPendingChange = State::POP;
	}
}

void StateManager::ClearAndSetState(std::unique_ptr<IState> state)
{
	if (state)
	{
		mPendingState = std::move(state);
		mPendingChange = State::SET;
	}
}

void StateManager::ProcessStateChange()
{
	switch (mPendingChange)
	{
	case StateManager::State::PUSH:
		OnPushState();
		break;

	case StateManager::State::POP:
		OnPopState();
		break;

	case StateManager::State::SET:
		OnSetState();
		break;
	}

	mPendingChange = State::NONE;
}

bool StateManager::Input()
{
	if (!std::empty(mStates))
	{
		return mStates.back()->Input();
	}

	return false;
}

void StateManager::Update()
{
	for (auto iter = std::begin(mStates); iter != std::end(mStates); ++iter)
	{
		(*iter)->Update();
	}
}

void StateManager::Render(sf::RenderTarget* renderTarget)
{
	for (auto iter = std::begin(mStates); iter != std::end(mStates); ++iter)
	{
		(*iter)->Render(renderTarget);
	}
}

void StateManager::OnPushState()
{
	if (mPendingState)
	{
		mPendingState->Enter();
		mStates.push_back(std::move(mPendingState));
	}
}

void StateManager::OnPopState()
{
	if (!mStates.empty())
	{
		mStates.back()->Exit();
		mStates.pop_back();
	}
}

void StateManager::OnSetState()
{
	if (mPendingState)
	{
		ClearStates();
		OnPushState();
	}
}