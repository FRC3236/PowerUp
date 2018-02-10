//
// Created by robotics on 1/20/2018.
//

#include "Elevator.h"
#include "../RobotMap.h"
#include <iostream>
#include <cmath>

//8650 is the top of the elevator//
double MaxHeight = 8650;

Elevator::Elevator() : Subsystem("Elevator"){
	Motor = new WPI_TalonSRX(LIFTCAN);
	Tray = new WPI_TalonSRX(TRAYCAN);
	LiftQuadrature = new FeedbackDevice(QuadEncoder);
	Motor->ConfigSelectedFeedbackSensor(*LiftQuadrature, 0, 0);
	SetEncoder();
	SetName("Elevator");
}

void Elevator::Initialize(){
	Motor->Set(0);
	Tray->Set(0);
}

void Elevator::SetMotor(double speed) {
	Motor->Set(speed);
}

void Elevator::Ascend(double speed) {
	double sp = speed;
	if (GetEncoder() > 7000) {
		sp = speed * ((MaxHeight - fabs(GetEncoder())) / MaxHeight)*3;
	}
	std::cout << "[elevator a]" << sp << std::endl;
	Motor->Set(-fabs(sp));
}

void Elevator::Descend(double speed) {
	double sp = speed;
	if (GetEncoder() < 1000) {
		sp = speed*(fabs(GetEncoder())/1000);
	}
	std::cout << "[elevator d]" << sp << std::endl;
	Motor->Set(fabs(speed));
}

void Elevator::SetEncoder() {
	Motor->SetSelectedSensorPosition(0, 0, 0);
}

double Elevator::GetEncoder() {
	return Motor->GetSelectedSensorPosition(0);
}

bool Elevator::GoToPosition(double targetPos) {
	double currentPos = GetEncoder();
	double marginOfError = 100;
	if (fabs(currentPos - targetPos) > marginOfError) {
		if (currentPos < targetPos) {
			Ascend(0.5);
		} else {
			Descend(0.5);
		}
	}
}

void Elevator::GoToSwitch(){
	GoToPosition(300);
}

bool Elevator::DeadZone(){
	bool DeadBool = (GetEncoder() >= 7000 && Motor->Get() < 0) || (GetEncoder() <= 0 && Motor->Get() > 0);
	SmartDashboard::PutBoolean("Deadzone", DeadBool);
	return DeadBool;
}

void Elevator::SetTray(double speed) {
	Tray->Set(speed);
}