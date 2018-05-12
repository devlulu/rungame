#include "BackgroundLayer.h"
#include "MyBodyParser.h"

bool BackgroundLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	winSize = Director::getInstance()->getVisibleSize();
	DownSpeed = winSize.height * 0.015;
	BlockTimer = DownSpeed * 0.39;
	LastPattern = 1;

	initBackground();
	initWallPattern();
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

	//�� ����(+���ϰ˻�)
	CreateWall(&LeftWall, &RightWall);

	/*
	���� �� ����
	*/
	this->addChild(LeftWall);
	//���� �� �׼�
	auto LeftAction1 = MoveTo::create(DownSpeed, Point(winSize.width / 2, -winSize.height));
	auto LeftAction2 = RemoveSelf::create();
	auto LeftAction3 = Sequence::create(LeftAction1, LeftAction2, nullptr);
	LeftWall->runAction(LeftAction3);

	/*
	������ �� ����
	*/
	if (RightWall != NULL) {
		this->addChild(RightWall);

		//������ �� �׼�
		auto RightAction1 = MoveTo::create(DownSpeed, Point(winSize.width / 2, -winSize.height));
		auto RightAction2 = RemoveSelf::create();
		auto RightAction3 = Sequence::create(RightAction1, RightAction2, nullptr);
		RightWall->runAction(RightAction3);
	}
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
	sprintf(LeftPath, "%s%d.png", "wall/left/", pattern);
	sprintf(RightPath, "%s%d.png", "wall/right/", pattern);

	//���� �� ����
	*Left = Sprite::create(LeftPath);
	(*Left)->setScaleX(winSize.width / (*Left)->getContentSize().width);
	(*Left)->setScaleY(winSize.height / (*Left)->getContentSize().height);
	(*Left)->setPosition(winSize.width / 2, winSize.height * 1.5);

	/*
		�������� �׽�Ʈ
	*/
	char jsonPath[100] = { 0, };
	sprintf(jsonPath, "wall/left/%d.json", pattern);
	MyBodyParser::getInstance()->parseJsonFile(jsonPath);
	auto body = MyBodyParser::getInstance()->bodyFormJson((*Left), "name");
	if (body != nullptr) {
		body->setCategoryBitmask(0x04);    // 0100
		body->setContactTestBitmask(0x01); // 0001
		body->setCollisionBitmask(0x06);   // 0110
		(*Left)->setPhysicsBody(body);
	}

	//������ �� ����
	if (pattern != 1) {
		*Right = Sprite::create(RightPath);
		(*Right)->setPosition(winSize.width/2, winSize.height * 1.5);
		(*Right)->setScaleX(winSize.width / (*Right)->getContentSize().width);
		(*Right)->setScaleY(winSize.height / (*Right)->getContentSize().height);
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
	auto bgLayer = Layer::create();
	this->addChild(bgLayer);

	//���̾ ��� �߰� 
	auto bgSprite = Sprite::create("bg.png");
	bgSprite->setPosition(Point(winSize.width/2, winSize.height/2));
	bgSprite->setScaleX(winSize.width / bgSprite->getContentSize().width);
	bgSprite->setScaleY(winSize.height / bgSprite->getContentSize().height);
	bgLayer->addChild(bgSprite);

	auto bgSprite2 = Sprite::create("bg.png");
	bgSprite2->setPosition(Point(winSize.width / 2, winSize.height ));
	bgSprite2->setScaleX(winSize.width / bgSprite->getContentSize().width);
	bgSprite2->setScaleY(winSize.height / bgSprite->getContentSize().height);
	bgLayer->addChild(bgSprite2);

	//���̾� �׼� �߰�
	auto action = Sequence::create(
		MoveBy::create(10.0f, Point(0, -bgSprite->getContentSize().height)),
		Place::create(Point::ZERO),
		NULL
	);
	auto repeataction = RepeatForever::create(action);

	bgLayer->runAction(repeataction);
}