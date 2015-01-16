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

		// Add a new T to the collection and return it. Return 0 on failure.
		T* add(string key);

		// Get the top of the stack if not specified. Return 0 on failure.
        virtual T* get(string key=string());
		bool exists(string key); // If the key exists in the map.
		size_t size();
		string top(); // Return the name of the top input.

		// Stack operations
		T* push(string key);
		void pop();
		void clear(); // Clear the stack, not the map.

	protected:

		// A typemap for the internal map
		typedef map<string, T*> _StacktypeMap;

		StringVec _stack; // The internal "stack" of keys.
		_StacktypeMap _map; // The key->element map.
};

#endif
