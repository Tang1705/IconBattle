#include "Sound.h"

// TODO ��Ч·������+Ԥ����
const string Sound::CLICKED = "/sound/clicked.mp3";

Sound* Sound::instance = nullptr;

Sound* Sound::getInstance()
{
	if (instance == nullptr) instance = new Sound();
	return instance;
}

void Sound::stop() const
{
	audio->stopAllEffects();
}

void Sound::play(const string& path) const
{
	audio->playEffect(path.data());
}

Sound::Sound()
{
	audio->preloadEffect(CLICKED.data());
	audio->setEffectsVolume(0.5f);
}
