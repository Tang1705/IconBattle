#ifndef __SETTING_BUTTON_H__
#define __SETTING_BUTTON_H__


#include "cocos2d.h"
#include "ui/UIButton.h"

#pragma region 
const std::string SETTING_BUTTON_NORMAL_IMAGE = "/image/gamescene/jetbraintheme/setting_normal.png";
const std::string SETTING_BUTTON_SELECTED_IMAGE = "/image/gamescene/jetbraintheme/setting_selected.png";
const std::string SETTING_BUTTON_DISABLED_IMAGE = "/image/gamescene/jetbraintheme/setting_disabled.png";
#pragma endregion 

USING_NS_CC;

// ���ð�ť�̳�Button
class SettingButton final
	:public ui::Button
{
public:
	static SettingButton* getInstance();// ����
	void settingByUser();//������Ҫ���صĽ���

private:
	static SettingButton*instance;
	static SettingButton* create();

};

#endif 
