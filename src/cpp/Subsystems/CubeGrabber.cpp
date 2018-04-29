//
// Created by robotics on 2/3/2018.
//

#include "CubeGrabber.h"
#include "../RobotMap.h"
#include <iostream>

CubeGrabber::CubeGrabber() : Subsystem("CubeGrabber") {
	SetName("CubeGrabber");
	Comp = new Compressor(0);
	Opened = true;
	ArmDown = true;
	Solenoid1 = new DoubleSolenoid(SolenoidPort1, SolenoidPort1 + 1);
	Solenoid2 = new DoubleSolenoid(SolenoidPort2, SolenoidPort2 + 1);

	IntakeLeft = new WPI_TalonSRX(INTAKEL);
	IntakeRight = new WPI_TalonSRX(INTAKER);

	//StopCompressor();
	//Extend();
};

void CubeGrabber::Retract() {
	Solenoid1->Set(DoubleSolenoid::Value::kOff);
	Solenoid1->Set(DoubleSolenoid::Value::kForward);
	Opened = false;
}
void CubeGrabber::Extend() {
	Solenoid1->Set(DoubleSolenoid::Value::kOff);
	Solenoid1->Set(DoubleSolenoid::Value::kReverse);
	Opened = true;
}
void CubeGrabber::RetractArm() {
	Solenoid2->Set(DoubleSolenoid::Value::kOff);
	Solenoid2->Set(DoubleSolenoid::Value::kReverse);
	ArmDown = false;
}
void CubeGrabber::ExtendArm() {
	Solenoid2->Set(DoubleSolenoid::Value::kOff);
	Solenoid2->Set(DoubleSolenoid::Value::kForward);
	ArmDown = true;
}

void CubeGrabber::Stop() {
	Solenoid1->Set(DoubleSolenoid::Value::kOff);
}

bool CubeGrabber::IsOpen() {
	std::cout << Solenoid1->Get() << std::endl;
	std::cout << (Solenoid1->Get() == 2) << std::endl << std::endl;
	return Solenoid1->Get() == 2;
}

void CubeGrabber::SpinIntake(double speed) {
	IntakeLeft->Set(-fmin(speed, 0.5));
	IntakeRight->Set(-fmin(speed, 0.5));
}

bool CubeGrabber::GetCompressor() {
	return Comp->GetClosedLoopControl();
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