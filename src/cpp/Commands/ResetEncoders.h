//
// Created by robotics on 2/1/2018.
//

#ifndef NEWPOWERUP_RESETENCODERS_H
#define NEWPOWERUP_RESETENCODERS_H
#include "../CommandBase.h"

class ResetEncoders : public CommandBase {
public:
	ResetEncoders();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};


#endif //NEWPOWERUP_RESETENCODERS_H
