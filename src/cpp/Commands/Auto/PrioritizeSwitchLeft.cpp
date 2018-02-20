//
// Created by robotics on 1/16/2018.
//

#include "PrioritizeSwitchLeft.h"
#include <iostream>
using namespace std;

AutoPrioritizeSwitchLeft::AutoPrioritizeSwitchLeft() {
	Requires(drivetrain);
}

void AutoPrioritizeSwitchLeft::Initialize() {
	drivetrain->KillDrive();
	Step = 1;
	pid = new PID(0);
}

void AutoPrioritizeSwitchLeft::Execute() {
	switch (Step) {
		default: {
			drivetrain->KillDrive();
			End();
		}
		case 1: {
			if (drivetrain->DriveInches(188, 0.9)) { //228
				Step = 2;
				//drivetrain->SetEncoder();
			}
			break;
		}
		case 2: {
			if (drivetrain->TurnToAngle(90)) {
			Step = 3;
					//drivetrain->SetEncoder();
				}
			}
			break;

		case 3: {
			if (drivetrain->DriveInches(12, 0.5)) {
			Step = 4;
				}
			}
		break;

		case 4: {

		}
			break;
	}
	frc::SmartDashboard::PutNumber("Current Step", Step);
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