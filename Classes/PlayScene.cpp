#include "PlayScene.h"
#include "BackgroundLayer.h"
#include "MyBodyParser.h"
#include "PlayLayer.h"
#include "GameoverScene.h"

cocos2d::Scene * PlayScene::createScene()
{
	//�������� �� �߰�
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	//�������� ���̾� �߰�
	auto layer = PlayScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);

	return scene;
}

bool PlayScene::init()
{
	if (!Scene::init())
		return false;
		
	bgLayer = BackgroundLayer::create();
	this->addChild(bgLayer);

	CharacterLayer = PlayLayer::create();
	this->addChild(CharacterLayer);	

	/*
		�������� �浹
	*/
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PlayScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//scheduleUpdate() �޼ҵ带 ����Ͽ� Update() �޼ҵ带 ȣ��.
	this->scheduleUpdate();

	return true;	
}

/*
	�������� �浹 �� �߻� �̺�Ʈ
*/
bool PlayScene::onContactBegin(PhysicsContact & contact)
{
	auto sp1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto sp2 = (Sprite*)contact.getShapeB()->getBody()->getNode();
	//MessageBox("", "");

	Scene *pScene = GameoverScene::createScene();
	Director::getInstance()->replaceScene(pScene);
	return true;
}

void PlayScene::update(float dt)
{
	intersect();
}

void PlayScene::intersect()
{
	//auto sprPlayer = (Sprite*)this->getChildByTag(TAG_SPRITE_PLAYER);
	Rect rectPlayer = CharacterLayer->Player->getBoundingBox();

	Rect rectWall = bgLayer->intersectWallRight->getBoundingBox();
	Rect rectWall2 = bgLayer->intersectWallLeft->getBoundingBox();

	if (rectPlayer.intersectsRect(rectWall) || rectPlayer.intersectsRect(rectWall2))
	{
		//CharacterLayer->CollisionCheck->setTexture(Director::getInstance()->getTextureCache()->addImage("Images/collision_On.png"));
		Scene *pScene = GameoverScene::createScene();
		Director::getInstance()->replaceScene(pScene);
	}
}