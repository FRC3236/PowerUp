//
// Created by robotics on 1/16/2018.
//

#ifndef NEWPOWERUP_AUTOPRIORITIZESWITCHLEFT_H
#define NEWPOWERUP_AUTOPRIORITIZESWITCHLEFT_H

#include "../../CommandBase.h"
#include "../../PID.h"


class AutoPrioritizeSwitchLeft : public CommandBase {
public:
	AutoPrioritizeSwitchLeft();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

	PID * pid;
	int Step;
};


#endif //NEWPOWERUP_AUTOPRIORITIZESWITCHLEFT_H
