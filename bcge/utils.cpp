#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "utils.h"

using namespace std;

bool read_text_file(string filename, string& buffer)
{
	// Open the file
	ifstream file(filename.c_str());
	if(!file.is_open())
	{
		cerr << "Error! Unable to open file: " << filename.c_str() << endl;
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
