#ifndef GAME_H_
#define GAME_H_

#include <SFML/Window.hpp>
#include <vector>
using namespace std;

class Manager;
class Keyboard;
class Renderer;
class Camera;
class Object;
class Instance;

class Game
{
	public:

		Game(Manager* manager);
		~Game();

		Manager* get_manager();
		Keyboard* get_keyboard();
		Renderer* get_renderer();
		Camera* get_camera();

		void update(float dt);
		void load();
		void run();
		void toggle_pause();
		void quit();

	private:

		Game();
		Manager* manager;
		bool isRunning, isPaused;
		Keyboard* keyboard;
		Renderer* renderer;
		Camera* camera;
		sf::Clock clock;
		sf::Time time;
		vector<Object*> objects;
		vector<Instance*> instances;
};

#endif /* GAME_H_ */
