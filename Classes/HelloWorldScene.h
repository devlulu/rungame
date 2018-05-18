#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__



#include "cocos2d.h"



USING_NS_CC;



class HelloWorld : public cocos2d::LayerColor

{

public:

	static cocos2d::Scene* createScene();



	virtual bool init();



	CREATE_FUNC(HelloWorld);



	// Add ----------------------------------------------------------

	PhysicsWorld* m_world;



	void setPhyWorld(PhysicsWorld* world) { m_world = world; }



	virtual bool onTouchBegan(Touch *touch, Event * event);

	virtual void onTouchEnded(Touch *touch, Event * event);



	Sprite* makePolygon(Vec2 point);

};



#endif // __HELLOWORLD_SCENE_H__
	