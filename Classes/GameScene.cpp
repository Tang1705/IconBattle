#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// ��������г�ʼ��������Ҫ���¼Ӻ������磺initComponents()

	return true;
}
