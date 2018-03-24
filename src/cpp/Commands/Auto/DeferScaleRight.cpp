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
		if (CommandBase::Field->GetSwitch()) {
			//Switch is on the right, go for it!
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

void DeferScaleRight::Execute() {
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
			elevator->GoToPosition(8100, 0.5);
			if (drivetrain->DriveInches(228, 0.65)) {
				Step = 2;
			}
			break;
		}
		case 2: {
			elevator->GoToPosition(8100, 0.5);
			if (drivetrain->TurnToAngle(90, 0.7)) {
				drivetrain->SetEncoder();
				Step = 3;
			}
			break;
		}
		case 3: {
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
			elevator->GoToPosition(3000, 0.5);
			if (drivetrain->DriveInches(150, 1)) {
				drivetrain->SetEncoder();
				Step = 52;
			}
			break;
		}
		case 52: {
			elevator->GoToPosition(3000, 0.5);
			if (drivetrain->TurnToAngle(90, 0.8)) {
				cubegrabber->ExtendArm();
				Step = 53;
			}
			break;
		}
		case 53: {
			elevator->GoToPosition(3000, 0.5);
			if (drivetrain->DriveInches(32, 0.5)) {
				drivetrain->SetEncoder();
				AutoTimer->Reset();
				AutoTimer->Start();
				cubegrabber->Extend();
				drivetrain->KillDrive();
				Step = 54;
			}
			break;
		}
		case 54: {
			elevator->GoToPosition(3000, 0.5);
			if (AutoTimer->Get() > 0.6) {
				if (drivetrain->DriveInches(-32, 0.5)) {
					drivetrain->SetEncoder();
					Step = 55;
				}
			}
			break;
		}
		case 55: {
			drivetrain->KillDrive();
			break;
		}


		case 101: {
			if (drivetrain->DriveInchesFast(195, 1)) {
				Step = 102;
			}
			break;
		}
		case 102: {
			if (drivetrain->TurnToAngle(90)) {
				Step = 103;
				drivetrain->SetEncoder();
				drivetrain->SetRefAngle(90);
			}
			break;
		}
		case 103: {
			if (drivetrain->DriveInchesFast(180, 1)) {
				drivetrain->SetEncoder();
				cubegrabber->ExtendArm();
				Step = 104;
			}
			break;
		}
		case 104: {
			elevator->GoToPosition(3000, 0.5);
			if (drivetrain->TurnToAngle(180)) {
				Step = 105;
				drivetrain->SetRefAngle(180);
			}
			break;
		}
		case 105: {
			elevator->GoToPosition(3000, 0.5);
			if (drivetrain->DriveInches(24, 0.5)) {
				drivetrain->SetEncoder();
				AutoTimer->Reset();
				AutoTimer->Start();
				cubegrabber->Extend();
				Step = 106;
			}
			break;
		}
		case 106: {
			elevator->GoToPosition(3000, 0.5);
			if (AutoTimer->Get() > 0.6) {
				if (drivetrain->DriveInches(-24, 0.3)) {
					drivetrain->SetEncoder();
					Step = 107;
				}
			}
			break;
		}
		case 107: {
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