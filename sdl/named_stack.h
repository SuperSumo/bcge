#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <map>

#include "defines_constants_typedefs.h"

using namespace std;

template <typename T> class NamedStack
{
    public:

		virtual ~NamedStack();

        // Map operations
        T* add(string key); // Add to map. Return 0 on failure
        T* get(string key=string()); // Top of stack by default, 0 on failure
		bool exists(string key); // If the key exists in the map
		size_t size();

		// Stack operations
		string top(); // Return the *name* of the top input.
		T* push(string key);
		void pop();
		void clear(); // Clear the stack, not the map.

	protected:

		StringVec _stack; // The internal "stack" of keys.
		map<string, T*> _map; // The key->element map.
};

#endif
