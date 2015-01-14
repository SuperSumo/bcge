#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#include <jsoncpp/json/json.h>

using namespace std;

class Config
{
	public:

		~Config();

		void open(string filename="config.json");
		void write(string filename="config.json");
		Json::Value root;
};

#endif
