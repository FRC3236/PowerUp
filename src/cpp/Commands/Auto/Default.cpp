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
	cubegrabber->Retract();
}

void AutoDefault::Execute() {

	switch (Step) {
		default: {
			drivetrain->KillDrive();
			End();
		}
			/*case 1: {
				if (drivetrain->TurnToAngle(90, 0.3)) {
					Step = 2;
				}
				break;
			}
			case 2: {
				drivetrain->KillDrive();
				break;
			}*/
			case 1: {
				cubegrabber->Retract();
				if (drivetrain->DriveInchesFast(90,0.7)) {
					drivetrain->SetEncoder();
					Step = 2;
				}
				break;
			}
			case 2: {
				drivetrain->KillDrive();
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