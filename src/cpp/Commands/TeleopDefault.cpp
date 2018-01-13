#include "TeleopDefault.h"
#include <WPILib.h>
#include "../CommandBase.h"
#include "../RobotMap.h"

#include <iostream>
using namespace std;
TeleopDefault::TeleopDefault() {
	Requires(drivetrain);
}

// Called just before this Command runs the first time
void TeleopDefault::Initialize() {
    drivetrain->Calibrate();
	drivetrain->SetEncoder();
}

// Called repeatedly when this Command is scheduled to run
void TeleopDefault::Execute() {
	std::cout << to_string(drivetrain->GetEncoder()) << std::endl;
    //std::cout << to_string(drivetrain->GetGyro()) << std::endl;
    //std::cout << to_string(drivetrain->GetDistance()) << std::endl;
	drivetrain->DriveInternal(-controls->RightJoystick->GetRawAxis(0), -controls->RightJoystick->GetRawAxis(0),controls->RightJoystick->GetRawAxis(0), controls->RightJoystick->GetRawAxis(0));

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
