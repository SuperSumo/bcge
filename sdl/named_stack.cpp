#include <string>
#include <map>

#include <SDL2/SDL.h>

#include "defines_constants_typedefs.h"
#include "named_stack.h"

using namespace std;

template <typename T> NamedStack<T>::~NamedStack()
{
	// Delete all the elements in the map
	typename map<string, T*>::iterator i = _map.begin();
	for (; i != _map.end(); ++i)
		delete i->second;
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
		"NamedStack::~NamedStack()");
}

template <typename T> T* NamedStack<T>::add(string key)
{
	// If the key exists, throw an error and return 0
	if (_map.find(key) != _map.end())
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"NamedStack::add() - Key %s already exists.",
			key.c_str());
		return 0;
	}

	// Don't allow adding a zero-length string as key
	if (key.length()==0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"NamedStack::add() - Key lenth must be > 0");
		return 0;
	}

	// Add a new item and return it
	_map[key] = new T;
	return _map[key];
}

template <typename T> T* NamedStack<T>::get(string key)
{
	// If the key doesn't exist, return 0
	if (_map.find(key) == _map.end())
		return 0;

	// If no string is specified, return the top of the stack
	if (key.length()==0)
		return _map[_stack.back()];

	// Otherwise, return the specified element
	return _map[key];
}

template <typename T> bool NamedStack<T>::exists(string key)
{
	return bool(_map.count(key));
}

template <typename T> size_t NamedStack<T>::size()
{
	return _stack.size();
}

template <typename T> string NamedStack<T>::top()
{
	if (size() <= 0)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
			"NamedStack::top() - Stack is empty");
		return string();
	}
	return _stack.back();
}

template <typename T> T* NamedStack<T>::push(string key)
{
	// If the key is already in the stack, error and return 0
	bool exists = false;
	for (StringVec::iterator i = _stack.begin(); i != _stack.end(); ++i)
		exists |= (*i == key);
	if (exists)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"NamedStack::push() - Key %s already exists.",
			key.c_str());
		return 0;
	}

	// Add an element pointer to the top of the stack and return it
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
		"NamedStack::push() - Pushing %s to top of stack",
		key.c_str());
	_stack.push_back(key);
	return get(key);
}

template <typename T> void NamedStack<T>::pop()
{
	// If the stack is empty, log a warning
	if (size() <= 0)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
			"NamedStack::pop() - Stack is empty");
		// Return because erasing from an empty set is undefined behavior
		return;
	}

	// Remove the top item from the stack
	_stack.pop_back();
}

template <typename T> void NamedStack<T>::clear()
{
	// Clear the stack, not the map
	_stack.clear();
}

// Explicit instantiation for the Input class. I don't like this, but oh well.
#include "input.h"
template class NamedStack<InputActionMap>;
