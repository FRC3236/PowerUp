#ifndef SRC_SYSTEMBASE_H
#define SRC_SYSTEMBASE_H

#include "Subsystems/DriveTrain.h"
#include "OI.h"
#include "WPILib.h"

class CommandBase : public frc::Command {
private:
public:
	static DriveTrain *drivetrain;
	static OI *controls;

    CommandBase(char const *name);
	CommandBase();

	static void Init();
};

#endif /* SRC_SYSTEMBASE_H*/
