
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
        (*iter)->Exit();

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
    if (!std::empty(mStates))
        mPendingChange = State::POP;
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
        return mStates.back()->Input();

    return false;
}

void StateManager::Update()
{
    for (const auto& state : mStates)
        state->Update();
}

void StateManager::Render(sf::RenderTarget* const renderTarget)
{
    for (const auto& state : mStates)
        state->Render(renderTarget);
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
    if (!std::empty(mStates))
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

IState* StateManager::GetCurrentState()
{
    if (!std::empty(mStates))
        return mStates.back().get();

    return nullptr;
}