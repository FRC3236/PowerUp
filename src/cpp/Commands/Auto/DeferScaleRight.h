//
// Created by robotics on 3/23/2018.
//

#ifndef NEWPOWERUP_DEFERSCALERIGHT_H
#define NEWPOWERUP_DEFERSCALERIGHT_H

#include "../../CommandBase.h"
#include "../../PID.h"

class DeferScaleRight : public CommandBase {
private:
	Timer * AutoTimer;
	int Step;
public:
	DeferScaleRight();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};


#endif //NEWPOWERUP_DEFERSCALERIGHT_H
