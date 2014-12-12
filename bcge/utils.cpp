#include "utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;

void error(const char* errStr)
{
	cerr << errStr << endl;
	throw runtime_error(errStr);
}

string display_matrix(glm::mat4 a)
{
	stringstream ss;
	ss.precision(2);
	ss << showpos << fixed;
	for (int r=0; r<4; r++)
	{
		ss << "\n";
		for (int c=0; c<4; c++)
			ss << " " << a[r][c];
	}
	return ss.str();
}

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
