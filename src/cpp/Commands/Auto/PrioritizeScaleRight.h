//
// Created by robotics on 1/27/2018.
//

#ifndef NEWPOWERUP_AUTOPRIORITIZESCALERIGHT_H
#define NEWPOWERUP_AUTOPRIORITIZESCALERIGHT_H

#include "../../CommandBase.h"
#include "../../PID.h"


class AutoPrioritizeScaleRight : public CommandBase {
public:
	AutoPrioritizeScaleRight();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

	int Step;
};


#endif //NEWPOWERUP_AUTOPRIORITIZESWITCHLEFT_H
