//
// Created by robotics on 1/20/2018.
//

#include "Elevator.h"
#include "../RobotMap.h"
#include <iostream>
#include <cmath>

//8650 is the top of the elevator//
double MaxHeight = 8200;
double MaxHeightCapture = MaxHeight - 750;
int count = 0;
double avg = 0;
int stalled = -1; // 0 means stalled forward, 1 is stalled backwards

Elevator::Elevator() : Subsystem("Elevator"){
	MotorA = new WPI_TalonSRX(LIFTCAN);
	MotorB = new WPI_TalonSRX(LIFTCAN2);
	LiftQuadrature = new FeedbackDevice(QuadEncoder);
	MotorA->ConfigSelectedFeedbackSensor(*LiftQuadrature, 0, 0);
	SetEncoder();
	SetName("Elevator");
}

void Elevator::Initialize(){
	MotorA->Set(0);
	MotorB->Set(0);
}

void Elevator::SetEncoder() {
	MotorA->SetSelectedSensorPosition(0,0,0);
	std::cout << "[Elevator] Set encoder to 0!" << std::endl;
}

void Elevator::SetMotor(double speed) {
	MotorA->Set(speed);
	MotorB->Set(speed);
}

void Elevator::Ascend(double speed) {
	double sp = speed;
	if (GetEncoder() > MaxHeightCapture) {
		sp = speed * ((MaxHeight - fabs(GetEncoder())) / MaxHeight)*10;
	}
	MotorA->Set(-fabs(sp));
	MotorB->Set(fabs(sp));
}

void Elevator::AscendTo(double speed, double pos) {
	double sp = speed;
	pos = fmin(pos, MaxHeightCapture);
	if (GetEncoder() > pos) {
		sp = speed * ((pos - fabs(GetEncoder())) / pos)*10;
	}
	std::cout << "[elevator a]" << sp << std::endl;
	Ascend(-fabs(sp));
}

void Elevator::Descend(double speed) {
	double sp = speed;
	if (GetEncoder() < 1000) {
		sp = speed*(fabs(GetEncoder())/1000);
	}
	//std::cout << "[elevator d]" << sp << std::endl;
	MotorA->Set(fabs(speed));
	MotorB->Set(-fabs(speed));
}

double Elevator::GetEncoder() {
	return MotorA->GetSelectedSensorPosition(0);
}

bool Elevator::GoToPosition(double targetPos) {
	return GoToPosition(targetPos, 0.5);
}

bool Elevator::GoToPosition(double targetPos, double speed) {
	double currentPos = GetEncoder();
	bool backwards = false;
	if (currentPos > targetPos) {
		double tempPos = targetPos;
		targetPos = currentPos;
		currentPos = tempPos;
		backwards = true;
	}
	double err = (fabs(targetPos - currentPos)) / targetPos;
	std::cout << "[Elevator GoToPosition] Backwards: " << backwards << " | " << err << std::endl;
	if (err < 0.05) {
		if (backwards) {
			Descend(speed * err);
		} else {
			Ascend(speed * err);
		}
		return false;
	} else {
		return true;
	}
}