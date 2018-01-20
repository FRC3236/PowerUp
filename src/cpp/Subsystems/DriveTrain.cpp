/**
	Team 3236 [Power Up!] | DriveTrain.cpp
	Purpose: Define all DriveTrain methods

	@author Eric Bernard
	@version 1.0 01/06/18
*/

#include "DriveTrain.h"
#include "../RobotMap.h"
#include <iostream>
#include <cmath>

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
	LeftSideA = new WPI_TalonSRX(LEFTCANENCODER);
	RightSideA = new WPI_TalonSRX(RIGHTCANENCODER);
	LeftSideB = new WPI_TalonSRX(LEFTCANBASIC);
	RightSideB = new WPI_TalonSRX(RIGHTCANBASIC);

	LeftSideQuadrature = new FeedbackDevice(QuadEncoder);
	RightSideQuadrature = new FeedbackDevice(QuadEncoder);

	LeftSwitch = new DigitalInput(0);
	RightSwitch = new DigitalInput(1);

    Gyro = new ADXRS450_Gyro();
	AnInput = new AnalogInput(0);

	RefAngle = Gyro->GetAngle();

	LeftSideA->ConfigSelectedFeedbackSensor(*LeftSideQuadrature, 0, 0);
	RightSideA->ConfigSelectedFeedbackSensor(*RightSideQuadrature, 0, 0);
	SetEncoder();

	SetName("DriveTrain");
	pid = new PID(0);
}
bool DriveTrain::GetLeftSwitch(){
	return LeftSwitch->Get();
}

bool DriveTrain::GetRightSwitch(){
	return RightSwitch->Get();
}

void DriveTrain::SetLeft(double speed) {
	LeftSideA->Set(speed);
	LeftSideB->Set(speed);
}

void DriveTrain::SetPID(double fac) {
	this->pid->Point(fac);
}

void DriveTrain::SetRight(double speed) {
	RightSideA->Set(speed);
	RightSideB->Set(speed);
}


void DriveTrain::Drive(double leftSpeed, double rightSpeed) {
	SetLeft(leftSpeed);
	SetRight(rightSpeed);

	return;
}

void DriveTrain::Drive(double speed) {
	SetLeft(speed);
	SetRight(-speed);
}

void DriveTrain::Turn(double speed) {
	SetLeft(speed);
    SetRight(speed);
}

bool DriveTrain::DriveInches(double inches, double speed) {
    double distance = GetEncoder();
	double err = (inches - distance) / inches;
    if (distance > inches) {
		speed = 0;
	}
	this->pid->Update(distance);
    DriveStraight(fmax(speed * err,0.25), RefAngle);
	SmartDashboard::PutNumber("Error", distance);
	return (distance > inches);
}
double DriveTrain::GetGyro() {
	return Gyro->GetAngle();
}

void DriveTrain::SetEncoder(){
    LeftSideA->SetSelectedSensorPosition(0, 0, 0);
	RightSideA->SetSelectedSensorPosition(0, 0, 0);
}

double DriveTrain::GetEncoder(){
	double SideA = LeftSideA->GetSelectedSensorPosition(0) / 1440.0 * 6.0 * M_PI;
	//double SideB = -(RightSideA->GetSelectedSensorPosition(0) / 1440.0 * 6.0 * M_PI);
	//return (SideA + SideB) / 2;
	return SideA;
}

void DriveTrain::DriveStraight(double speed, double refAngle) {
	double currentAngle = Gyro->GetAngle();
	double error = currentAngle - refAngle;
	//SmartDashboard::PutNumber("Error", error);
	double marginOfError = 1.6;
	double constSpeedChange = 0.03;
	double maxAngle = 15;
	std::cout << (error/maxAngle) << std::endl;
	double correction = constSpeedChange * ((error/maxAngle)/2);
	if (fabs(error) > marginOfError) {
		if (currentAngle > refAngle) {
			Drive(fmin(speed-this->pid->GetPI(), speed-0.3), -(speed));
		} else {
			Drive(speed, -(fmin(speed-this->pid->GetPI(), speed-0.3)));
		}
	} else {
		Drive(speed);
	}

}

bool DriveTrain::TurnAngle(double angle){
    double turn;
    double current = Gyro->GetAngle();
	double targetAngle = RefAngle + angle;
	double error = ((targetAngle - current) / angle);
    if (targetAngle > 0) {
		turn = 0.5;
	} else {
		turn = -0.5;
	}
	double speed = fmax(turn * error, 0.2);

	Turn(speed);
	std::cout << Gyro->GetAngle() << " " << targetAngle << std::endl;
	if (fabs(Gyro->GetAngle()) >  fabs(targetAngle)) {
		Turn(0);
	}

	SmartDashboard::PutNumber("Gyro", current);
	SmartDashboard::PutNumber("Error", error);

	if (fabs(targetAngle) - fabs(current) < 4) {
		return true;
	}

	//SmartDashboard::PutNumber("Error", speed);
	return (fabs(Gyro->GetAngle()) > fabs(targetAngle));
}

void DriveTrain::Calibrate(){
    Gyro->Calibrate();
}

double DriveTrain::GetDistance() {
	return this->AnInput->GetVoltage() / 0.0049 / 2.54 / 12;
}

/**
	Runs once the SystemBase initializes the DriveTrain

	@return void
*/
void DriveTrain::Initialize() {
	KillDrive();

	return;
}
/**
	Stops all Talon SRX's

	@return void
*/
void DriveTrain::KillDrive() {
	Drive(0,0);

	return;
}

void DriveTrain::SetRefAngle(double newRefAngle) {
	RefAngle = newRefAngle;
}

double DriveTrain::GetRefAngle() {
	return RefAngle;
}