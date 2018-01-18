//
// Created by robotics on 1/13/2018.
//

#include "ResetGyro.h"

ResetGyro::ResetGyro() {
	//Requires(drivetrain);
}

void ResetGyro::Initialize() {

}

void ResetGyro::Execute() {
	CommandBase::drivetrain->ResetGyro();
	End();
}

void ResetGyro::End() {

}

void ResetGyro::Interrupted() {
	End();
}

bool ResetGyro::IsFinished() {
	return true;
}