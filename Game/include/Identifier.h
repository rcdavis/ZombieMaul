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

namespace Id::Fonts {
	constexpr Identifier FreeSans(0, "res/fonts/FreeSans.ttf");
}
