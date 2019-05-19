#include "PannelNews.h"

PannelNews::PannelNews()
{
}

PannelNews::~PannelNews() {}

bool PannelNews::init()
{
	if (!Node::init())
		return false;
	setPosition(Point(640.f, 585.f));
	holder = Node::create();
	addChild(holder);
	newsBg = Sprite::create("/images/menuScene/jetBrainTheme/back_normal_image.png");
	holder->addChild(newsBg);

	sharpNode = DrawNode::create();
	Point point[4] = { Point(60.f,0.f), Point(710.f,0.f), Point(710.f,35.f),   Point(60.f,35.f) };
	//�����ʾ�ľ�������

	sharpNode->drawPolygon(point, 4, Color4F(255, 255, 255, 255), 2, Color4F(255, 255, 255, 255));
	//����������ʾ�ľ������򣬲�����Ӧ�����ڱ�ʶ�����Point(Vec2)����ָ�룬���鳤�ȣ������ɫ���߿��ȣ��߿���ɫ
	clipper = ClippingNode::create();
	clipper->setStencil(sharpNode);
	clipper->setAnchorPoint(Point(0.5, 0.5));
	newsBg->addChild(clipper);

	news = Label::createWithTTF("testing notice borad ~~~~~~~~~~~~", "/fonts/Marker Felt.ttf", 24);
	news->setColor(Color3B(214, 213, 213));
	clipper->addChild(news);

	layout();
	return true;
}

void PannelNews::layout()
{
	news->setAnchorPoint(Point::ZERO);
	news->setPosition(Point(720, 50));//���ù����������ݵĳ�ʼλ��
	schedule(schedule_selector(PannelNews::scrollText));//ʵ�ֹ������ֹ���
}

void PannelNews::scrollText(float)
{
	news->getPosition().x < (-1 * news->getContentSize().width) ? news->setPositionX(720) : news->setPositionX(news->getPositionX() - 2);
}