//
// Created by robotics on 1/16/2018.
//

#ifndef NEWPOWERUP_AUTOPRIORITIZESWITCHRIGHT_H
#define NEWPOWERUP_AUTOPRIORITIZESWITCHRIGHT_H

#include "../../CommandBase.h"


class AutoPrioritizeSwitchRight : public CommandBase {
public:
	AutoPrioritizeSwitchRight();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

	int Step;
};


#endif //NEWPOWERUP_AUTOPRIORITIZESWITCHLEFT_H
