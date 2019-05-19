#include "StoreScene.h"

USING_NS_CC;

Scene* StoreScene::createScene()
{
	return StoreScene::create();
}

bool StoreScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// ���ð�ť
	auto settingButton = ui::Button::create("/images/menuScene/jetBrainTheme/setting_normal_image.png", "/images/menuScene/jetBrainTheme/setting_selected_image.png", "/images/menuScene/jetBrainTheme/setting_disabled_image.png");
	settingButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		// TODO �������
	});
	settingButton->setPosition(Point(1050, 850));
	this->addChild(settingButton);

	// ���ذ�ť
	auto backButton = ui::Button::create("/images/menuScene/jetBrainTheme/back_normal_image.png", "/images/menuScene/jetBrainTheme/back_selected_image.png", "/images/menuScene/jetBrainTheme/back_disabled_image.png");
	backButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		//���ص��˵�����
		if(type == ui::Widget::TouchEventType::ENDED)
			Director::getInstance()->popScene();
	});
	backButton->setPosition(Point(1150, 850));
	this->addChild(backButton);

	return true;
}
