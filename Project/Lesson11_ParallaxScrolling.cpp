#include "Lesson11_ParallaxScrolling.h"

Engine::Lesson11_ParallaxScrolling::Lesson11_ParallaxScrolling(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Parallax Scrolling";
}

Engine::Lesson11_ParallaxScrolling::~Lesson11_ParallaxScrolling()
{
}

void Engine::Lesson11_ParallaxScrolling::Init()
{
	for (int i = 0; i <= 4; i++) {
		AddToLayer(backgrounds, "bg0" + to_string(i) + ".png");
	}
	for (int i = 5; i <= 8; i++) {
		AddToLayer(middlegrounds, "bg0" + to_string(i) + ".png");
	}
	for (int i = 9; i <= 9; i++) {
		AddToLayer(foregrounds, "bg0" + to_string(i) + ".png");
	}

	offset = 2;
}

void Engine::Lesson11_ParallaxScrolling::Update()
{
	MoveLayer(backgrounds, 0.005f);
	MoveLayer(middlegrounds, 0.03f);
	MoveLayer(foregrounds, 0.5f);
}

void Engine::Lesson11_ParallaxScrolling::Render()
{
	DrawLayer(backgrounds);
	DrawLayer(middlegrounds);
	DrawLayer(foregrounds);
}

void Engine::Lesson11_ParallaxScrolling::MoveLayer(vector<Sprite*>& bg, float speed)
{
	for (Sprite* s : bg) {
		if (s->GetPosition().x < -setting->screenWidth + offset) {
			s->SetPosition(setting->screenWidth + offset - 1, 0);
		}
		s->SetPosition(s->GetPosition().x - speed * GetGameTime(), s->GetPosition().y);
		s->Update(GetGameTime());
	}
}

void Engine::Lesson11_ParallaxScrolling::DrawLayer(vector<Sprite*>& bg)
{
	for (Sprite* s : bg) {
		s->Draw();
	}
}

void Engine::Lesson11_ParallaxScrolling::AddToLayer(vector<Sprite*>& bg, string name)
{
	Texture* texture = new Texture(name);

	Sprite* s = new Sprite(texture, defaultSpriteShader, defaultQuad);
	s->SetSize(setting->screenWidth + offset, setting->screenHeight);
	bg.push_back(s);

	Sprite* s2 = new Sprite(texture, defaultSpriteShader, defaultQuad);
	s2->SetSize(setting->screenWidth + offset, setting->screenHeight)->SetPosition(setting->screenWidth + offset - 1, 0);
	bg.push_back(s2);
}

