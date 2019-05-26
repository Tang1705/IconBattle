#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "StoreScene.h"
#include "GameScene.h"
#include "LevelScene.h"
#include "NewsBoard.h"
#include "BackButton.h"
#include "SettingButton.h"
#include "Theme.h"
#include "User.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

USING_NS_CC;

class MenuScene final :
	public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	bool init() override;
	CREATE_FUNC(MenuScene)

private:
	Theme* theme = Theme::getInstance("JetBrain");
	void initUsername();
	void initStoreButton();
	void initRankButton();
	void initGameButton();
};

#endif
