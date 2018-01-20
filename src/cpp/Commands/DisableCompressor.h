//
// Created by robotics on 1/20/2018.
//

#ifndef NEWPOWERUP_ENABLECOMPRESSOR_H
#define NEWPOWERUP_ENABLECOMPRESSOR_H
#include "../CommandBase.h"

class DisableCompressor : public CommandBase {
public:
	DisableCompressor();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};



#endif //NEWPOWERUP_ENABLECOMPRESSOR_H
