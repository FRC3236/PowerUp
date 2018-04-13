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

	std::cout << "AUTO: " << Step << std::endl;
	cubegrabber->Retract();
}

void AutoPrioritizeScaleLeft::Execute() {
	std::cout << "[Auto Scale] " <<  Step << " ENC: " << drivetrain->GetEncoder() << std::endl;
	switch (Step) {
		default: {
			std::cout << "[Auto Scale] Auto failed! We were on step " << Step << std::endl;
			drivetrain->KillDrive();
			Step = -1;
			End();
			break;
		}

		//Scale is on the left//
		case 1: {
			if (drivetrain->GetEncoder() > 110)  {
				elevator->GoToPosition(elevator->GetMaxHeight(), 0.5);
			}
			if (drivetrain->DriveInches(228, 0.8)) {
				Step = 2;
			}
			break;
		}
		case 2: {
			elevator->GoToPosition(elevator->GetMaxHeight(), 1);
			if (drivetrain->TurnToAngle(90, 1)) {
				drivetrain->SetEncoder();
				Step = 3;
			}
			break;
		}
		case 3: {
			elevator->GoToPosition(elevator->GetMaxHeight(), 1);
			if (drivetrain->DriveInches(12, 0.5)) {
				drivetrain->SetEncoder();
				Step = 4;
				AutoTimer->Reset();
				AutoTimer->Start();
			}
			break;
		}
		case 4: {
			cubegrabber->Extend();
			if (AutoTimer->Get() > 0.25) {
				while (floor(drivetrain->GetEncoder()) != 0) {
					drivetrain->SetEncoder();
				}
				Step = 5;
			}
			break;
		}
		case 5: {
			if (drivetrain->DriveInchesFast(-36, -0.6)) {
				Step = 6;
			}
			break;
		}
		case 6: {
			/*elevator->GoToPosition(50, 0.5);
			if (drivetrain->TurnToAngle(135)) {
				while (floor(drivetrain->GetEncoder()) != 0 ) {
					drivetrain->SetEncoder();
				}
				while (drivetrain->GetRefAngle() != 135) {
					drivetrain->SetRefAngle(135);
				}
				cubegrabber->ExtendArm();
				Step = 7;

				AutoTimer->Reset();
				AutoTimer->Start();
			}*/
			drivetrain->KillDrive();
			break;
		}
		/*
		case 7: {
			if (drivetrain->DriveInchesFast(85, 0.7))  {
				while (floor(drivetrain->GetEncoder()) != 0 ) {
					drivetrain->SetEncoder();
				}
				Step = 8;
			}
			break;
		}
		case 8: {
			if (drivetrain->TurnToAngle(180)) {
				Step = 9;
				while (floor(drivetrain->GetEncoder()) != 0 ) {
					drivetrain->SetEncoder();
				}
			}
			break;
		}
		case 9: {
			if (drivetrain->DriveInches(16, 0.5)) {
				//Step = 10;
				cubegrabber->Retract();
				while (floor(drivetrain->GetEncoder()) != 0 ) {
					drivetrain->SetEncoder();
				}
			}
			break;
		}
		case 10: {
			cubegrabber->Retract();
			break;
		}
		case 11: {
			elevator->GoToPosition(1500, 0.5);
			if (drivetrain->DriveInchesFast(12, 0.5)) {
				Step = 12;
				if (AutoTimer->Get() > 0.25) {
					cubegrabber->ExtendArm();
				}
			}
			break;
		}
		case 12: {
			elevator->GoToPosition(1500, 0.5);
			if (elevator->GetEncoder() > 1400) {
				cubegrabber->Extend();
				drivetrain->KillDrive();
			}
			break;r4
		}*/

		//Scale is on the right//
		case 101: {
			if (drivetrain->DriveInchesFast(194, 1)) {
				Step = 102;
				drivetrain->KillDrive();
			}
			break;
		}
		case 102: {
			if (drivetrain->TurnToAngle(83, 0.4)) { //CHANGED FROM 90
				Step = 103;
				drivetrain->SetEncoder();
				drivetrain->SetRefAngle(90);
			}
			break;
		}
		case 103: {
			if (drivetrain->DriveInchesFast(197, 1)) {
				drivetrain->SetEncoder();

				Step = 104;
			}
			break;
		}
		case 104: {
			elevator->GoToPosition(elevator->GetMaxHeight(), 0.5);
			if (drivetrain->TurnToAngle(0)) {
				drivetrain->SetRefAngle(0);
				drivetrain->SetEncoder();
				Step = 105;
			}
			break;
		}
		case 105: {
			elevator->GoToPosition(elevator->GetMaxHeight(), 0.8);
			if (drivetrain->DriveInchesFast(51, 0.8)) {
				drivetrain->KillDrive();
				Step = 106;
			}
			break;
		}
		case 106: {
			elevator->GoToPosition(elevator->GetMaxHeight(), 1);
			if (drivetrain->TurnToAngle(-90, 1)) {
				drivetrain->SetRefAngle(-90);
				drivetrain->SetEncoder();
				Step = 107;
			}
			break;
		}
		case 107: {
			elevator->GoToPosition(elevator->GetMaxHeight(), 0.5);
			if (drivetrain->DriveInches(26, 0.5)) {
				drivetrain->SetEncoder();
				Step = 108;
			}
			break;
		}
		case 108: {
			elevator->GoToPosition(elevator->GetMaxHeight(), 0.5);
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