#include "PlayLayer.h"
#include "MyBodyParser.h"
#include <time.h>
#include <stdlib.h>

bool PlayLayer::init()
{
	if (!Layer::init())
		return false;

	initPlayer();
	initTimer();

	// initalize Touch events
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}



void PlayLayer::initPlayer() {

	Point center = Point(240, 160);

	Player = Sprite::create("Images/arrow1.png");
	Player->setScale(0.3);
	Player->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	Player->setTag(TAG_SPRITE_PLAYER);

	/*
		물리엔진 추가
	*/
	
	MyBodyParser::getInstance()->parseJsonFile("Images/arrow1.json");
	auto body = MyBodyParser::getInstance()->bodyFormJson(Player, "name");
	if (body != nullptr) {
		body->setCategoryBitmask(0x01);    // 0001
		body->setContactTestBitmask(0x04); // 0100
		body->setCollisionBitmask(0x03);   // 0011		
		Player->setPhysicsBody(body);
	}

	this->addChild(Player, 1);
}

void PlayLayer::initTimer() {

	Sprite *timerBackground = Sprite::create("timerBG.png");
	timerBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - visibleSize.height / 5));
	timerBackground->setOpacity(60);
	timerBackground->setScale(visibleSize.height /visibleSize.width);
	this->addChild(timerBackground, 3);

	timeScore = Label::createWithSystemFont("0", "Arial", (visibleSize.height / visibleSize.width) * 50, Size(visibleSize.width, 300), TextHAlignment::CENTER, TextVAlignment::CENTER);
	timeScore->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - visibleSize.height/5));
	timeScore->setColor(Color3B(0,0,0));
	this->addChild(timeScore, 4);

}

void PlayLayer::timeTick(float t) {
	char strScore[100] = "";
	sprintf(strScore, "%d", ++score);
	timeScore->setString(strScore);
}

bool PlayLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {

	if (currentAction)
		Player->stopAction(currentAction);

	auto action1 = RotateTo::create(0.4, -90);
	auto action2 = MoveTo::create(MOVESPEED, Point(0 , visibleSize.height / 2));
	auto action3 = EaseIn::create(action2, 1.5);
	auto spawn1 = Spawn::create(action1, action2, action3, NULL);
	currentAction = Player->runAction(spawn1);

	if (!scoreFlag) {
		scoreFlag = true;
		this->schedule(schedule_selector(PlayLayer::timeTick), 0.1);
	}

	return true;
}

void PlayLayer::onTouchMoved(Touch* touch, Event* event) {

}

void PlayLayer::onTouchEnded(Touch* touch, Event* event) {
	if (currentAction)
		Player->stopAction(currentAction);

	auto action1 = RotateTo::create(0.4, 0);
	auto action2 = MoveTo::create(MOVESPEED, Point(visibleSize.width, visibleSize.height / 2));
	auto action3 = EaseIn::create(action2, 1.5);
	auto spawn2 = Spawn::create(action1, action2, action3, NULL);
	currentAction = Player->runAction(spawn2);
}

void PlayLayer::onTouchCancelled(Touch* touch, Event* event) {

}
