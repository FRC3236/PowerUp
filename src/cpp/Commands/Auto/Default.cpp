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
	Step = 1;
}

void AutoDefault::Execute() {

	switch (Step) {
		default: {
			drivetrain->KillDrive();
			End();
		}
		case 1: {
			cubegrabber->Extend();
			cubegrabber->RetractArm();
			if (drivetrain->DriveInches(150, 0.6)) {
				End();
			}
			break;
		}
		// end switch case
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