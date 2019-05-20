#ifndef __SOUND_H__
#define __SOUND_H__

#include "AudioEngine.h"
#include <string>
#include <vector>

using namespace cocos2d::experimental;
using std::string;
using std::vector;

class Sound
{
public:
	// TODO 文件格式请用MP3
	const string clicked = "/sound/clicked.mp3";

	static Sound* getInstance();
	void stop() const;
	void play(const string& path);
	bool getStatus() const { return on; };
	void turnOn() { on = true; };
	void turnOff() { on = false; };

private:
	static Sound* instance;
	int audioId = AudioEngine::INVALID_AUDIO_ID;
	bool on = true;
	Sound();
};

#endif
