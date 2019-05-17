#include "LoadingScene.h"
#include "Music.h"

Scene* LoadingScene::createScene()
{
	auto scene = LoadingScene::create();

	// ����һ�����б�����ɫ��layer
	Layer* layerCLayer = LayerColor::create(Color4B(0, 0, 0, 0), SCREEN_WIDTH, SCREEN_HEIGHT);
	layerCLayer->setIgnoreAnchorPointForPosition(false);
	layerCLayer->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	scene->addChild(layerCLayer);

	return scene;
}

bool LoadingScene::init()
{
	if (!Scene::init()) return false;


	// ��ӱ���ͼƬ
	auto sprite = Sprite::create("/images/loadingScene/jetBrainTheme/scene_sta.png");
	sprite->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(sprite);

	// �����Ϸ����
	label = Sprite::create("/images/loadingScene/jetBrainTheme/label1.png");
	label->setPosition(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(label, 0);

	// ���ڼ��ص����߳�
	std::thread loadingThread(&LoadingScene::loading, this);
	loadingThread.detach();

	// ��ʱ����ÿ2.5�����Ƿ���Կ�ʼ��Ϸ
	schedule(schedule_selector(LoadingScene::startGame), 2.5);

	//��ʼ���ű�������
	auto startMusic = new Music;
	startMusic->loading();

	return true;
}


void LoadingScene::loading()
{
	// TODO ����һ��

	loadingFlag = true;
}

void LoadingScene::startGame(float)
{
	if (!loadingFlag) return;
	else unschedule(schedule_selector(LoadingScene::startGame));

	// ����Ϸ���������ƶ�
	const auto moveTo = MoveTo::create(1, Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50));
	label->runAction(moveTo);

	// ���������ʼ��Ϸ
	auto ready = Sprite::create("/images/loadingScene/jetBrainTheme/label2.png");
	ready->setPosition(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50));
	ready->setOpacity(0); //����͸����Ϊ0
	this->addChild(ready);
	// �����Ч��
	const auto fadeIn = FadeIn::create(3.0f);
	ready->runAction(fadeIn);

	// ��������
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = [](Event* event)
	{
		Director::getInstance()->replaceScene(MenuScene::createScene());
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}
