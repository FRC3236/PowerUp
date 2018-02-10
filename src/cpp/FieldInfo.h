//
// Created by robotics on 2/1/2018.
//

#ifndef NEWPOWERUP_FIELDINFO_H
#define NEWPOWERUP_FIELDINFO_H
#include <utility>

class FieldInfo {
private:
	int Switch, Scale;

public:
	FieldInfo();
	void SetInformation(int,int);
	void SetInformation();
	int GetScale();
	int GetSwitch();
	std::pair<int,int> GetFieldInfo();
};


#endif //NEWPOWERUP_FIELDINFO_H
