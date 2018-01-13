//
// Created by robotics on 1/13/2018.
//

#ifndef NEWPOWERUP_DONOTHING_H
#define NEWPOWERUP_DONOTHING_H
#include "../CommandBase.h"

class DoNothing : public CommandBase {
public:
	DoNothing();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};


#endif //NEWPOWERUP_DONOTHING_H
