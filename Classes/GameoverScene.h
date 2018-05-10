#pragma once
#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "PlayLayer.h"
using namespace cocos2d;

class GameoverScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(GameoverScene);
	
private:
	virtual bool init() override;


};
