//
// Created by robotics on 1/23/2018.
//

#include "PrioritizeScaleLeft.h"
using namespace std;

AutoPrioritizeScaleLeft::AutoPrioritizeScaleLeft(){
	Requires(drivetrain);
}
void AutoPrioritizeScaleLeft::Initialize() {
	drivetrain->KillDrive();
	Step = 1;
}

void AutoPrioritizeScaleLeft::Execute() {
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
			if (drivetrain->TurnAngle(90)) {
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

void AutoPrioritizeScaleLeft::End() {
	drivetrain->KillDrive();
}

void AutoPrioritizeScaleLeft::Interrupted() {
	End();
}

bool AutoPrioritizeScaleLeft::IsFinished() {
	return Step == 10;
}



			//acticavate elevator to 



