#include "cocos2d.h"
#include <time.h>
#include <stdlib.h>
#include "MyBodyParser.h"
#include "DataManager.h"
USING_NS_CC;

#pragma once
#define TAG_SPRITE_PLAYER		1000
#define MOVESPEED	2
class PlayLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(PlayLayer);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* Player;
	/*bool Count = true;*/
	int Count = 0;

private:
	virtual bool init() override;

	//터치 이벤트
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);

	Action* currentAction = nullptr;

	void initPlayer();

	void initTimer();
	void timeTick(float t);
	int score = 0;
	bool scoreFlag = false;
	Label *timeScore;


	Size winSize;
};