#ifndef TeleopDefault_H
#define TeleopDefault_H

#include "../CommandBase.h"

class TeleopDefault : public CommandBase {
public:
	TeleopDefault();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // TeleopDefault_H
