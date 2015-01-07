#include <string>
#include <fstream>
#include <sstream>

#include <SDL2/SDL.h>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>

#include "config.h"

using namespace std;

Config::~Config()
{
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Config::~Config()");
	// Write back out to the config file
	write();
}

void Config::open(string filename)
{
	// Read in the json config file
	ifstream configFile(filename.c_str());
	if(configFile.fail())
	{
		// If the file opening failed, write a new file and open it
		ofstream createFile(filename.c_str());
		createFile.close();
		configFile.open(filename.c_str());
	}

	// Read from the stream into a buffer
	stringstream buffer;
	buffer << configFile.rdbuf();

	// Parse it using jsoncpp (https://github.com/open-source-parsers/jsoncpp)
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(buffer.str(), root);
	if (!parsingSuccessful)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Bad config file: %s\n",
			reader.getFormatedErrorMessages().c_str());
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Erasing config file: %s\n",
			filename.c_str());
		ofstream eraseFile(filename.c_str());
		eraseFile.close();
		configFile.open(filename.c_str());
	}
}

void Config::write(string filename)
{
	Json::StyledWriter writer;
	ofstream configFile(filename.c_str());
	configFile << writer.write(root);
}
