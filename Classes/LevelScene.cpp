#include "LevelScene.h"

USING_NS_CC;

Scene* LevelScene::createScene()
{
	return LevelScene::create();
}

bool LevelScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// ��������г�ʼ��������Ҫ���¼Ӻ������磺initComponents()

	return true;
}
