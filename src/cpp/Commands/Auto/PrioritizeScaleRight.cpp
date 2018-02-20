//
// Created by robotics on 1/16/2018.
//

#include "PrioritizeScaleRight.h"
using namespace std;

AutoPrioritizeScaleRight::AutoPrioritizeScaleRight() {
	Requires(drivetrain);
	Requires(elevator);
	Requires(cubegrabber);
}
void AutoPrioritizeScaleRight::Initialize() {
	drivetrain->KillDrive();
	if (CommandBase::Field->GetScale()) {
		Step = 1;
	} else {
		Step = 101;
	}
}

void AutoPrioritizeScaleRight::Execute() {
	switch (Step) {

		default: {
			drivetrain->KillDrive();
			End();
		}
		case 1: {
			cubegrabber->Retract();
			if (drivetrain->GetEncoder() > 24) {
				elevator->GoToPosition(8200, 0.8);
			}
			if (drivetrain->DriveInches(320, 1)) {
				Step = 2;
			}
			break;
		}
		case 2: {
			if (elevator->GoToPosition(8200)) {
				if (drivetrain->TurnToAngle(-90)) {
					Step = 3;
				}
			}
			break;
		}
		case 3: {
			drivetrain->KillDrive();
			Step = -1;
			break;
		}


		case 101: {
			cubegrabber->Retract();
			if (drivetrain->DriveInches(228, 1)) {
				Step = 102;
			}
			break;
		}
		case 102: {
			if (drivetrain->TurnToAngle(-90)) {
				Step = 103;
			}
			break;
		}
		case 103: {
			elevator->GoToPosition(8200, 0.8);
			if (drivetrain->DriveInches(250, 1)) {
				Step = 104;
			}
			break;
		}
		case 104: {
			elevator->GoToPosition(8200, 0.8);
			if (drivetrain->TurnToAngle(0)) {
				Step = 105;
			}
			break;
		}
		case 105: {
			elevator->GoToPosition(8200, 0.8);
			if (drivetrain->DriveInches(36, 0.8)) {
				Step = 106;
			}
			break;
		}
		case 106: {
			if (drivetrain->TurnToAngle(90)) {
				Step = 107;
			}
			break;
		}
		case 107: {
			//push and drop cube//
			Step = -1;
			break;
		}
	}
}

void AutoPrioritizeScaleRight::End() {
	drivetrain->KillDrive();
}

void AutoPrioritizeScaleRight::Interrupted() {
	End();
}

bool AutoPrioritizeScaleRight::IsFinished() {
	return Step == 10;
}