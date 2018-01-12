//
// Created by Eric on 1/11/2018.
//

#include "AutoDefault.h"

AutoDefault::AutoDefault() {
	Requires(drivetrain);
}

void AutoDefault::Initialize() {
	drivetrain->KillDrive();
}

void AutoDefault::Execute() {

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