#include "GameoverScene.h"
#include "SimpleAudioEngine.h"
#include <string>
USING_NS_CC;

bool GameoverScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	

	return true;
}
