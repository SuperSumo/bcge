#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "main_game.h"
#include "../input.h"
#include "../manager.h"
#include "../window.h"

void printProgramLog( GLuint program )
{
	//Make sure name is shader
	if( glIsProgram( program ) )
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );

		//Allocate string
		char* infoLog = new char[ maxLength ];

		//Get info log
		glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
		if( infoLogLength > 0 )
		{
			//Print Log
			printf( "%s\n", infoLog );
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf( "Name %d is not a program\n", program );
	}
}

void printShaderLog( GLuint shader )
{
	//Make sure name is shader
	if( glIsShader( shader ) )
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );

		//Allocate string
		char* infoLog = new char[ maxLength ];

		//Get info log
		glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
		if( infoLogLength > 0 )
		{
			//Print Log
			printf( "%s\n", infoLog );
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf( "Name %d is not a shader\n", shader );
	}
}

MainGame::MainGame(Manager* manager):
	Game(manager)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "MainGame::MainGame()");

	// TODO: Delete these
	gProgramID = 0;
	gVertexPos2DLocation = -1;
	gVBO = 0;
	gIBO = 0;
}

MainGame::~MainGame()
{
	glDeleteProgram(gProgramID);
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "MainGame::~MainGame()");
}

bool MainGame::init()
{
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "MainGame::init()");

	// Create an Input
	if (_input)
		delete _input;
	_input = new Input(this);

	// Register all the callbacks
	_input->register_callback("attack", attack);
	_input->register_callback("menu_click", menu_click);
	_input->register_callback("jump", jump);
	_input->register_callback("quit", quit);
	_input->register_callback("toggle_menu", toggle_menu);
	_input->register_callback("crouch", crouch);
	_input->register_callback("toggle_fullscreen", toggle_fullscreen);

	// Initialize the input, which loads the keymap from config.json
	_input->init();

	// Load the main keymap into the input stack
	// _input->push("menu");
	_input->push("main");

	// By default, hide the cursor in this game mode
	SDL_ShowCursor(0);

	// Since we are hiding the cursor, set to relative mode
	SDL_SetRelativeMouseMode(SDL_TRUE);

	// TODO: Delete everything under here

	//Generate program
	gProgramID = glCreateProgram();

	//Create vertex shader
	GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );

	//Get vertex source
	const GLchar* vertexShaderSource[] =
	{
		"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
	};

	//Set vertex source
	glShaderSource( vertexShader, 1, vertexShaderSource, NULL );

	//Compile vertex source
	glCompileShader( vertexShader );

	//Check vertex shader for errors
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &vShaderCompiled );
	if( vShaderCompiled != GL_TRUE )
	{
		printf( "Unable to compile vertex shader %d!\n", vertexShader );
		printShaderLog( vertexShader );
        return false;
	}

	//Attach vertex shader to program
	glAttachShader( gProgramID, vertexShader );

	//Create fragment shader
	GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

	//Get fragment source
	const GLchar* fragmentShaderSource[] =
	{
		"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 0.3, 0.6, 1.0, 1.0 ); }"
	};

	//Set fragment source
	glShaderSource( fragmentShader, 1, fragmentShaderSource, NULL );

	//Compile fragment source
	glCompileShader( fragmentShader );

	//Check fragment shader for errors
	GLint fShaderCompiled = GL_FALSE;
	glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled );
	if( fShaderCompiled != GL_TRUE )
	{
		printf( "Unable to compile fragment shader %d!\n", fragmentShader );
		printShaderLog( fragmentShader );
		return false;
	}

	//Attach fragment shader to program
	glAttachShader( gProgramID, fragmentShader );


	//Link program
	glLinkProgram( gProgramID );

	//Check for errors
	GLint programSuccess = GL_TRUE;
	glGetProgramiv( gProgramID, GL_LINK_STATUS, &programSuccess );
	if( programSuccess != GL_TRUE )
	{
		printf( "Error linking program %d!\n", gProgramID );
		printProgramLog( gProgramID );
		return false;
	}

	//Get vertex attribute location
	gVertexPos2DLocation = glGetAttribLocation( gProgramID, "LVertexPos2D" );
	if( gVertexPos2DLocation == -1 )
	{
		printf( "LVertexPos2D is not a valid glsl program variable!\n" );
		return false;
	}

	//VBO data
	GLfloat vertexData[] =
	{
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	//IBO data
	GLuint indexData[] = { 0, 1, 2, 3 };

	//Create VBO
	glGenBuffers( 1, &gVBO );
	glBindBuffer( GL_ARRAY_BUFFER, gVBO );
	glBufferData( GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW );

	//Create IBO
	glGenBuffers( 1, &gIBO );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW );

	return true;
}

void MainGame::update(float dt)
{
	// SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "MainGame::update() %f", dt);
}

void MainGame::interp(float dt)
{
	// SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "MainGame::interp() %f", dt);
}

void MainGame::draw_delete_me()
{
	//Clear color buffer
	glClear( GL_COLOR_BUFFER_BIT );

	//Render quad

	//Bind program
	glUseProgram( gProgramID );

	//Enable vertex position
	glEnableVertexAttribArray( gVertexPos2DLocation );

	//Set vertex data
	glBindBuffer( GL_ARRAY_BUFFER, gVBO );
	glVertexAttribPointer( gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );

	//Set index data and render
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
	glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );

	//Disable vertex position
	glDisableVertexAttribArray( gVertexPos2DLocation );

	//Unbind program
	glUseProgram(0);
}

void jump(Game* game, float dt, bool state, int x, int y)
{
	if (state)
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "jumping: %f", dt);
}

void crouch(Game* game, float dt, bool state, int x, int y)
{
	if (state)
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "crouching: %f", dt);
}

void quit(Game* game, float dt, bool state, int x, int y)
{
	if (state)
		game->get_manager()->quit();
}

void toggle_fullscreen(Game* game, float dt, bool state, int x, int y)
{
	if (state)
		game->get_manager()->get_window()->toggle_fullscreen();
}

void toggle_cursor(Game* game, float dt, bool state, int x, int y)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "toggle_cursor");
	SDL_bool cursorShown = SDL_bool((SDL_ShowCursor(-1) == 1));
	SDL_ShowCursor(!cursorShown);
	SDL_SetRelativeMouseMode(SDL_bool(SDL_ShowCursor(-1) == 0));
	SDL_Window* id = game->get_manager()->get_window()->get_id();
	SDL_SetWindowGrab(id, cursorShown);
}

void toggle_menu(Game* game, float dt, bool state, int x, int y)
{
	if (state)
	{
		SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "toggle_menu");
		toggle_cursor(game, dt, state, x, y);
		string top = game->get_input()->top();
		if (top == "menu")
		{
			game->get_input()->clear();
			game->get_input()->push("main");
		}
		else
		{
			game->get_input()->clear();
			game->get_input()->push("menu");
		}
		// cout << game->get_input()->top() << endl;
	}
}

void menu_click(Game* game, float dt, bool state, int x, int y)
{
	if (state)
		SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "UI Clicked (%i,%i)", x, y);
}

void attack(Game* game, float dt, bool state, int x, int y)
{
	if (state)
		SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Attack Charging!");
	else
		SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Attack Released!");
}
