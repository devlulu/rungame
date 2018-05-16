#pragma once
class DataManager {

private:

	static DataManager* mInstance;
	DataManager() { ; };
	

	int score;

public:
	static DataManager* getInstance();

	void setScore(int n);
	int getScore();
};



