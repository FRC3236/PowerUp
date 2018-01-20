//
// Created by robotics on 1/17/2018.
//

#include "PID.h"

PID::PID(double point) {
	this->PFac = 1;
	this->IFac = 1;
	this->DFac = 1;

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
	this->I += (this->P * 0.02);
	this->D = (this->P - this->preverror) / 0.02;

	this->preverror = this->P;
}

double PID::GetPI() {
	return (this->PFac * this->P) + (this->IFac * this->I);
}

void PID::Reset(double point) {
	this->P = 1;
	this->I = 1;
	this->D = 1;

	this->point = point;
}