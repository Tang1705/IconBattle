#include "SettingButton.h"

bool SettingButton::init()
{
	if (!Node::init()) return false;

	settingButton = ui::Button::create(settingButtonNormal, settingButtonSelected,

	                                   settingButtonDisabled);

	this->addChild(settingButton);


	// settingButton��Ӧ��������������
	settingButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (!popItem)
			{
				//TODO ��ťͼƬ����
				// ��Ӿ���˵�
				course = Sprite::create(courseMenuItemNormal);
				courseMenuItem = MenuItemSprite::create(course, course, course, [&](Ref* sender)
				{
					// TODO �̳�
				});
				courseMenuItem->setPosition(
					settingButton->getParent()->convertToWorldSpace(settingButton->getPosition()));

				music = Sprite::create(musicMenuItemNormal);
				musicMenuItem = MenuItemSprite::create(music, music, music, [&](Ref* sender)
				{
					const auto volume = Music::getInstance()->getVolume() % 100 - 20;
					Music::getInstance()->setVolume(volume); // ��������Ϊ0��20��40��60��80��100
					// TODO ����ͼƬ��ͼ�����
				});
				musicMenuItem->setPosition(
					settingButton->getParent()->convertToWorldSpace(settingButton->getPosition()));

				sound = Sprite::create(soundMenuItemNormal);
				soundMenuItem = MenuItemSprite::create(sound, sound, sound, [&](Ref* sender)
				{
					Sound::getInstance()->setStatus(!Sound::getInstance()->getStatus());
				});
				soundMenuItem->setPosition(
					settingButton->getParent()->convertToWorldSpace(settingButton->getPosition()));

#pragma region Appear Action
				// common action
				const auto delay = DelayTime::create(0.25);
				const auto fadeIn = FadeIn::create(0.25);

				// course action
				const auto courseMoveBy = MoveBy::create(0.25, Vec2(-75, 0));
				const auto courseSpawn = Spawn::create(fadeIn, delay, courseMoveBy, delay, nullptr);

				// music action
				const auto musicMoveBy = MoveBy::create(0.25, Vec2(-135, 0));
				const auto musicSpawn = Spawn::create(fadeIn, delay, musicMoveBy, delay, nullptr);

				// sound action
				const auto soundMoveBy = MoveBy::create(0.25, Vec2(-195, 0));
				const auto soundSpawn = Spawn::create(fadeIn, delay, soundMoveBy, delay, nullptr);

				menu = Menu::create(courseMenuItem, musicMenuItem, soundMenuItem, nullptr);
				menu->setPosition(Point(0, 0));
				Director::getInstance()->getRunningScene()->addChild(menu, 4);

				courseMenuItem->runAction(courseSpawn);
				musicMenuItem->runAction(musicSpawn);
				soundMenuItem->runAction(soundSpawn);

#pragma endregion
				popItem = true;
			}
			else
			{
#pragma region Disappear Action
				// common action
				const auto delay = DelayTime::create(0.25);
				const auto fadeOut = FadeOut::create(0.25);

				//course action
				const auto courseMoveBy = MoveBy::create(0.25, Vec2(75, 0));
				const auto courseSpawn = Spawn::create(fadeOut, delay, courseMoveBy, delay, nullptr);

				//music action
				const auto musicMoveBy = MoveBy::create(0.25, Vec2(135, 0));
				const auto musicSpawn = Spawn::create(fadeOut, delay, musicMoveBy, delay, nullptr);

				//sound action
				const auto soundMoveBy = MoveBy::create(0.25, Vec2(195, 0));
				const auto soundSpawn = Spawn::create(fadeOut, delay, soundMoveBy, delay, nullptr);

				courseMenuItem->runAction(Sequence::create(courseSpawn, CallFunc::create([&]()
				{
					Director::getInstance()
						->getRunningScene()->removeChild(menu);
				}), nullptr));
				musicMenuItem->runAction(Sequence::create(musicSpawn, CallFunc::create([&]()
				{
					Director::getInstance()
						->getRunningScene()->removeChild(menu);
				}), nullptr));
				soundMenuItem->runAction(Sequence::create(soundSpawn, CallFunc::create([&]()
				{
					Director::getInstance()
						->getRunningScene()->removeChild(menu);
				}), nullptr));

#pragma endregion
				popItem = false;
			}
		}
	});

	return true;
}
