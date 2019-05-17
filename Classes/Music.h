#ifndef __MUSIC_H__
#define __MUSIC_H__

#include "SimpleAudioEngine.h"
#include <string>
#include <vector>

using namespace CocosDenshion;
using std::string;
using std::vector;

class Music
{
public:
	static Music* getInstance();

	void loading(const vector<string>& path) const; // TODO �ļ���ʽ����WAV
	void stop() const;
	void play(const string& path) const;
	void change(const string& path) const;
	void setVolume(const int volume) const; // ��Χ0��100
	int getVolume() const;

private:
	static Music* instance;
	SimpleAudioEngine* audio = SimpleAudioEngine::getInstance();

	Music() = default;
};

#endif
