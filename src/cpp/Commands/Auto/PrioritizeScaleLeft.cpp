//
// Created by robotics on 1/23/2018.
//

#include "PrioritizeScaleLeft.h"
using namespace std;
#include <iostream>

AutoPrioritizeScaleLeft::AutoPrioritizeScaleLeft(){
	Requires(drivetrain);
	Requires(elevator);
	Requires(cubegrabber);
	AutoTimer = new Timer();
}
void AutoPrioritizeScaleLeft::Initialize() {
	AutoTimer->Stop();
	AutoTimer->Reset();
	AutoTimer->Start();
	drivetrain->KillDrive();
	if (CommandBase::Field->GetScale()) {
		Step = 101;
	} else {
		Step = 1;
	}
	cubegrabber->Retract();
}

void AutoPrioritizeScaleLeft::Execute() {
	std::cout << "[Auto]" <<  Step << std::endl;
	switch (Step) {
		default: {
			drivetrain->KillDrive();
			End();
		}
		case 1: {
			cubegrabber->StopCompressor();
			cubegrabber->Retract();
			if (drivetrain->GetEncoder() > 24) {
				Time = AutoTimer->Get();
				if ((AutoTimer->Get() - Time) >= 0.2) {
					elevator->SetMotor(-0.5);
				}
				elevator->SetMotor(0);
			}
			if (drivetrain->DriveInches(228, 1)) {    //320 for scale??
				Step = 2;
				drivetrain->SetEncoder();
			}
			break;
		}
		case 2: {
			if (elevator->GoToPosition(7600)) {
				if (drivetrain->TurnToAngle(90)) {
					Step = 3;
				}
			}
			break;
		}
		case 3: {
			drivetrain->KillDrive();
			Step = -1;
			break;
		}


		case 101: {
			if (drivetrain->DriveInches(200, 1)) {
				Step = 102;
			}
			break;
		}
		case 102: {
			if (drivetrain->TurnToAngle(90)) {
				Step = 103;
				drivetrain->SetEncoder();
				drivetrain->SetRefAngle(90);
			}
			break;
		}
		case 103: {
			std::cout << "[Auto] " << drivetrain->GetGyro() << std::endl;
			if (drivetrain->DriveInches(200, 1)) {
				Step = 104;
				drivetrain->SetEncoder();
			}
			break;
		}
		case 104: {
			elevator->GoToPosition(7600, 0.5);
			if (drivetrain->TurnToAngle(0)) {
				drivetrain->SetRefAngle(0);
				Step = 105;
				drivetrain->SetEncoder();
			}
			break;
		}
		case 105: {
			elevator->GoToPosition(7600, 0.5);
			if (drivetrain->DriveInches(56, 0.6)) {
				drivetrain->KillDrive();
				Step = 106;
			}
			break;
		}
		case 106: {
			elevator->GoToPosition(7600, 0.5);
			if (drivetrain->TurnToAngle(-75, 0.3)) {
				drivetrain->SetRefAngle(-75);
				drivetrain->SetEncoder();
				Step = 107;
			}
			break;
		}
		case 107: {
			elevator->GoToPosition(7600, 0.5);
			if (drivetrain->DriveInches(21, 0.5)) {
				Step = 108;
				drivetrain->SetEncoder();
			}
			break;
		}
		case 108: {
			cubegrabber->Extend();
			Step = 109;
			break;
		}
		case 109: {
			if (drivetrain->DriveInches(-21, -0.5)) {
				Step = -1;
				cubegrabber->StartCompressor();
				End();
			}
			break;
		}


		case 1000: {
			if (elevator->GoToPosition(7600, 0.5))  {
				drivetrain->KillDrive();
				End();
			}
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
	return Step == -1;
}