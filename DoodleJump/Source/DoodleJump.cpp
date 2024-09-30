
#include "Core/Base/Log.h"
#include "Game.h"

#include <sstream>
#include <string>


int main(int argc, char* argv[])
{
	uint32_t width, height;
	uint32_t minWidth = 200, minHeight = 400;
	bool fullscreen = false;
	if (argc > 1)
	{

		std::string windowSize;
		for (int i = 1; i < argc; i++)
		{
			if (std::string(argv[i]) == "-window" && argc > i + 1)
			{
				windowSize = argv[i + 1];
			}
			else if (std::string(argv[i]) == "-fullscreen")
			{
				fullscreen = true;
				windowSize = "400x800";
			}
		}

		char x;
		std::istringstream iss(windowSize);

		iss >> width >> x >> height;

		if (iss.fail())
		{
			LOG("Failed to set window size");
			return 1;
		}

		if (width < minWidth)
		{
			width = minWidth;
			LOG("Specified window width too low, window width was adjusted to " + std::to_string(width))
		}
		if (height < minHeight)
		{
			height = minHeight;
			LOG("Specified window height too low, window width was adjusted to " + std::to_string(height))
		}
	}
	else
	{
		width = 400;
		height = 800;
		fullscreen = false;
	}


	return run(new Game(width, height, fullscreen, "Content"));
}
