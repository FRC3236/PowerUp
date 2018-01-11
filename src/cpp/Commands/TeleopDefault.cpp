#include "TeleopDefault.h"
#include <WPILib.h>
#include "../CommandBase.h"
#include "../RobotMap.h"

TeleopDefault::TeleopDefault() {
	Requires(drivetrain);
}

// Called just before this Command runs the first time
void TeleopDefault::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void TeleopDefault::Execute() {

	drivetrain->DriveInternal(controls->RightJoystick->GetRawAxis(0), 0, 0, 0);

}

// Make this return true when this Command no longer needs to run execute()
bool TeleopDefault::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TeleopDefault::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TeleopDefault::Interrupted() {

}
