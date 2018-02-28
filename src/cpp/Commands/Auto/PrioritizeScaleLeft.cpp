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
	std::cout << "[Auto Step] " <<  Step << std::endl;
	switch (Step) {
		default: {
			drivetrain->KillDrive();
			End();
			break;
		}
		case 1: {
			elevator->GoToPosition(7600, 0.5);
			if (drivetrain->DriveInches(260, 1)) {
				Step = 2;
			}
			break;
		}
		case 2: {
			elevator->GoToPosition(7600, 0.5);
			if (drivetrain->TurnToAngle(90)) {
				while (floor(drivetrain->GetEncoder()) != 0 ) {
					drivetrain->SetEncoder();
				}
				Step = 3;
			}
			break;
		}
		case 3: {
			if (drivetrain->DriveInches(12, 0.5)) {
				while (floor(drivetrain->GetEncoder()) != 0 ) {
					drivetrain->SetEncoder();
				}
				Step = 4;
				AutoTimer->Reset();
				AutoTimer->Start();
			}
			break;
		}
		case 4: {
			cubegrabber->Extend();
			if (AutoTimer->Get() > 0.25) {
				while (floor(drivetrain->GetEncoder()) != 0 ) {
					drivetrain->SetEncoder();
				}
				Step = 5;
			}
			break;
		}
		case 5: {
			if (drivetrain->DriveInches(-28, -0.6)) {
				Step = 6;
			}
			break;
		}
		case 6: {
			elevator->GoToPosition(50, 0.5);
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
			}
			break;
		}
		case 7: {
			if (drivetrain->DriveInches(85, 0.7))  {
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
				while (floor(drivetrain->GetEncoder()) != 0 ) {
					drivetrain->SetEncoder();
				}
			}
			break;
		}
		/*case 10: {
			cubegrabber->Retract();
			elevator->GoToPosition(1500, 0.5);
			if (!Field->GetSwitch()) {
				std::cout << "[AUTOTIMER]" << AutoTimer->Get() << std::endl;
				if (AutoTimer->Get() > 0.25) {
					Step = 11;
					AutoTimer->Reset();
					AutoTimer->Start();
					cubegrabber->RetractArm();
				}
			} else {
				drivetrain->KillDrive();
			}
			break;
		}
		case 11: {
			elevator->GoToPosition(1500, 0.5);
			if (drivetrain->DriveInches(12, 0.5)) {
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
			break;
		}*/


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
			std::cout << "[Auto] " << drivetrain->GetGyro() << std::endl;
			if (drivetrain->DriveInches(200, 1.1)) {
				while (floor(drivetrain->GetEncoder()) != 0 ) {
					drivetrain->SetEncoder();
				}

				Step = 104;
			}
			break;
		}
		case 104: {
			elevator->GoToPosition(7600, 0.5);
			if (drivetrain->TurnToAngle(0)) {
				drivetrain->SetRefAngle(0);
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