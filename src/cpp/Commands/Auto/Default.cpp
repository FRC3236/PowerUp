//
// Created by Eric on 1/11/2018.
//

#include "Default.h"

using namespace std;

AutoDefault::AutoDefault() {
	Requires(drivetrain);
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
			if (drivetrain->DriveInches(228, 1)) {
				Step = 2;
			}
			break;
		}
		case 2: {
			if (drivetrain->TurnAngle(90)) {
				drivetrain->SetEncoder();
				drivetrain->SetRefAngle(drivetrain->GetGyro());
				Step = 3;
			}
			break;
		}
		case 3: {
			double dist = 66;
			double speed = 0.6;
			string INFOS = frc::DriverStation::GetInstance().GetGameSpecificMessage();
			string SIDE = "R";
			if (INFOS[0] == SIDE[0]) {
				dist = 150;
				speed = 0.75;
			}
			if (drivetrain->DriveInches(dist, speed)) {
				drivetrain->SetRefAngle(drivetrain->GetGyro());
				Step = 4;
			}
			break;
		}
		case 4: {
			if (drivetrain->TurnAngle(90)) {
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