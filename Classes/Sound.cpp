#include "Sound.h"

bool Sound::init()
{
	clickSound = SimpleAudioEngine::getInstance();

	return true;
}

void Sound::generateClickSound() const
{
	//����һ�ΰ�����
	clickSound->playEffect("/musics/clickSound.mp3");
}

