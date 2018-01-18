//
// Created by robotics on 1/17/2018.
//

#include "PID.h"
#include "WPILib.h"
#include <iostream>

PID::PID(double point) {
	this->Reset(point);
}

void PID::Point(double point) {
	this->point = point;
}

double PID::Point() {
	return this->point;
}

void PID::Update(double factor) {
	this->P = this->point - factor;
	this->I += (this->P);
	this->D = (this->P - this->preverror) / 0.02;

	this->preverror = this->P;
}

double PID::GetPI() {
	std::cout << "[PIDcpp] P:" << this->P << " I:" << this->I << " | Point: " << this->point << std::endl;
	frc::SmartDashboard::PutNumber("Error",(this->PFac * this->P) + (this->IFac * this->I));
	return (this->PFac * this->P) + (this->IFac * this->I);
}

void PID::Reset(double point) {
	this->P = 0;
	this->I = 0;
	this->D = 0;
	this->PFac = 0.002;
	this->IFac = 0.002;
	this->DFac = 0.002;
	this->point = point;
}