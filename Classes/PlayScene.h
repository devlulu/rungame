#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class PlayScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(PlayScene);
	static cocos2d::Scene* createScene();
private:
	virtual bool init() override;

	/*
		물리엔진
	*/
	void SetPhysicsWorld(PhysicsWorld *_world) { world = _world; };
	PhysicsWorld *world;
	bool onContactBegin(PhysicsContact& contact);
};