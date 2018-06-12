#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "PlayScene.h"
USING_NS_CC;

#define MAXNUM 25

class LoadingScene : public Scene
{
public:

	LoadingScene();
	~LoadingScene();

	virtual bool init();

	CREATE_FUNC(LoadingScene);

	void onEnter() override;

private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	
	Label *loadTTF;
	void loadingTTF();
	int loadingNum = 0;
	void loadingCallBack(Texture2D* pTexture);
	void loadingImage();

	ProgressTimer* progress;
};
