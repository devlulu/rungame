#include "GameoverScene.h"
#include "SimpleAudioEngine.h"
#include <string>
USING_NS_CC;

Scene* GameoverScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameoverScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameoverScene::init()
{
	if (!LayerColor::initWithColor(Color4B(255,255,255,255)))
	{
		return false;
	}

	initTimer();
	initRestart();
	return true;
}


void GameoverScene::initTimer() {

	Sprite *timerBackground = Sprite::create("timerBG.png");
	timerBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - visibleSize.height / 5));
	timerBackground->setOpacity(60);
	timerBackground->setScale(visibleSize.height / visibleSize.width);
	this->addChild(timerBackground, 3);

	char resultScore[100];
	DataManager *dataManager = DataManager::getInstance();
	sprintf(resultScore, "%d", dataManager->getScore());
	timeScore = Label::createWithSystemFont(resultScore, "Arial", (visibleSize.height / visibleSize.width) * 50, Size(visibleSize.width, 300), TextHAlignment::CENTER, TextVAlignment::CENTER);
	timeScore->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - visibleSize.height / 5));
	timeScore->setColor(Color3B(0, 0, 0));
	this->addChild(timeScore, 4);

}

void GameoverScene::initRestart() {
	auto btn = MenuItemImage::create("restart_on.png", "restart_off.png", CC_CALLBACK_1(GameoverScene::restartButtonCallback, this));
	auto menu = Menu::create(btn, NULL);
	menu->alignItemsVertically();
	this->addChild(menu);
}

void GameoverScene::restartButtonCallback(Ref* pSender) {
	Scene *pScene = PlayScene::createScene();
	Director::getInstance()->replaceScene(pScene);
}