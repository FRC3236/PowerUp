//
// Created by robotics on 1/13/2018.
//

#include "ResetEncoders.h"

ResetEncoders::ResetEncoders() {
	//Requires(drivetrain);
}

void ResetEncoders::Initialize() {

}

void ResetEncoders::Execute() {
	CommandBase::drivetrain->SetEncoder();
	End();
}

void ResetEncoders::End() {

}

void ResetEncoders::Interrupted() {
	End();
}

bool ResetEncoders::IsFinished() {
	return true;
}