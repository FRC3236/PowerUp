//
// Created by robotics on 2/13/2018.
//

#ifndef NEWPOWERUP_GRABCUBE_H
#define NEWPOWERUP_GRABCUBE_H
#include "../CommandBase.h"


class GrabCube : public CommandBase {
public:
	GrabCube();
	void Initialize() override;
	void Execute() override;
	void End() override;
	void Interrupted() override;
	bool IsFinished() override;
};


#endif //NEWPOWERUP_GRABCUBE_H
