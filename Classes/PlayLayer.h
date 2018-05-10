#pragma once
#include "cocos2d.h"
using namespace cocos2d;

USING_NS_CC;

#define TAG_SPRITE_PLAYER		1000
#define MOVESPEED	3
class PlayLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	CREATE_FUNC(PlayLayer);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size winSize;

private:
	virtual bool init() override;
	void initPlayer();

	//스프라이트 정리
	Sprite* Player;
	Point touchPoint;

	Vec2 mLatestInputPos;			//터치 시, 필요한 변수

									//touch func
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);

	Action* currentAction = nullptr;
};