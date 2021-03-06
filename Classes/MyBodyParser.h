//
//  MyBodyParser.h
//
//  Created by Jason Xu.
//
//
#include <string>
#include "cocos2d.h"
USING_NS_CC;
#include "json/document.h"
#pragma once



class MyBodyParser {
    MyBodyParser(){}
    rapidjson::Document doc;
public:
    static MyBodyParser* getInstance();
    bool parseJsonFile(const std::string& pFile);
    bool parse(unsigned char* buffer, long length);
    void clearCache();
    PhysicsBody* bodyFormJson(Node* pNode, const std::string& name);
};