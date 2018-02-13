//
// Created by robotics on 2/3/2018.
//

#include "CubeGrabber.h"
#include "../RobotMap.h"

CubeGrabber::CubeGrabber() : Subsystem("CubeGrabber") {
	SetName("CubeGrabber");
	Comp = new Compressor(0);
	Opened = true;
	Solenoid1 = new DoubleSolenoid(SolenoidPort1, SolenoidPort1 + 1);

	StopCompressor();
	//Extend();
};

void CubeGrabber::Extend() {
	Solenoid1->Set(DoubleSolenoid::Value::kOff);
	Solenoid1->Set(DoubleSolenoid::Value::kForward);
	Opened = true;
}

void CubeGrabber::Retract() {
	Solenoid1->Set(DoubleSolenoid::Value::kOff);
	Solenoid1->Set(DoubleSolenoid::Value::kReverse);
	Opened = false;
}

void CubeGrabber::Stop() {
	Solenoid1->Set(DoubleSolenoid::Value::kOff);
}

void CubeGrabber::StartCompressor() {
	Comp->SetClosedLoopControl(true);
}

void CubeGrabber::StopCompressor() {
	Comp->SetClosedLoopControl(false);
};

void CubeGrabber::ToggleCompressor() {
	Comp->SetClosedLoopControl(!Comp->GetClosedLoopControl());
}