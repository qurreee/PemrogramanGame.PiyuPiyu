#include "Lesson02_Lerp.h"

Engine::Lesson02_Lerp::Lesson02_Lerp(Setting* setting) :Engine::Game(setting)
{
	color_duration = 0.0f;
	r_p = 0;
	g_p = 0;
	b_p = 0;
	r_y = 0;
	g_y = 0;
	b_y = 0;
	f = 0.0f;
	mul = 0;

	setting->windowTitle = "LERP";
}

Engine::Lesson02_Lerp::~Lesson02_Lerp()
{
}

void Engine::Lesson02_Lerp::Init()
{
	// Yellow
	r_y = 255;
	g_y = 255;
	b_y = 0;
	// Purple
	r_p = 157;
	g_p = 3;
	b_p = 255;
	// Set mul to 1
	mul = -1;
	// Set f to 0
	f = 0.0f;
}

void Engine::Lesson02_Lerp::Update()
{
	if (color_duration >= 50.0f) {
		f += (mul *= (f <= 0.0f || f >= 1.0f) ? -1 : 1) * 0.02f;
		SetBackgroundColor(lerp((float)r_y, (float)r_p, f),
			lerp((float)g_y, (float)g_p, f),
			lerp((float)b_y, (float)b_p, f));
		color_duration = 0;
	}
	color_duration += GetGameTime();
}

void Engine::Lesson02_Lerp::Render()
{

}

int Engine::Lesson02_Lerp::lerp(float a, float b, float f)
{
	return (int)((1 - f) * a + f * b);
}

