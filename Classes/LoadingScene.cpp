#include "LoadingScene.h"

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

	jetIcon();

	// ���ڼ��ص����߳�
	std::thread loadingThread(&LoadingScene::loading, this);
	loadingThread.detach();

	// ��ʱ����ÿ2.5�����Ƿ���Կ�ʼ��Ϸ
	schedule(schedule_selector(LoadingScene::startGame), 2.5);

	return true;
}


void LoadingScene::loading()
{
	// TODO ����һ��

	// ��ʼ����������
	vector<string> musicPath;
	// TODO ����Ĭ�������ļ�λ��
	musicPath.emplace_back("/musics/tryBackgroundMusic.mp3");
	musicPath.emplace_back("/musics/tryBackgroundMusic.mp3");
	Music::getInstance()->loading(musicPath);

	// ��ʼ����Ч
	Sound::getInstance();

	loadingFlag = true;
}

void LoadingScene::startGame(float)
{
	if (!loadingFlag) return;
	else unschedule(schedule_selector(LoadingScene::startGame));

	// TODO ����Ĭ�������ļ�λ��
	Music::getInstance()->play("/musics/tryBackgroundMusic.mp3");

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

//����ͼ�궯��ʵ��
void LoadingScene::jetIcon()
{
	const auto dirs = Director::getInstance();

	//ͼ���Spawn������������
	Sprite *iconSet[10];
	Spawn *spawnSet[10];

	//ѭ����ʼ��Icon����Ͷ���
	for (auto i = 0; i < 10; i++)
	{
		iconSet[i] = Sprite::create("/images/loadingScene/jetBrainTheme/iconSet/medium/" + std::to_string(i) + ".png");
		iconSet[i]->setPosition(dirs->getVisibleSize().width / 2, 0);
		iconSet[i]->setScale(1);
		this->addChild(iconSet[i]);

		//����һ��Action��ʹ�þ����ĳһλ���������ͨ����ѧ���ʽʵ����Ȫ���ͣ���ª��
		const auto jumpRight = JumpBy::create(3, Point(dirs->getVisibleSize().width/4+30*i, 0-iconSet[i]->getContentSize().height),30 * i+100, 1);
		const auto jumpLeft = JumpBy::create(3, Point(-dirs->getVisibleSize().width/4-30*i, 0-iconSet[i]->getContentSize().height),30 * i+70, 1);

		const auto move = MoveTo::create(1.5,Vec2(dirs->getVisibleSize().width / 2, 0 - iconSet[i]->getContentSize().height));
		//ʵ�־�����ƶ�������Icon�Ŵ�
		const auto scale = ScaleTo::create(3, 2);

		const auto delay = DelayTime::create(0.25f);

		//���ݼ������жϾ����׳��ķ���
		if (i % 2 == 0)
		{
			spawnSet[i] = Spawn::create(jumpRight, delay, scale, delay->clone(), nullptr);//ͬʱ���ж������
			auto sequence = Sequence::create(spawnSet[i], delay, move, delay, nullptr);//��������
			iconSet[i]->runAction(RepeatForever::create(sequence));//ʵ���ظ���Ծ
		}
		else
		{
			spawnSet[i] = Spawn::create(jumpLeft, delay, scale, delay->clone(), nullptr);
			auto sequence = Sequence::create(spawnSet[i], delay, move, delay, nullptr);
			iconSet[i]->runAction(RepeatForever::create(sequence));
		}
	}
}
