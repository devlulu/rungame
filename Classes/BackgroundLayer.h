#pragma once
#include "cocos2d.h"
#define TAG_SPRITE_WALL 1
#define BLOCK_PATTERN 12
using namespace cocos2d;

#define DOWNSPEED 6.5f

class BackgroundLayer : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(BackgroundLayer);
	void initBackground();	
	void initPattern();
	void CreateBlock(Sprite** Left, Sprite** Right);
	void update(float delta);
	bool CheckPattern(int pattern);
		
private:
	virtual bool init() override;
	typedef struct PATTERN {
		std::vector <int> p;
	}PATTERN;

	Size winSize;	
	int LastPattern;
	PATTERN PossiblePattern[7];
};