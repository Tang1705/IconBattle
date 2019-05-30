#include "StoreScene.h"

Scene* StoreScene::createScene()
{
	return StoreScene::create();
}

bool StoreScene::init()
{
	if (!Scene::init()) return false;

	// TODO �滻���ð�ť
	auto settingButton = SettingButton::create();
	settingButton->setPosition(Point(1050, 850));
	this->addChild(settingButton);

	// ���ذ�ť
	this->addChild(BackButton::create());
	
	initCoins();
	initLabel();
	initThemeIcon();
	initButtons();
	
	return true;
}

void StoreScene::initCoins()
{
	auto coinIcon = Sprite::create(theme->storeSceneCoin);
	coinIcon->setPosition(Point(130, 850));
	this->addChild(coinIcon, -1);

	// TODO ������
	auto coinText = Label::createWithTTF("30", "font/marker_felt.ttf", 30);
	coinText->setPosition(Point(220, 850));
	this->addChild(coinText, -1);
}

void StoreScene::initLabel()
{
	auto label = Sprite::create(theme->storeSceneStoreLabel);
	label->setPosition(Point(600, 800));
	this->addChild(label, -1);
}

void StoreScene::initThemeIcon()
{
	auto jetBrainThemeIcon = Sprite::create(theme->storeSceneJetBrainThemeIcon);
	jetBrainThemeIcon->setPosition(Point(240, 450));
	this->addChild(jetBrainThemeIcon, -1);

	auto AdobeThemeIcon = Sprite::create(theme->storeSceneAdobeThemeIcon);
	AdobeThemeIcon->setPosition(Point(600, 450));
	this->addChild(AdobeThemeIcon, -1);

	auto officeThemeIcon = Sprite::create(theme->storeSceneOfficeThemeIcon);
	officeThemeIcon->setPosition(Point(960, 450));
	this->addChild(officeThemeIcon, -1);
}

void StoreScene::initButtons()
{
	// ѡ��ť
	auto choiceIcon = ui::Button::create(theme->storeSceneChoiceButtonNormal,
		theme->storeSceneChoiceButtonSelected,
		theme->storeSceneChoiceButtonDisabled);
	choiceIcon->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		// TODO
	});
	choiceIcon->setPosition(Point(240, 120));
	this->addChild(choiceIcon);

	// Adobe��ť
	auto adobeCoinIcon = ui::Button::create(theme->storeSceneAdobeCoinsButtonNormal,
		theme->storeSceneAdobeCoinsButtonSelected,
		theme->storeSceneAdobeCoinsButtonDisabled);
	adobeCoinIcon->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		// TODO
	});
	adobeCoinIcon->setPosition(Point(600, 120));
	this->addChild(adobeCoinIcon);

	// Office��ť
	auto officeCoinIcon = ui::Button::create(theme->storeSceneOfficeCoinsButtonNormal,
		theme->storeSceneOfficeCoinsButtonSelected,
		theme->storeSceneOfficeCoinsButtonDisabled);
	officeCoinIcon->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		// TODO
	});
	officeCoinIcon->setPosition(Point(960, 120));
	this->addChild(officeCoinIcon);
}