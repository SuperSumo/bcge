#ifndef DEFINES_CONSTANTS_TYPEDEFS_H
#define DEFINES_CONSTANTS_TYPEDEFS_H

#include <string>
#include <vector>

using namespace std;

// Defines
#define TITLE "Awesome SDL Game! v0.1"
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define ICON "icon.png"

// Typedefs
typedef unsigned char uchar;
typedef unsigned int uint;
typedef vector<string> StringVec;

// Constants
static const float DT = 0.1f; // How fast the physics is updated (sec)

#endif
