#include "TeleopDefault.h"
#include <WPILib.h>
#include "../CommandBase.h"
#include "../RobotMap.h"

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

}

// Called repeatedly when this Command is scheduled to run
void TeleopDefault::Execute() {
	double forwardSpeed, lateralSpeed;
	forwardSpeed = controls->DriverStick->GetY();
	lateralSpeed = controls->DriverStick->GetX();

	drivetrain->GetEncoder();
	drivetrain->Drive(lateralSpeed - forwardSpeed, lateralSpeed + forwardSpeed);

	//std::cout << "[elevator shtuff]" << elevator->Tray->GetOutputCurrent() << std::endl;

	if (controls->OperatorStick->GetRawButton(1)) {
		if (controls->OperatorStick->GetY() >= 0) {
			elevator->Descend(controls->OperatorStick->GetY() *.8);
		} else {
			elevator->Ascend(controls->OperatorStick->GetY() *.8);
		}
	} else {
		elevator->SetMotor(0);
	}

	if(controls->OperatorStick->GetRawButtonPressed(3)){
		if (cubegrabber->ArmDown) {
			cubegrabber->RetractArm();
		} else {
			cubegrabber->ExtendArm();
		}
	}
	if (controls->OperatorStick->GetRawButtonPressed(5) /*&& GrabberButton*/) {
		if (cubegrabber->Opened) {
			cubegrabber->Retract();
		} else {
			cubegrabber->Extend();
		}
	}

	if (controls->OperatorStick->GetRawButtonPressed(11)) {
		cubegrabber->ToggleCompressor();
	}

	frc::SmartDashboard::PutBoolean("COMPRESSOR", cubegrabber->GetCompressor());
	frc::SmartDashboard::PutNumber("Text Display 1", drivetrain->GetEncoder());
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
