//
// Created by robotics on 1/16/2018.
//

#include "AutoPrioritizeSwitchLeft.h"
#include <iostream>
using namespace std;

AutoPrioritizeSwitchLeft::AutoPrioritizeSwitchLeft() {
	Requires(drivetrain);
}

void AutoPrioritizeSwitchLeft::Initialize() {
	drivetrain->KillDrive();
	Step = 1;

	drivetrain->SetPID(0);
}

void AutoPrioritizeSwitchLeft::Execute() {
	SmartDashboard::PutNumber("Gyro", drivetrain->GetGyro());
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
			if (drivetrain->TurnToAngle(90)) {
				drivetrain->SetEncoder();
				Step = 3;
				drivetrain->SetPID(90);
			}
			drivetrain->SetPID(90);
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
				Step = 4;
			}
			break;
		}
		case 4: {
			if (drivetrain->TurnToAngle(180)) {
				drivetrain->SetPID(180);
				End();
			}
			break;
		}
			// end switch case
	}
}

void AutoPrioritizeSwitchLeft::End() {
	drivetrain->KillDrive();
}

void AutoPrioritizeSwitchLeft::Interrupted() {
	End();
}

bool AutoPrioritizeSwitchLeft::IsFinished() {
	return Step == 10;
}