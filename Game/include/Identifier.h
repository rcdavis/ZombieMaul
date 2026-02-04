#pragma once

#include <stdint.h>

class Identifier {
public:
	constexpr Identifier(uint32_t id, const char* idStr = nullptr) :
		mId(id),
		mIdStr(idStr)
	{}

	constexpr const char* GetIdStr() const { return mIdStr; }
	constexpr uint32_t GetId() const { return mId; }

	constexpr friend bool operator==(const Identifier& first, const Identifier& second) {
		return first.mId == second.mId;
	}

	constexpr friend bool operator!=(const Identifier& first, const Identifier& second) {
		return first.mId != second.mId;
	}

	constexpr friend bool operator<(const Identifier& first, const Identifier& second) {
		return first.mId < second.mId;
	}

	constexpr friend bool operator>(const Identifier& first, const Identifier& second) {
		return first.mId > second.mId;
	}

private:
	uint32_t mId;
	const char* mIdStr;
};

namespace Id::Data {
	constexpr Identifier Guard(0, "res/data/Guard.json");
	constexpr Identifier GuardWalkAnim(1, "res/data/GuardWalkAnim.json");
	constexpr Identifier Level(2, "res/data/Level.json");
	constexpr Identifier Person(3, "res/data/Person.json");
	constexpr Identifier PersonWalkAnim(4, "res/data/PersonWalkAnim.json");
	constexpr Identifier Player(5, "res/data/Player.json");
	constexpr Identifier PlayerWalkAnim(6, "res/data/PlayerWalkAnim.json");
	constexpr Identifier Settings(7, "res/data/Settings.txt");
	constexpr Identifier Zombie(8, "res/data/Zombie.json");
	constexpr Identifier ZombieWalkAnim(9, "res/data/ZombieWalkAnim.json");
	constexpr uint32_t Num = 10;
}

namespace Id::Fonts {
	constexpr Identifier FreeSans(0, "res/fonts/FreeSans.ttf");
	constexpr uint32_t Num = 1;
}

namespace Id::Textures {
	constexpr Identifier Character(0, "res/textures/CharacterSprite.png");
	constexpr Identifier MallMap(1, "res/textures/MallMap.png");
	constexpr Identifier MenuBg(2, "res/textures/MenuBG1.png");
	constexpr Identifier MenuCredits(3, "res/textures/MenuCredits.png");
	constexpr Identifier MenuExit(4, "res/textures/MenuExit.png");
	constexpr Identifier MenuOptions(5, "res/textures/MenuOptions.png");
	constexpr Identifier MenuPlay(6, "res/textures/MenuPlay.png");
	constexpr Identifier MenuPointer(7, "res/textures/MenuPointer.png");
	constexpr Identifier ZombieMaulIcon(8, "res/textures/zombie-maul-icon.png");
	constexpr uint32_t Num = 9;
}
