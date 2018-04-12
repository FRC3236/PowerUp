//
// Created by Eric on 1/11/2018.
//

#include "Default.h"

using namespace std;


AutoDefault::AutoDefault() {
	Requires(drivetrain);
	Requires(cubegrabber);
}

void AutoDefault::Initialize() {
	drivetrain->KillDrive();
    drivetrain->SetEncoder();
	while (floor(drivetrain->GetEncoder()) != 0 ) {
		drivetrain->SetEncoder();
	}
	Step = 1;
}

void AutoDefault::Execute() {

	switch (Step) {
		default: {
			drivetrain->KillDrive();
			End();
		}
		case 1: {
			elevator->GoToPosition(elevator->GetSwitchHeight(), 0.6);
			cubegrabber->Retract();
			if (drivetrain->DriveInchesFast(120,0.7)) {
				drivetrain->SetEncoder();
				Step = 2;
			}
			break;
		}
		case 2: {
			drivetrain->KillDrive();
			elevator->GoToPosition(elevator->GetSwitchHeight(), 0.6);
			break;
		}
	}
}

void AutoDefault::Interrupted() {
	End();
}

void AutoDefault::End() {
	drivetrain->KillDrive();
}

bool AutoDefault::IsFinished() {
	return false;
}