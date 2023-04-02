
#include "InputManager.h"

InputManager InputManager::Global;

InputManager::InputManager()
{
    mPrevKeyboardState.fill(false);
    mCurKeyboardState.fill(false);
}

InputManager::~InputManager() {}

void InputManager::Poll()
{
    //std::copy(std::cbegin(mCurKeyboardState), std::cend(mCurKeyboardState), std::begin(mPrevKeyboardState));
    memcpy(std::data(mPrevKeyboardState), std::data(mCurKeyboardState), std::size(mCurKeyboardState));

    for (auto i = 0; i < sf::Keyboard::KeyCount; ++i)
        mCurKeyboardState[i] = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i);
}

bool InputManager::IsKeyPressed(sf::Keyboard::Key key) const
{
    return mCurKeyboardState[key] && !mPrevKeyboardState[key];
}

bool InputManager::IsKeyDown(sf::Keyboard::Key key) const
{
    return mCurKeyboardState[key];
}

bool InputManager::IsKeyReleased(sf::Keyboard::Key key) const
{
    return !mCurKeyboardState[key] && mPrevKeyboardState[key];
}
