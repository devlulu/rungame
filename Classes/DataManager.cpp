#include "DataManager.h"

DataManager* DataManager::mInstance = nullptr;

DataManager* DataManager::getInstance()
{
	if (!mInstance) {
		mInstance = new DataManager();
	}
	return mInstance;
}

