//
// Created by robotics on 1/23/2018.
//
#include "PrioritizeScaleLeft.h"
using namespace std;

AutoPrioritizeScaleLeft::AutoPrioritizeScaleLeft(){
	Requires(drivetrain);
	Requires(elevator);
	Requires(cubegrabber);
}
void AutoPrioritizeScaleLeft::Initialize() {
	drivetrain->KillDrive();
	if (CommandBase::Field->GetScale()) {
		Step = 101;
	}
	Step = 1;
}

void AutoPrioritizeScaleLeft::Execute() {
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
				if (drivetrain->TurnToAngle(90)) {
					Step = 3;
				}
			}
		}
		case 3: {
			drivetrain->KillDrive();
			Step = -1;
		}


		case 101: {
			cubegrabber->Retract();
			if (drivetrain->DriveInches(228, 1)) {
				Step = 102;
			}
		}
		case 102: {
			if (drivetrain->TurnToAngle(90)) {
				Step = 103;
			}
		}
		case 103: {
			elevator->GoToPosition(8200, 0.8);
			if (drivetrain->DriveInches(250, 1)) {
				Step = 104;
			}
		}
		case 104: {
			elevator->GoToPosition(8200, 0.8);
			if (drivetrain->TurnToAngle(0)) {
				Step = 105;
			}
		}
		case 105: {
			elevator->GoToPosition(8200, 0.8);
			if (drivetrain->DriveInches(36, 0.8)) {
				Step = 106;
			}
		}
		case 106: {
			if (drivetrain->TurnToAngle(-90)) {
				Step = 107;
			}
		}
		case 107: {
			//push and drop cube//
			Step = -1;
		}
	}
}

void AutoPrioritizeScaleLeft::End() {
	drivetrain->KillDrive();
}

void AutoPrioritizeScaleLeft::Interrupted() {
	End();
}

bool AutoPrioritizeScaleLeft::IsFinished() {
	return Step == -1;
}



			//acticavate elevator to 



