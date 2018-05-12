#pragma once
#include "cocos2d.h"
USING_NS_CC;

#define TAG_SPRITE_PLAYER		1000
#define MOVESPEED	3
class PlayLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(PlayLayer);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	

	

private:
	virtual bool init() override;

	//터치 이벤트
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);

	Sprite* Player;
	Action* currentAction = nullptr;

	void initPlayer();
	Size winSize;
};