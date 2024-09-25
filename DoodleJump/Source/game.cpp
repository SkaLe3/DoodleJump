
#include "Core/Base/MyFramework.h"
#include "Core/Base/Log.h"

#include <sstream>
#include <string>


int main(int argc, char* argv[])
{
	uint32_t width, height;
	uint32_t minWidth = 300, minHeight = 600;
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
			else
			{
				return 1;
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

	}
	else
	{
		width = 300;
		height = 800;
		fullscreen = false;
	}
	return run(new MyFramework(width, height, fullscreen));
}
