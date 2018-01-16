//
// Created by robotics on 1/16/2018.
//

#include "AutoPrioritizeSwitchRight.h"
using namespace std;

AutoPrioritizeSwitchRight::AutoPrioritizeSwitchRight() {
	Requires(drivetrain);
}

void AutoPrioritizeSwitchRight::Initialize() {
	drivetrain->KillDrive();
	Step = 1;
}

void AutoPrioritizeSwitchRight::Execute() {
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
	}
}

void AutoPrioritizeSwitchRight::End() {
	drivetrain->KillDrive();
}

void AutoPrioritizeSwitchRight::Interrupted() {
	End();
}

bool AutoPrioritizeSwitchRight::IsFinished() {
	return Step == 10;
}