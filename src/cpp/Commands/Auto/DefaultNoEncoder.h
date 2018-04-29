//
// Created by robotics on 4/27/2018.
//

#include "../../CommandBase.h"
#include <WPILib.h>
#ifndef NEWPOWERUP_DEFAULTNOENCODER_H
#define NEWPOWERUP_DEFAULTNOENCODER_H



class DefaultNoEncoder : public CommandBase {
public:
	DefaultNoEncoder();
	Timer * AutoTimer;
	int Step;
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};


#endif //NEWPOWERUP_DEFAULTNOENCODER_H
