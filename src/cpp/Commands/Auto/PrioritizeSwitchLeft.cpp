//
// Created by robotics on 1/23/2018.
//

#include "PrioritizeSwitchLeft.h"
using namespace std;
#include <iostream>

AutoPrioritizeSwitchLeft::AutoPrioritizeSwitchLeft(){
	Requires(drivetrain);
	Requires(elevator);
	Requires(cubegrabber);
}

void AutoPrioritizeSwitchLeft::Initialize() {
	drivetrain->KillDrive();
	if (CommandBase::Field->GetScale()) {
		Step = 101;
	} else {
		Step = 1;
	}

	Step = 1000;
	cubegrabber->Retract();
}

void AutoPrioritizeSwitchLeft::Execute() {
	std::cout << "[Auto Switch Left]" <<  Step << std::endl;
	switch (Step) {
		default: {
			drivetrain->KillDrive();
			End();
			break;
		}
		case 1: {
			elevator->AscendTo(0.5, 1200);
			if (drivetrain->DriveInches(180, 1)) {
				Step = 2;
			}
			break;
		}
		case 2: {
			elevator->AscendTo(0.5, 1200);
			if (drivetrain->TurnToAngle(90)) {
				while (floor(drivetrain->GetEncoder()) != 0 ) {
					drivetrain->SetEncoder();
					cubegrabber->ExtendArm();
				}
				Step = 3;
			}
			break;
		}
		case 3: {
			elevator->AscendTo(0.5, 1200);
			if (drivetrain->DriveInches(12, 0.5)) {
				while (floor(drivetrain->GetEncoder()) != 0 ) {
					drivetrain->SetEncoder();
				}
				Step = 4;
			}
			break;
		}
		case 4: {
			cubegrabber->Extend();
			elevator->AscendTo(0.5, 1200);
			drivetrain->KillDrive();
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
				while (floor(drivetrain->GetEncoder()) != 0 ) {
					drivetrain->SetEncoder();
				}
				drivetrain->SetRefAngle(90);
			}
			break;
		}
		case 103: {
			if (drivetrain->DriveInches(150, 1)) {
				while (floor(drivetrain->GetEncoder()) != 0 ) {
					drivetrain->SetEncoder();
				}

				Step = 104;
			}
			break;
		}
		case 104: {
			elevator->AscendTo(0.5, 1200);
			if (drivetrain->TurnToAngle(180)) {
				drivetrain->SetRefAngle(180);
				while (floor(drivetrain->GetEncoder()) != 0 ) {
					drivetrain->SetEncoder();
				}

				Step = 105;
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
			if (drivetrain->TurnToAngle(-75, 0.2)) {
				drivetrain->SetRefAngle(-75);
				while (floor(drivetrain->GetEncoder()) != 0 ) {
					drivetrain->SetEncoder();
				}
				Step = 107;
			}
			break;
		}
		case 107: {
			elevator->GoToPosition(7600, 0.5);
			if (drivetrain->DriveInches(21, 0.5)) {
				while (floor(drivetrain->GetEncoder()) != 0 ) {
					drivetrain->SetEncoder();
				}
				Step = 108;
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
			if (drivetrain->DriveInches(15, 0.5)) {
				Step = 1001;
			}
			break;
		}
		case 1001: {
			if (drivetrain->DriveInches(-15, -0.5)) {
				drivetrain->KillDrive();
			}
		}

	}
}

void AutoPrioritizeSwitchLeft::End() {
	drivetrain->KillDrive();
}

void AutoPrioritizeSwitchLeft::Interrupted() {
	End();
}

bool AutoPrioritizeSwitchLeft::IsFinished() {
	return Step == -1;
}