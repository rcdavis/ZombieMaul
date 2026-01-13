#include "Input/Input.h"

#include <array>
#include <cstdint>

namespace Input {
	static std::array<bool, sf::Keyboard::KeyCount> mPrevKeyboardState;
	static std::array<bool, sf::Keyboard::KeyCount> mCurKeyboardState;

	void Poll() {
		std::copy(std::cbegin(mCurKeyboardState), std::cend(mCurKeyboardState), std::begin(mPrevKeyboardState));

		for (auto i = 0; i < sf::Keyboard::KeyCount; ++i)
			mCurKeyboardState[i] = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i);
	}

	bool IsKeyPressed(sf::Keyboard::Key key) {
		return mCurKeyboardState[(uint32_t)key] && !mPrevKeyboardState[(uint32_t)key];
	}

	bool IsKeyDown(sf::Keyboard::Key key) {
		return mCurKeyboardState[(uint32_t)key];
	}

	bool IsKeyReleased(sf::Keyboard::Key key) {
		return !mCurKeyboardState[(uint32_t)key] && mPrevKeyboardState[(uint32_t)key];
	}
}
