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
	drivetrain->SetEncoder();
	Requires(drivetrain);
}

// Called repeatedly when this Command is scheduled to run
void TeleopDefault::Execute() {
	double forwardSpeed, lateralSpeed;
	forwardSpeed = controls->RightJoystick->GetY();
	lateralSpeed = controls->RightJoystick->GetX();
	drivetrain->Drive( lateralSpeed - forwardSpeed, lateralSpeed + forwardSpeed );
	double avg = ((lateralSpeed - forwardSpeed) + (lateralSpeed - forwardSpeed)) / 2;
	frc::SmartDashboard::PutNumber("Error", avg);
}

// Make this return true when this Command no longer needs to run execute()
bool TeleopDefault::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TeleopDefault::End() {
	drivetrain->KillDrive();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TeleopDefault::Interrupted() {
	End();
}
