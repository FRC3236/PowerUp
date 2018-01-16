//
// Created by robotics on 1/16/2018.
//

#ifndef NEWPOWERUP_AUTOPRIORITIZESWITCHLEFT_H
#define NEWPOWERUP_AUTOPRIORITIZESWITCHLEFT_H

#include "../CommandBase.h"


class AutoPrioritizeSwitchLeft : public CommandBase {
public:
	AutoPrioritizeSwitchLeft();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

	int Step;
};


#endif //NEWPOWERUP_AUTOPRIORITIZESWITCHLEFT_H
