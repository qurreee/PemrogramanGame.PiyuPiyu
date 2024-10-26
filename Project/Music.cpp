#include "Music.h"

using namespace Engine;

Music::Music(const char* path)
{
	music = Mix_LoadMUS(path);
}

Music::~Music()
{
	Mix_FreeMusic(music);
}

bool Music::IsPaused()
{
	return Mix_PausedMusic() == 1;
}

bool Music::IsPlaying()
{
	return Mix_PlayingMusic() == 1;
}

Engine::Music* Engine::Music::Play(bool loop)
{
	Mix_PlayMusic(music, loop ? -1 : 0);
	return this;
}

Engine::Music* Music::Pause()
{
	Mix_PauseMusic();
	return this;
}

Engine::Music* Music::Resume()
{
	Mix_ResumeMusic();
	return this;
}

Engine::Music* Music::Stop()
{
	Mix_HaltMusic();
	return this;
}

Engine::Music* Engine::Music::SetVolume(int volume)
{
	this->volume = volume;
	Mix_VolumeMusic(volume * 128 / 100);
	return this;
}
