#include "HelloWorldScene.h"
#include "MyBodyParser.h"



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



	addChild(makePolygon(location));

}



Sprite* HelloWorld::makePolygon(Vec2 point)

{

	auto polygon = Sprite::create("f1.png");



	MyBodyParser::getInstance()->parseJsonFile("exam3.json");



	auto material = PhysicsMaterial(0.1f, 1.0f, 0.5f);

	auto body = MyBodyParser::getInstance()->bodyFormJson(polygon, "forward");



	if (body != nullptr) {



		polygon->setPhysicsBody(body);

		polygon->setPosition(Vec2(point.x, point.y));

	}



	return polygon;

}
