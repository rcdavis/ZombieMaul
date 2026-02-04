
#include "Utils/Log.h"
#include "Game.h"

int main(int argc, char** argv) {
	Log::Init();

	Game g;
	g.Run();

	return 0;
}
