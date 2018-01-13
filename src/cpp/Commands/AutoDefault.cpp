//
// Created by Eric on 1/11/2018.
//

#include "AutoDefault.h"
#include <iostream>

AutoDefault::AutoDefault() {
	Requires(drivetrain);
}

void AutoDefault::Initialize() {
	drivetrain->KillDrive();
    drivetrain->SetEncoder();
	Step = 1;
}

void AutoDefault::Execute() {
	std::cout << Step << std::endl;
	if (Step == 1) {
		if (drivetrain->DriveInches(228, 1)) {
			Step = 2;
		}
	} else if (Step == 2) {
		bool Done = drivetrain->TurnAngle(90);
		if (Done) {
			drivetrain->SetEncoder();
			drivetrain->SetRefAngle(drivetrain->GetGyro());
			Step = 3;
		}
	} else if (Step == 3) {
		double dist = 66;
		double speed = 0.6;
		std::string INFOS = frc::DriverStation::GetInstance().GetGameSpecificMessage();
		std::string SIDE = "R";
		if (INFOS[0] == SIDE[0]) {
			dist = 150;
			speed = 0.75;
		}
		if (drivetrain->DriveInches(dist, speed)) {
			drivetrain->SetRefAngle(drivetrain->GetGyro());
			Step = 4;
		}
	} else if (Step == 4) {
		if (drivetrain->TurnAngle(90)) {
			End();
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