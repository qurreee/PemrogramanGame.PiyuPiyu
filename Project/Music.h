#ifndef MUSIC_H
#define MUSIC_H

#include <SDL/SDL_mixer.h>


namespace Engine {
	class Music
	{
	public:
		Music(const char* path);
		~Music();
		bool IsPaused();
		bool IsPlaying();
		Music* Play(bool loop);
		Music* Pause();
		Music* Resume();
		Music* Stop();
		Music* SetVolume(int volume);
	private:
		Mix_Music* music = NULL;
		int volume = 100;
	};
}

#endif

