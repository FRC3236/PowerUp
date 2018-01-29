
// Created by robotics on 1/27/2018.
//

#include "PrioritizeScaleRight.h"
using namespace std;

AutoPrioritizeScaleRight::AutoPrioritizeScaleRight(){
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
			if (drivetrain->DriveInches(315, 1)) {
				Step = 2;
			}
			break;
		}
		case 2: {
			if (drivetrain->TurnToAngle(-90)) {
				drivetrain->SetEncoder();
				drivetrain->SetRefAngle(drivetrain->GetGyro());
				{
					Step = 3;
				}
			}

			break;
		}
		case 3: {
			if (drivetrain->DriveInches(15, 0)) {
				End();
			}
			break;
		}
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

