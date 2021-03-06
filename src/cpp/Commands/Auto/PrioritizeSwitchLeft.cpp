//
// Created by robotics on 1/23/2018.
//

#include "PrioritizeSwitchLeft.h"
using namespace std;
#include <iostream>

AutoPrioritizeSwitchLeft::AutoPrioritizeSwitchLeft(){
	Requires(drivetrain);
	Requires(elevator);
	Requires(cubegrabber);
	AutoTimer = new Timer();
	AutoTimer->Stop();
	AutoTimer->Reset();
}

void AutoPrioritizeSwitchLeft::Initialize() {
	drivetrain->KillDrive();
	if (CommandBase::Field->GetSwitch()) {
		Step = 101;
	} else {
		Step = 1;
	}
	cubegrabber->Retract();
	cubegrabber->RetractArm();
	drivetrain->SetEncoder();
	drivetrain->ResetGyro();
}

void AutoPrioritizeSwitchLeft::Execute() {
	std::cout << "STEP: " << Step << std::endl;
			switch (Step) {
				default: {
					drivetrain->KillDrive();
					Step = -1;
					End();
					break;
				}

		//Switch is on the left//
		case 1: {
			if (drivetrain->DriveInches(12, 0.5)) {
				Step = 2;
				drivetrain->KillDrive();
			}

			break;
		}
		case 2: {
			elevator->GoToPosition(elevator->GetSwitchHeight(), 0.6);
			if (drivetrain->TurnToAngle(-45, 0.1)) {
				drivetrain->KillDrive();
				Step = 3;
				// Purposefully not setting ref angle so
				// the drivetrain curves to the switch.
				cubegrabber->ExtendArm();
				drivetrain->SetEncoder();
				drivetrain->SetRefAngle(-45);
			}
			break;
		}
		case 3: {
			elevator->GoToPosition(elevator->GetSwitchHeight(), 0.6);
			std::cout << std::endl << drivetrain->GetEncoder() << " ENCODER VAL" << std::endl;
			if (drivetrain->DriveInchesNotStraight(55,0.3)) {
				drivetrain->KillDrive();
				Step = 4;
				AutoTimer->Start();
			}
			break;
		}
		case 4: {
			elevator->GoToPosition(elevator->GetSwitchHeight(), 0.6);
			cubegrabber->Extend();
			Step = 7;
			break;
		}
		case 5: {
			elevator->GoToPosition(elevator->GetSwitchHeight(), 0.6);
			if (drivetrain->DriveInches(12, 0.4)) {
				drivetrain->KillDrive();
				Step = 6;
			}
			break;
		}
		case 6: {
			cubegrabber->Extend();
			elevator->GoToPosition(elevator->GetSwitchHeight(), 0.6);
			Step = 7;
			break;
		}
		case 7: {
			if (drivetrain->DriveInches(-20, 0.2)) {

				Step = -1;
				drivetrain->KillDrive();
			}
			break;
		}

		//Switch is on the right//
		case 101: {
			elevator->GoToPosition(elevator->GetSwitchHeight(), 0.6);
			if (drivetrain->TurnToAngle(45, 0.8)) {
				drivetrain->KillDrive();
				Step = 102;
				// Purposefully not setting ref angle so
				// the drivetrain curves to the switch.
				cubegrabber->ExtendArm();
				drivetrain->SetEncoder();
				drivetrain->SetRefAngle(45);
			}
			break;
		}
		case 102: {
			elevator->GoToPosition(elevator->GetSwitchHeight(), 0.6);
			std::cout << std::endl << drivetrain->GetEncoder() << " ENCODER VAL" << std::endl;
			if (drivetrain->DriveInchesNotStraight(55,0.5)) {
				drivetrain->KillDrive();
				Step = 103;
				AutoTimer->Start();
			}
			break;
		}
		case 103: {
			elevator->GoToPosition(elevator->GetSwitchHeight(), 0.6);
			if (drivetrain->TurnToAngle(0, 0.3)) {
				Step = 104;
				drivetrain->SetEncoder();
				drivetrain->SetRefAngle(0);
			}
			break;
		}
		case 104: {
			elevator->GoToPosition(elevator->GetSwitchHeight(), 0.6);
			if (drivetrain->DriveInches(12, 0.6)) {
				drivetrain->KillDrive();
				Step = 105;
			}
			break;
		}
		case 105: {
			cubegrabber->Extend();
			elevator->GoToPosition(elevator->GetSwitchHeight(), 0.6);
			Step = 106;
			break;
		}
		case 106: {
			if (drivetrain->DriveInches(-20, 0.2)) {

				Step = -1;
				drivetrain->KillDrive();
			}
			break;
		}
	}
}

void AutoPrioritizeSwitchLeft::End() {
	drivetrain->KillDrive();
}

void AutoPrioritizeSwitchLeft::Interrupted() {
	End();
}

bool AutoPrioritizeSwitchLeft::IsFinished() {
	return Step == -1;
}