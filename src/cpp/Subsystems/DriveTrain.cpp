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
	LeftSide = new WPI_TalonSRX(FRONTLEFTCANPORT);
	RightSide = new WPI_TalonSRX(BACKRIGHTCANPORT);

	LeftSideQuadrature = new FeedbackDevice(QuadEncoder);
	RightSideQuadrature = new FeedbackDevice(QuadEncoder);

    Gyro = new ADXRS450_Gyro();
	AnInput = new AnalogInput(0);

	RefAngle = Gyro->GetAngle();

	LeftSide->ConfigSelectedFeedbackSensor(*LeftSideQuadrature, 0, 0);
	RightSide->ConfigSelectedFeedbackSensor(*RightSideQuadrature, 0, 0);
	SetEncoder();
}

/**
	Sets the speeds of each Talon SRX individually
	@param fls : the desired speed of LeftSide
	@param frs : the desired speed of FrontRight
	@param bls : the desired speed of BackLeft
	@param brs : the desired speed of RightSide

	@return void
*/
void DriveTrain::Drive(double fls, double brs) {
	LeftSide->Set(fls);
	RightSide->Set(brs);

	return;
}

void DriveTrain::Drive(double s){
    this->LeftSide->Set(s);
    this->RightSide->Set(-s);
}

void DriveTrain::Turn(double speed) {
	LeftSide->Set(speed);
    RightSide->Set(speed);
}

bool DriveTrain::DriveInches(double inches, double speed) {
    double distance = GetEncoder();
	double err = (inches - distance) / inches;
    if (distance > inches) {
        speed = 0;
    }
	std::cout << "REFANGLE: " << RefAngle << std::endl;
    Drive(fmax(speed * err,0.25));
	SmartDashboard::PutNumber("Error", distance);
	return (distance > inches);
}

double DriveTrain::GetGyro() {
	return Gyro->GetAngle();
}

void DriveTrain::SetEncoder(){
    LeftSide->SetSelectedSensorPosition(0, 0, 0);
	RightSide->SetSelectedSensorPosition(0, 0, 0);
}

double DriveTrain::GetEncoder(){
	double SideA = LeftSide->GetSelectedSensorPosition(0) / 1440.0 * 6.0 * M_PI;
	double SideB = -(RightSide->GetSelectedSensorPosition(0) / 1440.0 * 6.0 * M_PI);
	//return (SideA + SideB) / 2;
	return SideA;
}

void DriveTrain::DriveStraight(double speed, double refAngle) {
	double currentAngle = Gyro->GetAngle();
	double error = currentAngle - refAngle;
	//SmartDashboard::PutNumber("Error", error);
	int marginOfError = 1;
	double constSpeedChange = 0.05;
	double maxAngle = 15;
	double correction = constSpeedChange * (error/maxAngle);
	if (fabs(error) > marginOfError) {
		if (currentAngle > refAngle) {
			Drive(fmin(speed-correction, speed-0.3), -(speed));
		} else {
			Drive(speed, -(fmin(speed-correction, speed-0.3)));
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
		turn = 0.7;
	} else {
		turn = -0.7;
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
	this->KillDrive();

	return;
}
/**
	Stops all Talon SRX's

	@return void
*/
void DriveTrain::KillDrive() {
	this->Drive(0,0);

	return;
}

void DriveTrain::SetRefAngle(double newRefAngle) {
	RefAngle = newRefAngle;
}

double DriveTrain::GetRefAngle() {
	return RefAngle;
}