//
// Created by robotics on 1/20/2018.
//

#include "Elevator.h"
#include "../RobotMap.h"
#include <iostream>
#include <cmath>

Elevator::Elevator() : Subsystem("Elevator"){
	CompressorPort = new Compressor(0);
	Solenoid1 = new DoubleSolenoid(SolenoidPort1, SolenoidPort1 + 1);
	Solenoid2 = new DoubleSolenoid(SolenoidPort2, SolenoidPort2 + 1);
	Solenoid3 = new DoubleSolenoid(SolenoidPort3, SolenoidPort3 + 1);
	Solenoid4 = new DoubleSolenoid(SolenoidPort4, SolenoidPort4 + 1);
}

void Elevator::Initialize(){
	Solenoid1->Set(DoubleSolenoid::Value::kOff);
	Solenoid2->Set(DoubleSolenoid::Value::kOff);
	Solenoid3->Set(DoubleSolenoid::Value::kOff);
	Solenoid4->Set(DoubleSolenoid::Value::kOff);
}

