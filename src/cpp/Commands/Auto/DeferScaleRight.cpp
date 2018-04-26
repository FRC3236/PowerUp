//
// Created by robotics on 3/23/2018.
//

#include "DeferScaleRight.h"
#include <iostream>

DeferScaleRight::DeferScaleRight() {
	Requires(drivetrain);
	Requires(elevator);
	Requires(cubegrabber);
	AutoTimer = new Timer();
}

void DeferScaleRight::Initialize() {
	AutoTimer->Stop();
	AutoTimer->Reset();
	AutoTimer->Start();
	drivetrain->KillDrive();
	if (CommandBase::Field->GetScale()) {
		//Scale is on the right, defer to other bot, check switch;
		Step = 1;
	} else {
		//Scale is on the right, go for it!
		Step = 51;
	}
	cubegrabber->RetractArm();
	cubegrabber->Retract();
}

void DeferScaleRight::Execute() {
	std::cout << "[Auto Scale DEFERRIGHT]" << Step << std::endl;
	switch (Step) {
		default: {
			std::cout << "[Auto Scale DEFERRIGHT] Auto failed! We were on step " << Step << std::endl;
			drivetrain->KillDrive();
			End();
			Step = -1;
			break;
		}
		case 1: {
			if (drivetrain->GetEncoder() > 110) {
				elevator->GoToPosition(elevator->GetMaxHeight(), 0.5);
			}
			if (drivetrain->DriveInches(226, 0.65)) {
				Step = 2;
			}
			break;
		}
		case 2: {
			elevator->GoToPosition(elevator->GetMaxHeight(), 0.8);
			if (drivetrain->TurnToAngle(-80, 1)) {
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

void DeferScaleRight::End() {
	drivetrain->KillDrive();
}

void DeferScaleRight::Interrupted() {
	End();
}

bool DeferScaleRight::IsFinished() {
	return Step == -1;
}