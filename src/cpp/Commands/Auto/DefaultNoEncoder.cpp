//
// Created by robotics on 4/27/2018.
//

#include "DefaultNoEncoder.h"

DefaultNoEncoder::DefaultNoEncoder() {
	AutoTimer = new Timer();
	AutoTimer->Stop();
	AutoTimer->Reset();
	Step = 1;
	Requires(drivetrain);
}

void DefaultNoEncoder::Initialize() {
	AutoTimer->Start();
	Step = 1;
	drivetrain->KillDrive();
}

void DefaultNoEncoder::Execute() {
	if (AutoTimer->Get() < 6.5) {
		drivetrain->DriveStraight(0.2, 0);
	} else {
		drivetrain->KillDrive();
	}
}

void DefaultNoEncoder::Interrupted() {
	drivetrain->KillDrive();
}

void DefaultNoEncoder::End() {
	drivetrain->KillDrive();
}

bool DefaultNoEncoder::IsFinished() {
	return AutoTimer->Get() > 6.5;
}