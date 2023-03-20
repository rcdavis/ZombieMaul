
#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include <SFML/Window/Keyboard.hpp>

#include <array>

class InputManager
{
public:
    static InputManager Global;

    void Poll();

    bool IsKeyPressed(sf::Keyboard::Key key) const;
    bool IsKeyDown(sf::Keyboard::Key key) const;
    bool IsKeyReleased(sf::Keyboard::Key key) const;

private:
    InputManager();
    ~InputManager();
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    std::array<bool, sf::Keyboard::KeyCount> mPrevKeyboardState;
    std::array<bool, sf::Keyboard::KeyCount> mCurKeyboardState;
};

#endif // !_INPUT_MANAGER_H_
