#include "Sound.h"

Sound* Sound::instance = nullptr;

Sound* Sound::getInstance()
{
	if (instance == nullptr) instance = new Sound();
	return instance;
}

void Sound::stop() const
{
	AudioEngine::stop(audioId);
}

void Sound::play(const string& path)
{
	if (on) audioId = AudioEngine::play2d(path, false, 0.9f);
}

Sound::Sound()
{
	AudioEngine::preload(click);
	AudioEngine::preload(threeKill);
	AudioEngine::preload(fourKill);
	AudioEngine::preload(fiveKill);
	AudioEngine::preload(boom);
	AudioEngine::preload(superCreate);
}
