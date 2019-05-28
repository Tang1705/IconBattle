#ifndef __SETTING_BUTTON_H__
#define __SETTING_BUTTON_H__


#include "cocos2d.h"
#include "ui/UIButton.h"
#include "Music.h"
#include "Sound.h"


using std::string;
USING_NS_CC;

class SettingButton
{
public:
	SettingButton(Scene* scene,int order);

private:
#pragma region Image URL
	const string settingButtonNormal = "/image/common/setting_normal.png";
	const string settingButtonSelected = "/image/common/setting_selected.png";
	const string settingButtonDisabled = "/image/common/setting_disabled.png";

	const string courseMenuItemNormal = "/image/common/course.png";
	const string musicMenuItemNormal = "/image/common/music.png";
	const string soundMenuItemNormal = "/image/common/sound.png";

#pragma endregion

	bool popItem = false; //false��������ѡ���֮�ջ�
	bool soundPlay = false; //false�ر���Ч����֮��
	int musicVolume = 0; //����
	int zOrder = 0;
	ui::Button* settingButton;
	Scene* currentScene;
	Sprite* course; //�̳�
	Sprite* music; //����
	Sprite* sound; //��Ч
	MenuItemSprite* courseMenuItem;
	MenuItemSprite* musicMenuItem;
	MenuItemSprite* soundMenuItem;
	Menu* menu;
};

#endif
