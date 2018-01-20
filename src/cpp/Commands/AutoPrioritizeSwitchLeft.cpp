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
	pid = new PID(228);
}

void AutoPrioritizeSwitchLeft::Execute() {
	switch (Step) {
		default: {
			drivetrain->KillDrive();
			End();
		}
		case 1: {
			drivetrain->SetPID(228);
			std::cout << "GETPID" << this->pid->GetPI() << std::endl;
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

void AutoPrioritizeSwitchLeft::End() {
	drivetrain->KillDrive();
}

void AutoPrioritizeSwitchLeft::Interrupted() {
	End();
}

bool AutoPrioritizeSwitchLeft::IsFinished() {
	return Step == 10;
}