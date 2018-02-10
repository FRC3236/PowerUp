#include "TeleopDefault.h"
#include <WPILib.h>
#include "../CommandBase.h"
#include "../RobotMap.h"

#include <iostream>
using namespace std;
TeleopDefault::TeleopDefault() {
	Requires(drivetrain);
	Requires(elevator);
}

// Called just before this Command runs the first time
void TeleopDefault::Initialize() {
	Requires(drivetrain);
	Requires(elevator);
	Requires(cubegrabber);

	drivetrain->SetEncoder();
	elevator->SetEncoder();

}

// Called repeatedly when this Command is scheduled to run
void TeleopDefault::Execute() {
	double forwardSpeed, lateralSpeed;
	forwardSpeed = controls->DriverStick->GetY();
	lateralSpeed = controls->DriverStick->GetX();
	///climbSpeed  = controls->LeftJoystick->GetY();
	drivetrain->GetEncoder();
	drivetrain->Drive(lateralSpeed - forwardSpeed, lateralSpeed + forwardSpeed);
	double avg = ((lateralSpeed - forwardSpeed) + (lateralSpeed - forwardSpeed)) / 2;

	std::cout << controls->OperatorStick->GetPOV() << std::endl;

	if (controls->OperatorStick->GetRawButton(0)) {
		if (controls->OperatorStick->GetY() >= 0) {
			elevator->Descend(controls->OperatorStick->GetY() /2);
		} else {
			elevator->Ascend(controls->OperatorStick->GetY() /2);
		}
	} else {
		elevator->SetMotor(0);
	}

	if (controls->OperatorStick->GetRawButton(5)) {
		if (cubegrabber->Opened) {
			cubegrabber->Retract();
		} else {
			cubegrabber->Extend();
		}
	}

	frc::SmartDashboard::PutNumber("Error", avg);
	frc::SmartDashboard::PutNumber("ELEVATOR ENCODER", elevator->GetEncoder());
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
