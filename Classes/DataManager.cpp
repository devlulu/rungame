#include "DataManager.h"

DataManager* DataManager::mInstance = nullptr;

DataManager* DataManager::getInstance()
{
	if (!mInstance) {
		mInstance = new DataManager();
	}
	return mInstance;
}

void DataManager::setScore(int n) {
	score = n;
}

int DataManager::getScore() {
	return score;
}