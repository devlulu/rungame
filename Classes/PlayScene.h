#pragma once
#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "PlayLayer.h"
using namespace cocos2d;

class PlayScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(PlayScene);

	BackgroundLayer *getBackgroundLayer();
	PlayLayer *getPlayLayer();
	
private:
	virtual bool init() override;

	BackgroundLayer *background_layer;
	PlayLayer *play_layer;


};
