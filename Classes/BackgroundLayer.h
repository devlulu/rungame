#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class BackgroundLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(BackgroundLayer);

	Sprite *intersectWallLeft;
	Sprite *intersectWallRight;

	PhysicsWorld* m_world;
	void setPhyWorld(PhysicsWorld* world) { m_world = world; }

private:
	virtual bool init() override;
	void initBackground();

	void CreateWall(Sprite** Left, Sprite** Right);
	bool CheckWallPattern(short pattern);
	void initWallPattern();
	void UpdateWall(float dt);

	typedef struct PATTERN {
		std::vector <int> p;
	}PATTERN;
	PATTERN PossiblePattern[7];

	Size winSize;
	short LastPattern;
	float DownSpeed;
	float BlockTimer;
};