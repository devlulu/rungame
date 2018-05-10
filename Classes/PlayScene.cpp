#include "PlayScene.h"
#include "SimpleAudioEngine.h"
#include <string>
USING_NS_CC;

bool PlayScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->background_layer = BackgroundLayer::create();
	this->addChild(background_layer, 0);
	this->background_layer->setPosition(origin.x, origin.y);
	this->setZOrder(0);

	this->play_layer = PlayLayer::create();
	this->addChild(play_layer, 0);
	this->play_layer->setPosition(origin.x, origin.y);
	this->setZOrder(1);

	return true;
}
