#include "LoadingScene.h"
#define GAME_SCREEN_WIDTH 1200
#define GAME_SCREEN_HEIGHT 900

USING_NS_CC;

Scene* LoadingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingScene::create();

	// ����һ�����б�����ɫ��layer2 (��ɫ)
	CCLayer *layer2 = CCLayerColor::create(ccc4(0x00, 0x00, 0x00, 0xf0), GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
	layer2->ignoreAnchorPointForPosition(false);
	layer2->setPosition(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2);
	layer2->addChild(layer);
	scene->addChild(layer2, 1, layer2->getTag());

	return scene;
}

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// ��ӱ���ͼƬ
	auto sprite = Sprite::create("/images/loadingScene/jetbrainTheme/scene_sta.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	this->addChild(sprite);

	// �����Ϸ����
	label = Sprite::create("/images/loadingScene/jetbrainTheme/label1.png");
	label->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	this->addChild(label, 0);

	// ������ɣ�׼����ʼ��Ϸ
	readyToStart();

	return true;
}


void LoadingScene::readyToStart()
{
	// ����Ϸ���������ƶ�
	auto moveTo = MoveTo::create(1, Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2 + 50));
	label->runAction(moveTo);

	// ���������ʼ��Ϸ
	Sprite *ready = Sprite::create("/images/loadingScene/jetbrainTheme/label2.png");
	ready->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2 - 50));
	ready->setOpacity(0);	//����͸����Ϊ0
	this->addChild(ready);
	// �����Ч��
	auto fadeIn = FadeIn::create(3.0f);
	ready->runAction(fadeIn);


	// ��������
	auto _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseDown = CC_CALLBACK_1(LoadingScene::startGame, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}

void LoadingScene::startGame(Event* ev)
{
	log("ready to start");
	// ��ת����Ϸ����
	// auto scene = GameScene::createScene();
	// CCDirector::sharedDirector()->replaceScene(scene);
}