#include "DisableCompressor.h"

DisableCompressor::DisableCompressor() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(elevator);
}

// Called just before this Command runs the first time
void DisableCompressor::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void DisableCompressor::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool DisableCompressor::IsFinished() {

}

// Called once after isFinished returns true
void DisableCompressor::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DisableCompressor::Interrupted() {

}