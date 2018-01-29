//
// Created by robotics on 1/23/2018.
//

#ifndef NEWPOWERUP_AUTOPRIORITIZESCALELEFT_H
#define NEWPOWERUP_AUTOPRIORITIZESCALELEFT_H

#include "../../CommandBase.h"
#include "../../PID.h"


class AutoPrioritizeScaleLeft : public CommandBase {
public:
	AutoPrioritizeScaleLeft();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

	int Step;
};


#endif //NEWPOWERUP_AUTOPRIORITIZESWITCHLEFT_H
