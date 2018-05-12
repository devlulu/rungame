#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class BackgroundLayer : public cocos2d::LayerColor
{
public:
	CREATE_FUNC(BackgroundLayer);
	void initBackground();

private:
	virtual bool init() override;
	
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