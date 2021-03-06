#include "LevelScene.h"

Scene* LevelScene::createScene(const bool isClassical)
{
	const auto scene = LevelScene::create();

	scene->isClassical = isClassical;
	scene->initModeLabel(isClassical);

	// 背景设置
	scene->initBackground();

	// 设置layer来存放各个按钮
	scene->layer = Layer::create();
	scene->layer->setContentSize(Size(scene->buttonDistance * 11, SCREEN_HEIGHT));

	// 设置页面滚动
	scene->initScrollView();

	// 初始化按钮位置
	for (auto i = 0; i < 10; i++)
	{
		scene->pos[i].first = scene->buttonDistance * (i + 1);
		scene->pos[i].second = Util::getRandomNumber(200, 650);
	}

	// 初始化选关按钮
	scene->initButtons();

	// 初始化金币
	scene->initCoin();

	// 画连接按钮的线
	auto drawNode = DrawNode::create();
	scene->layer->addChild(drawNode, 3);

	for (auto i = 0; i < 9; i++)
	{
		drawNode->drawSegment(Point(scene->pos[i].first, scene->pos[i].second),
		                      Point(scene->pos[i + 1].first, scene->pos[i + 1].second),
		                      5, Color4F(1, 1, 1, 0.3f));
	}

	// 设置按钮
	auto settingButton = SettingButton::create();
	settingButton->setPosition(Point(1080, 850));
	scene->addChild(settingButton, 4);

	// 返回按钮
	auto backButton = Button::create(scene->theme->backButtonNormal, scene->theme->backButtonSelected,
	                                 scene->theme->backButtonDisabled);

	backButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		//返回到上一个场景
		if (type == ui::Widget::TouchEventType::ENDED)
			Director::getInstance()->replaceScene(
				TransitionFade::create(1.0f, MenuScene::create()));
	});
	backButton->setPosition(Point(1150, 850));
	scene->addChild(backButton, 4);

	return scene;
}

void LevelScene::initBackground()
{
	// 第一张背景图 —— 星空
	backgroundFirst = Sprite::create(theme->levelSceneDistantView);
	backgroundFirst->setPosition(Vec2::ZERO);
	backgroundFirst->setAnchorPoint(Vec2::ZERO);
	this->addChild(backgroundFirst);

	backgroundSecond = Sprite::create(theme->levelSceneDistantView);
	backgroundSecond->setPosition(Vec2::ZERO);
	backgroundSecond->setAnchorPoint(Vec2(1, 0));
	this->addChild(backgroundSecond);

	// 第二张背景图 —— 前景的星星
	foregroundFirst = Sprite::create(theme->levelSceneForeground);
	foregroundFirst->setPosition(Vec2::ZERO);
	foregroundFirst->setAnchorPoint(Vec2::ZERO);
	this->addChild(foregroundFirst);

	foregroundSecond = Sprite::create(theme->levelSceneForeground);
	foregroundSecond->setPosition(Vec2::ZERO);
	foregroundSecond->setAnchorPoint(Vec2(1, 0));
	this->addChild(foregroundSecond);

	scheduleUpdate();
}

void LevelScene::initScrollView()
{
	auto scrollView = ui::ScrollView::create();
	scrollView->setPosition(Point(0, 0));
	scrollView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	scrollView->setTouchEnabled(true);
	scrollView->setScrollBarAutoHideTime(0);
	scrollView->setBounceEnabled(true);
	scrollView->setContentSize(Size(SCREEN_WIDTH, SCREEN_HEIGHT));
	scrollView->setInnerContainerSize(layer->getContentSize());
	scrollView->addChild(layer);
	addChild(scrollView, 3);

	//添加鼠标事件侦听
	auto listenerMouse = EventListenerMouse::create();
	listenerMouse->setEnabled(true);
	listenerMouse->onMouseScroll = [&, scrollView](EventMouse* event)
	{
		const auto x = event->getScrollY(); //滚轮上滑x值小于0，下滑x值小于0

		if (x < 0) currentScrollPercent -= 10;
		else currentScrollPercent += 10;

		if (currentScrollPercent > 100) currentScrollPercent = 100;
		if (currentScrollPercent < 0) currentScrollPercent = 0;

		scrollView->scrollToPercentHorizontal(currentScrollPercent, 1, true);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);
}

void LevelScene::initButtons()
{
	const auto unlockedLevel = isClassical
		                           ? User::getInstance()->getUnlockedClassicalLevel()
		                           : User::getInstance()->getUnlockedPlusLevel();
	for (auto i = 0; i < 10; i++)
	{
		auto levelButton = ui::Button::create(theme->levelSelectButton + std::to_string(i + 1) + "_normal.png",
		                                      theme->levelSelectButton + std::to_string(i + 1) + "_selected.png",
		                                      theme->levelSelectButton + std::to_string(i + 1) + "_disabled.png");

		if (i >= unlockedLevel)levelButton->setEnabled(false);
		levelButton->addTouchEventListener([&, i](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				GameSceneController::getInstance()->startLevelGame(isClassical, i);
			}
		});

		layer->addChild(levelButton, 4);
		levelButton->setPosition(Point(pos[i].first, pos[i].second));
		levelButton->setOpacity(0); //设置透明度为0

		const auto fadeIn = FadeIn::create(0.8f); // 淡入的效果
		const auto delay = DelayTime::create(1.2f * i);

		levelButton->runAction(Sequence::create(delay, fadeIn, nullptr));
	}
}

void LevelScene::initCoin()
{
	auto coinIcon = Sprite::create(theme->storeSceneCoin);
	coinIcon->setPosition(Point(130, 850));
	this->addChild(coinIcon, 4);

	coinText = Label::createWithTTF(to_string(user->getCoin()), theme->markerFeltFont, 30);
	coinText->setPosition(Point(220, 850));
	this->addChild(coinText, 11);
}

void LevelScene::initModeLabel(const bool isClassical)
{
	auto modeLabel = Label::createWithTTF(isClassical ? "经典模式" : "进阶模式", theme->semiBoldFont, 50);
	modeLabel->setPosition(Point(600, 850));
	this->addChild(modeLabel, 4);
}

void LevelScene::update(float)
{
	backgroundFirst->setPositionX(backgroundFirst->getPositionX() + 1);
	backgroundSecond->setPositionX(backgroundSecond->getPositionX() + 1);

	foregroundFirst->setPositionX(backgroundFirst->getPositionX() + 1);
	foregroundSecond->setPositionX(backgroundSecond->getPositionX() + 1);

	if (backgroundFirst->getPositionX() >= SCREEN_WIDTH)
	{
		backgroundFirst->setPositionX(0);
		backgroundSecond->setPositionX(0);
	}

	if (foregroundFirst->getPositionX() >= SCREEN_WIDTH)
	{
		foregroundFirst->setPositionX(0);
		foregroundSecond->setPositionX(0);
	}
}
