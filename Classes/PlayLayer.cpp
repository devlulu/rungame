#include "PlayLayer.h"

#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace cocos2d;

USING_NS_CC;

Scene* PlayLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = PlayLayer::create();

	scene->addChild(layer);

	return scene;
}


bool PlayLayer::init()
{
	if (!Layer::init())
	//if (!LayerColor::initWithColor(Color4B(255, 220, 220, 255)))
	//{
		return false;
	//}

	initPlayer();

	// initalize Touch events
	auto listener = EventListenerTouchOneByOne::create();
	//listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void PlayLayer::initPlayer() {

	Point center = Point(240, 160);

	Player = Sprite::create("Images/arrow1.png");
	Player->setScale(0.5);
	Player->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	Player->setTag(TAG_SPRITE_PLAYER);

	this->addChild(Player, 1);

}


bool PlayLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {

	if (currentAction)
		Player->stopAction(currentAction);

	auto action1 = RotateTo::create(0.5, -90);
	auto action2 = MoveTo::create(MOVESPEED, Point(0 , visibleSize.height / 2));
	auto spawn = Spawn::create(action1, action2, NULL);
	currentAction = Player->runAction(spawn);

	return true;
}

void PlayLayer::onTouchMoved(Touch* touch, Event* event) {

}

void PlayLayer::onTouchEnded(Touch* touch, Event* event) {
	if (currentAction)
		Player->stopAction(currentAction);

	auto action1 = RotateTo::create(0.5, 0);
	auto action2 = MoveTo::create(MOVESPEED, Point(visibleSize.width, visibleSize.height / 2));
	auto spawn = Spawn::create(action1, action2, NULL);
	currentAction = Player->runAction(spawn);


}

void PlayLayer::onTouchCancelled(Touch* touch, Event* event) {

}
