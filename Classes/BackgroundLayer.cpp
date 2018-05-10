#include "BackgroundLayer.h"
using namespace cocos2d;

Scene* BackgroundLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = BackgroundLayer::create();
	scene->addChild(layer);
	return scene;
}

/*
	배경화면 추가
*/
void BackgroundLayer::initBackground()
{
	auto bgLayer = Layer::create();
	this->addChild(bgLayer);

	//레이어에 배경 추가 
	auto bgSprite = Sprite::create("b2.png");
	bgSprite->setAnchorPoint(Point::ZERO);
	bgSprite->setPosition(Point::ZERO);
	bgSprite->setScaleX(winSize.width / bgSprite->getContentSize().width);
	bgSprite->setScaleY(winSize.height / bgSprite->getContentSize().height);
	bgLayer->addChild(bgSprite);
	
	auto bgSprite2 = Sprite::create("b2.png", Rect(0, 0, winSize.width, winSize.height));
	bgSprite2->setAnchorPoint(Point::ZERO);
	bgSprite2->setPosition(Point(0, winSize.height));
	bgSprite2->setScaleX(winSize.width / bgSprite->getContentSize().width);
	bgSprite2->setScaleY(winSize.height / bgSprite->getContentSize().height);
	bgLayer->addChild(bgSprite2);
	
	//레이어 액션 추가
	auto action = Sequence::create(
		MoveBy::create(10.0f, Point(0, -winSize.height)),
		Place::create(Point::ZERO),
		NULL
	);
	auto repeataction = RepeatForever::create(action);

	bgLayer->runAction(repeataction);
}


void BackgroundLayer::CreateBlock(Sprite** Left, Sprite** Right)
{
	//난수함수로 패턴 결정	
	char LeftPath[100] = { 0, };
	char RightPath[100] = { 0, };
	int pattern = 0;

	do {
		pattern = rand() % 5 + 1;
		log("pattern : %d", pattern);
	} while (CheckPattern(pattern) == false);

	sprintf(LeftPath, "%s%d.png", "wall/left/", pattern);
	sprintf(RightPath, "%s%d.png", "wall/right/", pattern);

	*Left = Sprite::create(LeftPath);
	//(*Left)->setScale(0.5f);
	(*Left)->setAnchorPoint(Point(0, 0.5));
	(*Left)->setPosition(0, winSize.height / 2);

	if (pattern != 1) {
		*Right = Sprite::create(RightPath);
		//(*Right)->setScale(0.5f);
		(*Right)->setAnchorPoint(Point(1, 0.5));
		(*Right)->setPosition(winSize.width, winSize.height / 2);
	}	

	LastPattern = pattern;
}

/*
	패턴 검사
*/
bool BackgroundLayer::CheckPattern(int pattern)
{
	std::vector<int>::iterator end = PossiblePattern[LastPattern].p.end();
	std::vector<int>::iterator begin = PossiblePattern[LastPattern].p.begin();

	for (std::vector<int>::iterator iterPos = begin; iterPos != end; ++iterPos) {
		if (*iterPos == pattern)
			return true;
	}	

	return false;
}

void BackgroundLayer::initPattern()
{
	//1번 블록 패턴
	for(int i=1; i<=6; i++)
		PossiblePattern[1].p.push_back(i);
	
	//2번 블록 패턴
	for (int i = 1; i <= 6; i++)
	{
		if (i == 3 || i == 4 || i == 5)
			continue;
		PossiblePattern[2].p.push_back(i);
	}

	//3번 블록 패턴
	for (int i = 1; i <= 6; i++)
	{
		if (i == 2 || i == 6)
			continue;
		PossiblePattern[3].p.push_back(i);
	}

	//4번 블록 패턴
	for (int i = 1; i <= 6; i++)
	{
		if (i == 5)
			continue;
		PossiblePattern[4].p.push_back(i);
	}
	
	//5번 블록 패턴
	for (int i = 1; i <= 6; i++)
	{
		if (i == 3 || i == 5)
			continue;
		PossiblePattern[5].p.push_back(i);
	}

	//6번 블록 패턴
	for (int i = 1; i <= 6; i++)
	{
		if (i == 2 || i == 6)
			continue;
		PossiblePattern[6].p.push_back(i);
	}
}

void BackgroundLayer::update(float delta)
{
	Sprite *LeftWall = NULL;
	Sprite *RightWall = NULL;
	auto Layer1 = Layer::create();
	Layer1->setAnchorPoint(Point(0.5, 0.5));
	Layer1->setPositionY(winSize.height);
	this->addChild(Layer1);

	CreateBlock(&LeftWall, &RightWall);
	Layer1->addChild(LeftWall);
	if (RightWall != NULL)	Layer1->addChild(RightWall);

	auto action = Sequence::create(
		MoveTo::create(DOWNSPEED, Point(0, -winSize.height * 1.2)),
		RemoveSelf::create(),
		NULL
	);

	Layer1->runAction(action);
}


bool BackgroundLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(255,255,255,255))) {
		return false;
	}

	LastPattern = 1;
	srand(time(NULL));
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();
	winSize = Director::getInstance()->getVisibleSize();	

	initPattern();
	initBackground();	
	float scheduleSpeed = DOWNSPEED * 0.3;		
	this->schedule(schedule_selector(BackgroundLayer::update), scheduleSpeed);

	return true; 
}