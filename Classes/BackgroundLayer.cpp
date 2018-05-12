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
벽생성 스케쥴러
*/
void BackgroundLayer::UpdateWall(float dt)
{
	Sprite *LeftWall = NULL;
	Sprite *RightWall = NULL;

	//벽 생성(+패턴검사)
	CreateWall(&LeftWall, &RightWall);

	/*
	왼쪽 벽 설정
	*/
	this->addChild(LeftWall);
	//왼쪽 벽 액션
	auto LeftAction1 = MoveTo::create(DownSpeed, Point(winSize.width / 2, -winSize.height));
	auto LeftAction2 = RemoveSelf::create();
	auto LeftAction3 = Sequence::create(LeftAction1, LeftAction2, nullptr);
	LeftWall->runAction(LeftAction3);

	/*
	오른쪽 벽 설정
	*/
	if (RightWall != NULL) {
		this->addChild(RightWall);

		//오른쪽 벽 액션
		auto RightAction1 = MoveTo::create(DownSpeed, Point(winSize.width / 2, -winSize.height));
		auto RightAction2 = RemoveSelf::create();
		auto RightAction3 = Sequence::create(RightAction1, RightAction2, nullptr);
		RightWall->runAction(RightAction3);
	}
}

/*
	스프라이트 벽 생성 후
	포인터 매개변수 저장
*/
void BackgroundLayer::CreateWall(Sprite ** Left, Sprite ** Right)
{
	//난수함수로 패턴 결정	
	char LeftPath[100] = { 0, };
	char RightPath[100] = { 0, };
	int pattern = 0;

	//현재 패턴이 만족할 때까지 무한 루프
	do {
		pattern = rand() % 5 + 1;
	} while (CheckWallPattern(pattern) == false);

	//이미지 경로 불러오기
	sprintf(LeftPath, "%s%d.png", "wall/left/", pattern);
	sprintf(RightPath, "%s%d.png", "wall/right/", pattern);

	//왼쪽 벽 설정
	*Left = Sprite::create(LeftPath);
	(*Left)->setScaleX(winSize.width / (*Left)->getContentSize().width);
	(*Left)->setScaleY(winSize.height / (*Left)->getContentSize().height);
	(*Left)->setPosition(winSize.width / 2, winSize.height * 1.5);

	/*
		물리엔진 테스트
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

	//오른쪽 벽 설정
	if (pattern != 1) {
		*Right = Sprite::create(RightPath);
		(*Right)->setPosition(winSize.width/2, winSize.height * 1.5);
		(*Right)->setScaleX(winSize.width / (*Right)->getContentSize().width);
		(*Right)->setScaleY(winSize.height / (*Right)->getContentSize().height);
	}

	LastPattern = pattern;
}

/*
	패턴 검사
	패턴을 만족하지 않으면(다음 패턴을 생성할 수 없으면) false리턴
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
	//1번 블록 패턴
	for (int i = 1; i <= 6; i++)
		PossiblePattern[1].p.push_back(i);

	//2번 블록 패턴
	for (int i = 1; i <= 6; i++)
	{
		if (i == 3 || i == 4 || i == 5)
			continue;
		PossiblePattern[2].p.push_back(i);
	}

	//3번 블록 패턴
	for (int i = 1; i <= 6; i++)
	{
		if (i == 2 || i == 6)
			continue;
		PossiblePattern[3].p.push_back(i);
	}

	//4번 블록 패턴
	for (int i = 1; i <= 6; i++)
	{
		if (i == 5)
			continue;
		PossiblePattern[4].p.push_back(i);
	}

	//5번 블록 패턴
	for (int i = 1; i <= 6; i++)
	{
		if (i == 3 || i == 5)
			continue;
		PossiblePattern[5].p.push_back(i);
	}

	//6번 블록 패턴
	for (int i = 1; i <= 6; i++)
	{
		if (i == 2 || i == 6)
			continue;
		PossiblePattern[6].p.push_back(i);
	}
}

/*
	배경화면 초기화
*/
void BackgroundLayer::initBackground()
{
	auto bgLayer = Layer::create();
	this->addChild(bgLayer);

	//레이어에 배경 추가 
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

	//레이어 액션 추가
	auto action = Sequence::create(
		MoveBy::create(10.0f, Point(0, -bgSprite->getContentSize().height)),
		Place::create(Point::ZERO),
		NULL
	);
	auto repeataction = RepeatForever::create(action);

	bgLayer->runAction(repeataction);
}