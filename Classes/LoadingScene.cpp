#include "LoadingScene.h"
LoadingScene::LoadingScene() {}

LoadingScene::~LoadingScene() {}

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	onEnter();
	loadingImage();

	
	return true;
}

void LoadingScene::onEnter()
{
	Scene::onEnter();
}

void LoadingScene::loadingImage() {

	auto progressSprite = Sprite::create("loadingbar.png");
	progress = ProgressTimer::create(progressSprite);
	progress->setType(ProgressTimerType::BAR);
	progress->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - visibleSize.height / 2));
	progress->setMidpoint(Vec2(0, 0));
	progress->setBarChangeRate(Vec2(1,0));
	progress->setPercentage(0);
	this->addChild(progress,4);

	loadTTF = Label::createWithSystemFont("0%", "Arial", (visibleSize.height / visibleSize.width) * 50, Size(visibleSize.width, 300), TextHAlignment::CENTER, TextVAlignment::CENTER);
	loadTTF->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - visibleSize.height / 2));
	loadTTF->setScale(0.8f);
	loadTTF->setColor(Color3B(0, 255, 255));
	this->addChild(loadTTF, 4);

	/* Test */
	Director::getInstance()->getTextureCache()->addImageAsync("HelloWorld.png",CC_CALLBACK_1(LoadingScene::loadingCallBack, this));

	/* Resource folder */
	Director::getInstance()->getTextureCache()->addImageAsync("restart_off.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("restart_on.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("timerBG.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));

	/* background folder */
	Director::getInstance()->getTextureCache()->addImageAsync("background/bg.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("background/bg2.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("background/star.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("background/test.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	
	/* Image folder */
	Director::getInstance()->getTextureCache()->addImageAsync("Image/arrow1.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Image/arrow11.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Image/arrow2.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));

	/* wall folder */
	Director::getInstance()->getTextureCache()->addImageAsync("wall/intersectWallLeft.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/intersectWallRight.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/wall.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));

	Director::getInstance()->getTextureCache()->addImageAsync("wall/left/left_wall_1.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/left/left_wall_2.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/left/left_wall_3.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/left/left_wall_4.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/left/left_wall_5.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/left/left_wall_6.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	
	Director::getInstance()->getTextureCache()->addImageAsync("wall/right/right_wall_2.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/right/right_wall_3.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/right/right_wall_4.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/right/right_wall_5.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/right/right_wall_6.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));

}

void LoadingScene::loadingTTF() {
	char strNum[100] = "";
	int percent = (int)(((float)++loadingNum / MAXNUM) * 100);
	sprintf(strNum, "%d%%", percent);
	progress->setPercentage(percent);

	loadTTF->setString(strNum);
}

void LoadingScene::loadingCallBack(Texture2D* pTexture)
{
	loadingTTF();

	if (loadingNum == MAXNUM) {
		auto scene = PlayScene::createScene();
		TransitionScene* pTransition = TransitionFade::create(3, scene);
		Director::getInstance()->replaceScene(pTransition);
	}
}