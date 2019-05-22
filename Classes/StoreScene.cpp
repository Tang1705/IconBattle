#include "StoreScene.h"

Scene* StoreScene::createScene()
{
	return StoreScene::create();
}

bool StoreScene::init()
{
	if (!Scene::init()) return false;

	// TODO �滻���ð�ť
	this->addChild(SettingButton::create());

	// ���ذ�ť
	this->addChild(BackButton::create());

	return true;
}
