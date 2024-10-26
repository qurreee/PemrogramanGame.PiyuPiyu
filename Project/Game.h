#ifndef BASEGAME_H
#define BASEGAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <GL/glew.h>
#include <iostream>
#include "Setting.h"
#include "Shader.h"
#include "Quad.h"
#include "Input.h"
#include <map>
#include <GLM/gtc/matrix_transform.hpp>

using namespace std;

namespace Engine {
	enum class State {
		RUNNING,
		EXIT
	};

	class Game
	{
	public:
		Game(Setting* setting);
		~Game();
		void SetBackgroundColor(int r, int g, int b);
		void Run();
		mat4 GetDefaultProjection();
		Shader* GetDefaultSpriteShader();
		Shader* GetDefaultTextShader();
		Quad* GetDefaultQuad();
		Input* GetInputManager();
		Setting* GetSettings();
		float GetGameTime(); //delta time
		State GetState();
		void SetState(State state);
	protected:
		Setting* setting = NULL;
		State state;
		unsigned int currentFrameRate = 0;
		mat4 defaultProjection;
		Shader* defaultSpriteShader = NULL;
		Shader* defaultTextShader = NULL;
		Quad* defaultQuad = NULL;
		Input* inputManager = NULL;
	
		mat4 CreateDefaultProjection();
		Shader* CreateDefaultSpriteShader();
		Shader* CreateDefaultTextShader();
		//method abstrak
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;

	private:
		mat4 projection;
		float targetFrameTime = 0;
		float deltaTime = 0;
		unsigned int lastTime = 0, duration = 0, numFrame = 0;
		SDL_Window* InitInternal();
		void GameLoop(SDL_Window* window);
		void CalcDeltaTimeAndFramerate();
		void PollInput();
	};
}

#endif
