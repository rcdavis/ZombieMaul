#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <optional>

#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Time.hpp"

class Animation {
public:
	struct Frame {
		sf::IntRect rect;
		sf::Time timestamp;
		sf::Time duration;
	};

public:
	Animation();
	~Animation();

	const std::string& GetName() const { return mName; }

	const Frame& GetFrame(sf::Time timestamp) const;

	const sf::Time& GetDuration() const { return mDuration; }

	const bool IsLooping() const { return mIsLooping; }

	static std::optional<Animation> Load(const std::filesystem::path& filepath);

private:
	std::string mName;

	std::vector<Frame> mFrames;

	sf::Time mDuration;

	bool mIsLooping;
};
