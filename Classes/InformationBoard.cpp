#include "GameScene.h"

void GameScene::initInformationBoard()
{
	// 宝石背景版
	auto bottomBackground = Sprite::create(theme->gameSceneBottomBackground);
	bottomBackground->setPosition(Point(793, 419));
	this->addChild(bottomBackground, -1);

	// 主背景版
	auto topBackground = Sprite::create(theme->gameSceneTopBackground);
	topBackground->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(topBackground, 10);

	// 设置按钮
	auto settingButton = SettingButton::create();
	settingButton->setPosition(Point(1080, 850));
	this->addChild(settingButton, 11);

	// 返回按钮
	auto backButton = Button::create(theme->backButtonNormal, theme->backButtonSelected,
	                                 theme->backButtonDisabled);
	backButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			const auto dialog = Dialog::create(theme->messageDialogBackground, Size(640, 480));
			dialog->setContentText("您确定要退出当前游戏么? 这将丢失当前游戏进度!", 36, 60, 20);

			dialog->addButton(MenuItemSprite::create(
				Sprite::create(theme->gameSceneYesButtonNormal),
				Sprite::create(theme->gameSceneYesButtonSelected),
				Sprite::create(theme->gameSceneYesButtonNormal),
				[&](Ref* sender)
				{
					Director::getInstance()->replaceScene(TransitionSlideInL::create(
						1.0f, mode == LEVEL_MODE ? LevelScene::createScene(isClassical) : MenuScene::create()));
				}));
			dialog->addButton(MenuItemSprite::create(
				Sprite::create(theme->gameSceneNoButtonNormal),
				Sprite::create(theme->gameSceneNoButtonSelected),
				Sprite::create(theme->gameSceneNoButtonNormal),
				[&, dialog](Ref* sender)
				{
					Director::getInstance()->getRunningScene()->removeChild(dialog);
				}));

			this->addChild(dialog, 30);
		}
	});
	backButton->setPosition(Point(1150, 850));
	this->addChild(backButton, 11);

	// 标题
	const string gameModeName = mode == PRACTICE_MODE ? "练习" : mode == LEVEL_MODE ? "闯关" : "挑战";
	auto modeLabel = Label::createWithTTF(isClassical ? "经典" + gameModeName : "进阶" + gameModeName, theme->semiBoldFont,
	                                      50);
	modeLabel->setPosition(modeLabel->getContentSize().width / 2 + 90, 850);
	this->addChild(modeLabel, 12);

	// 步数背景
	auto stepBackground = Sprite::create(mode != PRACTICE_MODE
		                                     ? theme->gameSceneStepSpriteBackground
		                                     : theme->gameSceneInfStepSpriteBackground);
	stepBackground->setScale(1.5);
	stepBackground->setPosition(225, 640);
	this->addChild(stepBackground, 11);

	// 步数Label
	stepNumberLabel = Label::createWithTTF(mode != PRACTICE_MODE ? to_string(stepNumber) : "", theme->markerFeltFont,
	                                       48);
	stepNumberLabel->enableGlow(Color4B::YELLOW);
	stepNumberLabel->setPosition(225, 635);
	this->addChild(stepNumberLabel, 12);

	// 目标分数
	totalScoreLabel = Label::createWithTTF(std::to_string(totalScore), theme->markerFeltFont, 35);
	totalScoreLabel->setPosition(225, 540);
	this->addChild(totalScoreLabel, 12);

	// 积分条背景
	auto processBar = Sprite::create(theme->gameSceneGreyProcessBar);
	processBar->setPosition(Point(225, 385));
	this->addChild(processBar, 11);

	// 积分条前景，设置竖排
	currentProgressBar = Sprite::create(theme->gameSceneProcessBar);
	progressController = ProgressTimer::create(currentProgressBar);
	progressController->setPosition(Point(225, 385));
	progressController->setType(ProgressTimer::Type::BAR);
	progressController->setBarChangeRate(Point(0, 1));
	progressController->setMidpoint(Point(0, 0));
	progressController->setPercentage(0);
	this->addChild(progressController, 12);

	// 分数板
	currentScoreLabel = Label::createWithTTF("0", theme->markerFeltFont, 32);
	currentScoreLabel->setPosition(225, 230);
	this->addChild(currentScoreLabel, 11);

	// 提示次数
	hintNumberSprite = Sprite::create(theme->gameSceneHintNumber + to_string(hintNumber) + ".png");
	hintNumberSprite->setPosition(340, 520);
	this->addChild(hintNumberSprite, 12);

	// 提示按钮
	auto hintButton = Button::create(theme->gameSceneHintButtonNormal,
	                                 theme->gameSceneHintButtonSelected,
	                                 theme->gameSceneHintButtonDisabled);
	hintButton->setPosition(Point(375, 540));
	hintButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			if (hintNumber > 0 && showHint())
			{
				hintNumber--;
				hintNumberSprite->setTexture(theme->gameSceneHintNumber + to_string(hintNumber) + ".png");
			}
		}
	});
	this->addChild(hintButton, 11);
}

void GameScene::setTotalScore(const int score)
{
	if (totalScore >= 0 && totalScoreLabel != nullptr)
	{
		totalScore = score;
		totalScoreLabel->setString(to_string(score));
	}
}

void GameScene::setStepNumber(const int step)
{
	if (step >= 0 && stepNumberLabel != nullptr)
	{
		stepNumber = step;
		stepNumberLabel->setString(to_string(step));
	}
}

void GameScene::minusStepNumber()
{
	if (stepNumber > 0 && stepNumberLabel != nullptr)
	{
		stepNumber--;
		if (mode != PRACTICE_MODE) stepNumberLabel->setString(to_string(stepNumber));
	}
}

void GameScene::addCurrentScore(const int deltaScore)
{
	const auto previousScore = currentScore;

	if (currentScore + deltaScore <= 0) currentScore = 0;
	else if (currentScore + deltaScore >= totalScore) currentScore = totalScore;
	else currentScore += deltaScore;

	const auto processAction = ProgressFromTo::create(0.25, 100.0f * previousScore / totalScore,
	                                                  100.0f * currentScore / totalScore);
	progressController->runAction(processAction);

	currentScore = previousScore + deltaScore;
	log("Score: Add %d; From %d; To %d; Total %d;", deltaScore, previousScore, currentScore, totalScore);
	currentScoreLabel->setString(to_string(currentScore));
}
