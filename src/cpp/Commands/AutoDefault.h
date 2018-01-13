//
// Created by Eric on 1/11/2018.
//

#include "../CommandBase.h"

#ifndef POWERUP_AUTODEFAULT_H
#define POWERUP_AUTODEFAULT_H


class AutoDefault : public CommandBase {
public:
	AutoDefault();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

	int Step;
};


#endif //POWERUP_AUTODEFAULT_H
