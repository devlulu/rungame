#pragma once
#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "PlayLayer.h"
#include "DataManager.h"
#include "PlayScene.h"
using namespace cocos2d;

class GameoverScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(GameoverScene);
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
private:
	virtual bool init() override;
	void initTimer();
	Label *timeScore;
	void initRestart();
	void restartButtonCallback(Ref* pSender);
};
