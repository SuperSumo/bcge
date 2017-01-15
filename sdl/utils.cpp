#include <string>
#include <fstream>
#include <string>
#include <sstream>

#include <SDL2/SDL.h>

#include "utils.h"

using namespace std;

bool read_text_file(string filename, string& buffer)
{
	// Open the file
	ifstream file(filename.c_str());
	if(!file.is_open())
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"read_text_file - unable to read %s", filename.c_str());
		return false;
	}

	// Read the file
	stringstream fileData;
	fileData << file.rdbuf();
	file.close();
	file.clear();

	// Set the buffer
	buffer = string(fileData.str());
	return true;
}
