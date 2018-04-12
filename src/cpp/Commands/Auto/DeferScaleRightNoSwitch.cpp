//
// Created by robotics on 3/23/2018.
//

#include "DeferScaleRightNoSwitch.h"
#include <iostream>

DeferScaleRightNoSwitch::DeferScaleRightNoSwitch() {
	Requires(drivetrain);
	Requires(elevator);
	Requires(cubegrabber);
	AutoTimer = new Timer();
}

void DeferScaleRightNoSwitch::Initialize() {
	AutoTimer->Stop();
	AutoTimer->Reset();
	AutoTimer->Start();
	drivetrain->KillDrive();
	if (CommandBase::Field->GetScale()) {
		//Scale is on the right, defer to other bot, check switch;
		if (CommandBase::Field->GetSwitch()) {
			//Switch is on the right, drive forward and turn.
			Step = 101;
		} else {
			//Switch is on the left, go for it!
			Step = 51;
		}
	} else {
		//Scale is on the left, go for it!
		Step = 1;
	}
	cubegrabber->RetractArm();
	cubegrabber->Retract();
}

void DeferScaleRightNoSwitch::Execute() {
	std::cout << "[Auto Scale DEFER]" << Step << std::endl;
	switch (Step) {
		default: {
			std::cout << "[Auto Scale DEFER] Auto failed! We were on step " << Step << std::endl;
			drivetrain->KillDrive();
			End();
			Step = -1;
			break;
		}
		case 1: {
			if (drivetrain->GetEncoder() > 110) {
				elevator->GoToPosition(elevator->GetMaxHeight(), 0.5);
			}
			if (drivetrain->DriveInches(228, 0.65)) {
				Step = 2;
			}
			break;
		}
		case 2: {
			elevator->GoToPosition(elevator->GetMaxHeight(), 0.8);
			if (drivetrain->TurnToAngle(90, 0.7)) {
				drivetrain->SetEncoder();
				Step = 3;
			}
			break;
		}
		case 3: {
			elevator->GoToPosition(elevator->GetMaxHeight(), 1);
			if (drivetrain->DriveInches(12, 0.5)) {
				drivetrain->SetEncoder();
				Step = 4;
				AutoTimer->Reset();
				AutoTimer->Start();
			}
			break;
		}
		case 4: {
			cubegrabber->Extend();
			if (AutoTimer->Get() > 0.25) {
				while (floor(drivetrain->GetEncoder()) != 0) {
					drivetrain->SetEncoder();
				}
				Step = 5;
			}
			break;
		}
		case 5: {
			if (drivetrain->DriveInchesFast(-36, -0.6)) {
				Step = 6;
			}
			break;
		}
		case 6: {
			drivetrain->KillDrive();
			break;
		}



		case 51: {
			elevator->GoToPosition(elevator->GetSwitchHeight(), 0.5);
			if (drivetrain->DriveInches(150, 1)) {
				drivetrain->SetEncoder();
				Step = 52;
			}
			break;
		}
		case 52: {
			drivetrain->KillDrive();
			break;
		}

	}
}

void DeferScaleRightNoSwitch::End() {
	drivetrain->KillDrive();
}

void DeferScaleRightNoSwitch::Interrupted() {
	End();
}

bool DeferScaleRightNoSwitch::IsFinished() {
	return Step == -1;
}