//
// Created by robotics on 1/13/2018.
//

#ifndef NEWPOWERUP_RESETGYRO_H
#define NEWPOWERUP_RESETGYRO_H
#include "../CommandBase.h"

class ResetGyro : public CommandBase {
public:
	ResetGyro();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};


#endif //NEWPOWERUP_RESETGYRO_H
