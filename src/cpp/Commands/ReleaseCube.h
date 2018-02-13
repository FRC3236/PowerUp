//
// Created by robotics on 2/13/2018.
//

#ifndef NEWPOWERUP_RELEASECUBE_H
#define NEWPOWERUP_RELEASECUBE_H
#include "../CommandBase.h"


class ReleaseCube : public CommandBase {
public:
	ReleaseCube();
	void Initialize() override;
	void Execute() override;
	void End() override;
	void Interrupted() override;
	bool IsFinished() override;
};



#endif //NEWPOWERUP_RELEASECUBE_H
