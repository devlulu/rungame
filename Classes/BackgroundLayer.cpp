#include "BackgroundLayer.h"
#include "MyBodyParser.h"

bool BackgroundLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	winSize = Director::getInstance()->getVisibleSize();
	/*DownSpeed = winSize.height * 0.015;
	BlockTimer = DownSpeed * 0.39;*/
	DownSpeed = 8.0;
	BlockTimer = 4.0f;
	LastPattern = 1;
	
	initBackground();
	//initWallPattern();
	this->schedule(schedule_selector(BackgroundLayer::UpdateWall), BlockTimer);

	return true;
}

/*
������ �����췯
*/
void BackgroundLayer::UpdateWall(float dt)
{
	Sprite *LeftWall = NULL;
	Sprite *RightWall = NULL;

	char wallPath[100] = { 0, };
	int n = 0;

	n = rand() % 8 + 1;
	sprintf(wallPath, "test/pattern%d.png", n);	
	Sprite *wall = Sprite::create(wallPath);
	wall->setPosition(Point(winSize.width / 2, winSize.height * 1.5));
	this->addChild(wall);

	auto action1 = MoveTo::create(13.0, Point(winSize.width / 2, -winSize.height * 1.5));
	auto action2 = RemoveSelf::create();
	auto action3 = Sequence::create(action1, action2, nullptr);
	wall->runAction(action3);

	/*
		������
	*/

	////�� ����(+���ϰ˻�)
	//CreateWall(&LeftWall, &RightWall);

	///*
	//���� �� ����
	//*/
	//this->addChild(LeftWall);
	////���� �� �׼�
	//auto LeftAction1 = MoveTo::create(DownSpeed, Point(winSize.width / 2, -winSize.height));
	//auto LeftAction2 = RemoveSelf::create();
	//auto LeftAction3 = Sequence::create(LeftAction1, LeftAction2, nullptr);
	//LeftWall->runAction(LeftAction3);

	///*
	//������ �� ����
	//*/
	//if (RightWall != NULL) {
	//	this->addChild(RightWall);

	//	//������ �� �׼�
	//	auto RightAction1 = MoveTo::create(DownSpeed, Point(winSize.width / 2, -winSize.height));
	//	auto RightAction2 = RemoveSelf::create();
	//	auto RightAction3 = Sequence::create(RightAction1, RightAction2, nullptr);
	//	RightWall->runAction(RightAction3);
	//}
}

/*
	��������Ʈ �� ���� ��
	������ �Ű����� ����
*/
void BackgroundLayer::CreateWall(Sprite ** Left, Sprite ** Right)
{
	//�����Լ��� ���� ����	
	char LeftPath[100] = { 0, };
	char RightPath[100] = { 0, };
	int pattern = 0;

	//���� ������ ������ ������ ���� ����
	do {
		pattern = rand() % 5 + 1;
	} while (CheckWallPattern(pattern) == false);

	//�̹��� ��� �ҷ�����
	sprintf(LeftPath, "%s%d.png", "left_wall_", pattern);
	sprintf(RightPath, "%s%d.png", "right_wall_", pattern);

	//���� �� ����
	*Left = Sprite::createWithSpriteFrameName(LeftPath);
	(*Left)->setPosition(winSize.width / 2, winSize.height * 1.5);
	//(*Left)->setScaleX(winSize.width / (*Left)->getContentSize().width);
	//(*Left)->setScaleY(winSize.height / (*Left)->getContentSize().height);

	/*
		���ʺ� ��������
	*/
	char jsonPath[100] = { 0, };
	sprintf(jsonPath, "wall/left/%d.json", pattern);
	MyBodyParser::getInstance()->parseJsonFile(jsonPath);
	auto body = MyBodyParser::getInstance()->bodyFormJson((*Left), "Name");
	if (body != nullptr) {
		body->setDynamic(true);
		body->setMass(100.0f);
		body->setCategoryBitmask(0x04);    // 0100
		body->setContactTestBitmask(0x01); // 0001
		body->setCollisionBitmask(0x00);   // 0000
		(*Left)->setPhysicsBody(body);
	}

	//������ �� ����
	if (pattern != 1) {
		*Right = Sprite::createWithSpriteFrameName(RightPath);
		(*Right)->setPosition(winSize.width / 2, winSize.height * 1.5);
		//(*Right)->setScaleX(winSize.width / (*Right)->getContentSize().width);
		//(*Right)->setScaleY(winSize.height / (*Right)->getContentSize().height);

		char jsonPath[100] = { 0, };
		sprintf(jsonPath, "wall/right/%d.json", pattern);
		MyBodyParser::getInstance()->parseJsonFile(jsonPath);
		auto body = MyBodyParser::getInstance()->bodyFormJson((*Right), "Name");
		if (body != nullptr) {
			body->setDynamic(true);
			body->setMass(100.0f);
			body->setCategoryBitmask(0x04);    // 0100
			body->setContactTestBitmask(0x01); // 0001
			body->setCollisionBitmask(0x00);   // 0000
			(*Right)->setPhysicsBody(body);
		}
	}

	LastPattern = pattern;
}

/*
	���� �˻�
	������ �������� ������(���� ������ ������ �� ������) false����
*/
bool BackgroundLayer::CheckWallPattern(short pattern)
{
	std::vector<int>::iterator end = PossiblePattern[LastPattern].p.end();
	std::vector<int>::iterator begin = PossiblePattern[LastPattern].p.begin();

	for (std::vector<int>::iterator iterPos = begin; iterPos != end; ++iterPos) {
		if (*iterPos == pattern)
			return true;
	}

	return false;
}

void BackgroundLayer::initWallPattern()
{
	//1�� ��� ����
	for (int i = 1; i <= 6; i++)
		PossiblePattern[1].p.push_back(i);

	//2�� ��� ����
	for (int i = 1; i <= 6; i++)
	{
		if (i == 3 || i == 4 || i == 5)
			continue;
		PossiblePattern[2].p.push_back(i);
	}

	//3�� ��� ����
	for (int i = 1; i <= 6; i++)
	{
		if (i == 2 || i == 6)
			continue;
		PossiblePattern[3].p.push_back(i);
	}

	//4�� ��� ����
	for (int i = 1; i <= 6; i++)
	{
		if (i == 5)
			continue;
		PossiblePattern[4].p.push_back(i);
	}

	//5�� ��� ����
	for (int i = 1; i <= 6; i++)
	{
		if (i == 3 || i == 5)
			continue;
		PossiblePattern[5].p.push_back(i);
	}

	//6�� ��� ����
	for (int i = 1; i <= 6; i++)
	{
		if (i == 2 || i == 6)
			continue;
		PossiblePattern[6].p.push_back(i);
	}
}

/*
	���ȭ�� �ʱ�ȭ
*/
void BackgroundLayer::initBackground()
{
	////��� -> ����
	//SpriteFrameCache::getInstance()->addSpriteFrame(Sprite::create("background/bg.png")->getDisplayFrame(), "bg"); 
	//auto bg = Sprite::createWithSpriteFrameName("bg");
	//bg->setAnchorPoint(Point::ZERO);
	//this->addChild(bg);

	//auto node = ParallaxNode::create();
	//this->addChild(node);

	//auto action_1 = MoveBy::create(20.0f, Point(0, -1920));
	//auto action_2 = Place::create(Point::ZERO);
	//auto action_3 = Sequence::create(action_1, action_2, NULL);
	//auto action = RepeatForever::create(action_3);
	//node->runAction(action);

	//// ���� ? ���ΰ�? -> �з����� ���� ������
	//auto bg_1 = Sprite::create("background/star.png");
	//bg_1->setAnchorPoint(Point::ZERO);
	//node->addChild(bg_1, 0, Point(0, 1), Point::ZERO);

	///*auto bg_2 = Sprite::create("star.png", Rect(0,0,1080,1920));
	//bg_2->setAnchorPoint(Point::ZERO);
	//node->addChild(bg_2, 0, Point(0, 1), Point(0, 1920));*/

	auto bg = Sprite::create("test/BG.png");
	bg->setAnchorPoint(Point::ZERO);
	this->addChild(bg);

	//�� �߰�
	/*intersectWallLeft = Sprite::create("wall/intersectWallLeft.png");
	intersectWallLeft->setPosition(Vec2(-10, winSize.height / 2));
	this->addChild(intersectWallLeft);

	intersectWallRight = Sprite::create("wall/intersectWallRight.png");
	intersectWallRight->setPosition(Vec2(winSize.width + 10, winSize.height / 2));
	this->addChild(intersectWallRight);*/
}