#pragma once

#if !defined(NOT_USE_GENERATOR)
#define GENERATE_GETSETTER(varType, parameter, memberVar) \
varType get##parameter() \
{ \
    return memberVar; \
} \
void set##parameter(varType parameter) \
{ \
    memberVar = parameter; \
}
#endif

class DataManager {

private:

	static DataManager* mInstance;
	DataManager() { ; };
	
	int m_score;

public:
	static DataManager* getInstance();

	GENERATE_GETSETTER(int, Score, m_score);
};



