#ifndef SRC_SYSTEMBASE_H
#define SRC_SYSTEMBASE_H

#include "Subsystems/DriveTrain.h"
#include "Subsystems/Elevator.h"
#include "OI.h"
#include "WPILib.h"
#include "FieldInfo.h"
#include "Subsystems/CubeGrabber.h"

class CommandBase : public frc::Command {
private:
public:
	static DriveTrain *drivetrain;
	static OI *controls;
	static Elevator *elevator;
	static FieldInfo *Field;
	static CubeGrabber *cubegrabber;

	CommandBase(char const *name);
	CommandBase();

	static void Init();
};

#endif /* SRC_SYSTEMBASE_H*/
