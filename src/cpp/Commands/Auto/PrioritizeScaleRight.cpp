//
// Created by robotics on 1/16/2018.
//

#include "PrioritizeScaleRight.h"
#include <iostream>
using namespace std;

AutoPrioritizeScaleRight::AutoPrioritizeScaleRight() {
	Requires(drivetrain);
}

void AutoPrioritizeScaleRight::Initialize() {
	drivetrain->KillDrive();
	Step = 1;
}

void AutoPrioritizeScaleRight::Execute() {
	switch (Step) {
		default: {
			drivetrain->KillDrive();
			End();
		}
		case 1: {
			drivetrain->SetPID(0);
			if (drivetrain->DriveInches(228, 1)) {
				Step = 2;
			}
			break;
		}
		case 2: {
			drivetrain->SetPID(-90);
			if (drivetrain->TurnAngle(-90)) {
				drivetrain->SetEncoder();
				drivetrain->SetRefAngle(drivetrain->GetGyro());
				Step = 3;
			}
			break;
		}
		case 3: {
			double dist = 12;
			double speed = 0.6;
			if (Field->GetSwitch()) {
				dist = 150;
				speed = 0.75;
			}
			drivetrain->SetPID(-90);
			if (drivetrain->DriveInches(dist, speed)) {
				drivetrain->SetRefAngle(drivetrain->GetGyro());
				Step = 4;
			}
			break;
		}
		case 4: {
			if (drivetrain->TurnAngle(-90)) {
				End();
			}
			break;
		}
			// end switch case
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