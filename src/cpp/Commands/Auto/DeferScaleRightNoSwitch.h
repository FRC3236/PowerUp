//
// Created by robotics on 3/23/2018.
//

#ifndef NEWPOWERUP_DEFERSCALERIGHTNOSWITCH_H
#define NEWPOWERUP_DEFERSCALERIGHTNOSWITCH_H

#include "../../CommandBase.h"
#include "../../PID.h"

class DeferScaleRightNoSwitch: public CommandBase {
private:
	Timer * AutoTimer;
	int Step;
public:
	DeferScaleRightNoSwitch();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};


#endif //NEWPOWERUP_DEFERSCALERIGHTNOSWITCH_H
