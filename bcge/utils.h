#ifndef UTILS_H_
#define UTILS_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
using namespace std;

void error(const char* errStr);
string display_matrix(glm::mat4 a);
bool read_text_file(string filename, string& buffer);

#endif
