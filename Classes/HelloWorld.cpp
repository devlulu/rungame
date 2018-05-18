#include "HelloWorld.h"



USING_NS_CC;



Scene* HelloWorld::createScene()

{

	//auto scene = Scene::create();    

	//auto layer = HelloWorld::create();

	//scene->addChild(layer);



	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vect gravity = Vect(0.0f, -300.0f);



	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	scene->getPhysicsWorld()->setGravity(gravity);



	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

	auto edgeNode = Node::create();

	edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

	edgeNode->setPhysicsBody(body);

	scene->addChild(edgeNode);



	auto layer = HelloWorld::create();

	layer->setPhyWorld(scene->getPhysicsWorld());



	scene->addChild(layer);





	return scene;

}



bool HelloWorld::init()

{

	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))

	{

		return false;

	}



	/////////////////////////////



	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);

	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);





	return true;

}



bool HelloWorld::onTouchBegan(Touch *touch, Event * event)

{

	return true;

}



void HelloWorld::onTouchEnded(Touch *touch, Event * event)

{

	auto location = touch->getLocation();

	addNewSpriteAtPosition(location);

}



void HelloWorld::addNewSpriteAtPosition(Point p)

{

	// ��������Ʈ �����

	auto sprite = Sprite::create("CloseSelected.png");

	sprite->setPosition(p);



	// ��������Ʈ�� ũ�⸸ŭ ���� ��ü�� �ٵ� �����

	auto material1 = PhysicsMaterial(0.0f, 0.0f, 0.0f);

	auto material2 = PhysicsMaterial(0.0f, 1.0f, 0.1f);



	auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2,

		material2);

	// �ٵ��� ���� ���ϱ�

	body->setMass(100.0f);



	// ��������Ʈ�� ���� ��ü�� �ٵ� ����

	sprite->setPhysicsBody(body);



	this->addChild(sprite);

}
