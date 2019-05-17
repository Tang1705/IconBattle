#include "Music.h"

bool Music::loading()
{   
	backMusic = SimpleAudioEngine::getInstance();

	// TODO: �����ϴ����н�������������

	//��Ӧ�ô����ϴ����е�������
	startMusic("/musics/tryBackgroundMusic.mp3");

	return true;
}

void Music::startMusic(const char* musicFileName) const
{
	//ѭ������
	backMusic->playBackgroundMusic(musicFileName, true);
}

void Music::setVolume(const float volume) const
{
	backMusic->setBackgroundMusicVolume(volume);
}

void Music::changeMusic(const char*  newMusicName) const
{
	backMusic->stopBackgroundMusic();
	backMusic->playBackgroundMusic(newMusicName);
}

void Music::stopMusic() const
{
	backMusic->stopBackgroundMusic();
}
