//
// Created by robotics on 1/23/2018.
//

#include "PrioritizeSwitchRight.h"
using namespace std;
#include <iostream>

AutoPrioritizeSwitchRight::AutoPrioritizeSwitchRight(){
	Requires(drivetrain);
	Requires(elevator);
	Requires(cubegrabber);
	AutoTimer = new Timer();
	AutoTimer->Stop();
	AutoTimer->Reset();
}

void AutoPrioritizeSwitchRight::Initialize() {
	drivetrain->KillDrive();
	if (CommandBase::Field->GetSwitch()) {
		Step = 101;
	} else {
		Step = 1;
	}
	cubegrabber->Retract();
	cubegrabber->RetractArm();
}

void AutoPrioritizeSwitchRight::Execute() {

	switch (Step) {
		default: {
			drivetrain->KillDrive();
			Step = -1;
			End();
			break;
		}

			//Switch is on the left//
		case 1: {
			if (drivetrain->DriveInchesNoSlow(12)) {
				Step = 2;
				drivetrain->KillDrive();
				break;
			}
		}
		case 2: {
			elevator->GoToPosition(elevator->GetSwitchHeight(), 0.6);
			if (drivetrain->TurnToAngle(-45)) {
				drivetrain->KillDrive();
				Step = 3;
				// Purposefully not setting ref angle so
				// the drivetrain curves to the switch.
				break;
			}
		}
		case 3: {
			elevator->GoToPosition(elevator->GetSwitchHeight(), 0.6);
			if (drivetrain->DriveInches(190,0.8)) {
				drivetrain->KillDrive();
				Step = 4;
				AutoTimer->Start();
				break;
			}
		}
		case 4: {
			elevator->GoToPosition(elevator->GetSwitchHeight(), 0.6);
			cubegrabber->ExtendArm();
			if (AutoTimer->Get() > 0.6) {
				Step = 5;
			}
			break;
		}
		case 5: {
			cubegrabber->Extend();
			elevator->GoToPosition(elevator->GetSwitchHeight(), 0.6);
			Step = 6;
			break;
		}
		case 6: {
			if (drivetrain->DriveInches(-20, 0.4)) {

				cubegrabber->RetractArm();
				Step = -1;
				drivetrain->KillDrive();
			}
			break;
		}

			//Switch is on the right//
		case 101: {
			if (drivetrain->DriveInches(12, 0.5)) {
				Step = 102;
				drivetrain->KillDrive();
				break;
			}
		}
		case 102: {
			elevator->GoToPosition(elevator->GetSwitchHeight(), 0.5);
			if (drivetrain->TurnToAngle(45)) {
				drivetrain->KillDrive();
				Step = 103;
				// Purposefully not setting ref angle so
				// the drivetrain curves to the switch.
				break;
			}
		}
		case 103: {
			elevator->GoToPosition(elevator->GetSwitchHeight(), 0.5);
			if (drivetrain->DriveInches(190,0.8)) {
				drivetrain->KillDrive();
				Step = 104;
				AutoTimer->Start();
				break;
			}
		}
		case 104: {
			elevator->GoToPosition(elevator->GetSwitchHeight(), 0.5);
			cubegrabber->ExtendArm();
			if (AutoTimer->Get() > 0.6) {
				Step = 105;
			}
			break;
		}
		case 105: {
			cubegrabber->Extend();
			cubegrabber->RetractArm();
			Step = 106;
			break;
		}
		case 106: {
			if (drivetrain->DriveInches(-20, 0.4)) {
				Step = -1;
				drivetrain->KillDrive();
			}
			break;
		}
	}
}

void AutoPrioritizeSwitchRight::End() {
	drivetrain->KillDrive();
}

void AutoPrioritizeSwitchRight::Interrupted() {
	End();
}

bool AutoPrioritizeSwitchRight::IsFinished() {
	return Step == -1;
}