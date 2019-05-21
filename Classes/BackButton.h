#ifndef __BACK_BUTTON_H__
#define __BACK_BUTTON_H__


#include "cocos2d.h"
#include "ui/UIButton.h"

#pragma region 
const std::string BACK_BUTTON_NORMAL_IMAGE = "/image/gamescene/jetbraintheme/back_normal.png";
const std::string BACK_BUTTON_SELECTED_IMAGE = "/image/gamescene/jetbraintheme/back_selected.png";
const std::string BACK_BUTTON_DISABLED_IMAGE = "/image/gamescene/jetbraintheme/back_disabled.png";
#pragma endregion 

USING_NS_CC;

// ���ذ�ť�̳�Button
class BackButton final
	:public ui::Button
{
public:
	static BackButton* getInstance();// ����
	void backLastScene();//������Ҫ���صĽ���

private:
	static BackButton *instance;
	static BackButton* create();

};

#endif 
