//
// Created by robotics on 1/20/2018.
//

#include "Elevator.h"
#include "../RobotMap.h"
#include <iostream>
#include <cmath>

//8650 is the top of the elevator/
int count = 0;
double avg = 0;
int stalled = -1; // 0 means stalled forward, 1 is stalled backwards
double MaxHeight, MaxHeightCapture;
Elevator::Elevator() : Subsystem("Elevator"){
	MotorA = new WPI_TalonSRX(LIFTCAN);
	MotorB = new WPI_TalonSRX(LIFTCAN2);
	LiftQuadrature = new FeedbackDevice(QuadEncoder);
	MotorB->ConfigSelectedFeedbackSensor(*LiftQuadrature, 0, 0);
	SetEncoder();
	SetName("Elevator");
	MaxHeight = GetMaxHeight();
	MaxHeightCapture = GetMaxHeight() * .75;
}

void Elevator::Initialize(){
	MotorA->Set(0);
	MotorB->Set(0);
}

void Elevator::SetEncoder() {
	MotorB->SetSelectedSensorPosition(0,0,0);
	std::cout << "[Elevator] Set encoder to 0!" << std::endl;
}

double Elevator::GetMaxHeight() {
	return 4825;
}

double Elevator::GetSwitchHeight() {
	return 2100;
}

void Elevator::SetMotor(double speed) {
	MotorA->Set(speed);
	MotorB->Set(speed);
}

void Elevator::Ascend(double speed) {
	double sp = speed;
	if (GetEncoder() > MaxHeightCapture) {
		sp = speed * (((MaxHeight - MaxHeightCapture) - (GetEncoder() - MaxHeightCapture)) / (MaxHeight - MaxHeightCapture));
	}
	std::cout << "MOVING ELEVATOR UP AT " << sp << std::endl;
	MotorA->Set(-fabs(sp));
	MotorB->Set(fabs(sp));
}

void Elevator::AscendTo(double speed, double pos) {
	double sp = speed;
	pos = fmin(pos, MaxHeightCapture);
	if (GetEncoder() > pos) {
		sp = fmin(speed * ((pos - fabs(GetEncoder())) / pos)*10, speed);
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

void Elevator::DescendNoShift(double speed) {
	MotorA->Set(fabs(speed));
	MotorB->Set(-fabs(speed));
}

void Elevator::AscendNoShift(double speed) {
	MotorA->Set(-fabs(speed));
	MotorB->Set(fabs(speed));
}

double Elevator::GetEncoder() {
	return fabs(MotorB->GetSelectedSensorPosition(0));
}

bool Elevator::GoToPosition(double targetPos) {
	return GoToPosition(targetPos, 0.5);
}

bool Elevator::GoToPosition(double targetPos, double speed) {
	double currentPos = GetEncoder();
	std::cout << "ELEVATOR GOTOPOS " << targetPos << " " << GetEncoder() << std::endl;
	bool backwards = false;
	if (currentPos > targetPos) {
		double tempPos = targetPos;
		targetPos = currentPos;
		currentPos = tempPos;
		backwards = true;
	}
	double err = (fabs(targetPos - currentPos)) / targetPos;
	std::cout << "ELEVATOR GOTOPOS " <<  speed << " " << err*2.35<< " " << speed * (err*2.35) << std::endl;
	speed = speed * fmin(1,(err*2.35));
	if (err > 0.05) {
		if (backwards) {
			DescendNoShift(speed);
		} else {
			AscendNoShift(speed);
		}
		return false;
	} else {
		return true;
	}
}