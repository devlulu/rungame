#include "PlayScene.h"
#include "BackgroundLayer.h"
#include "MyBodyParser.h"
#include "PlayLayer.h"

cocos2d::Scene * PlayScene::createScene()
{
	//�������� �� �߰�
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

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

	auto bgLayer = BackgroundLayer::create();
	this->addChild(bgLayer);

	auto CharacterLayer = PlayLayer::create();
	this->addChild(CharacterLayer);
	
	/*
		�������� �浹
	*/
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PlayScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;	
}

/*
	�������� �浹 �� �߻� �̺�Ʈ
*/
bool PlayScene::onContactBegin(PhysicsContact & contact)
{
	auto sp1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto sp2 = (Sprite*)contact.getShapeB()->getBody()->getNode();
	MessageBox("", "");

	return true;
}
