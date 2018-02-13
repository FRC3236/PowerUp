#include "TeleopDefault.h"
#include <WPILib.h>
#include "../CommandBase.h"
#include "../RobotMap.h"

bool GrabberButton = true;

#include <iostream>
using namespace std;
TeleopDefault::TeleopDefault() {
	Requires(drivetrain);
	Requires(elevator);
	Requires(cubegrabber);
}

// Called just before this Command runs the first time
void TeleopDefault::Initialize() {
	drivetrain->SetEncoder();
	elevator->SetEncoder();

}

// Called repeatedly when this Command is scheduled to run
void TeleopDefault::Execute() {
	double forwardSpeed, lateralSpeed;
	forwardSpeed = controls->DriverStick->GetY();
	lateralSpeed = controls->DriverStick->GetX();

	drivetrain->GetEncoder();
	drivetrain->Drive(lateralSpeed - forwardSpeed, lateralSpeed + forwardSpeed);
	double avg = ((lateralSpeed - forwardSpeed) + (lateralSpeed - forwardSpeed)) / 2;

	//std::cout << "[elevator shtuff]" << elevator->Tray->GetOutputCurrent() << std::endl;

	if (controls->OperatorStick->GetRawButton(1)) {
		if (controls->OperatorStick->GetY() >= 0) {
			elevator->Descend(controls->OperatorStick->GetY() /2);
		} else {
			elevator->Ascend(controls->OperatorStick->GetY() /2);
		}
	} else {
		elevator->SetMotor(0);
	}

	if (controls->OperatorStick->GetRawButtonPressed(5) /*&& GrabberButton*/) {
		if (cubegrabber->Opened) {
			cubegrabber->Retract();
		} else {
			cubegrabber->Extend();
		}
		GrabberButton = false;
	} else {
		GrabberButton = true;
	}

	if (controls->OperatorStick->GetPOV() == 0) {
		elevator->SetTray(1);
	} else if (controls->OperatorStick->GetPOV() == 180) {
		elevator->SetTray(-1);
	} else {
		elevator->SetTray(0);
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
