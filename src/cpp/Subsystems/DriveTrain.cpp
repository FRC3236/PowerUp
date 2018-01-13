/**
	Team 3236 [Power Up!] | DriveTrain.cpp
	Purpose: Define all DriveTrain methods

	@author Eric Bernard
	@version 1.0 01/06/18
*/

#include "DriveTrain.h"
#include "../RobotMap.h"
#include <cmath>


DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
	FrontLeft = new WPI_TalonSRX(FRONTLEFTCANPORT);
	FrontRight = new WPI_TalonSRX(FRONTRIGHTCANPORT);
	BackLeft = new WPI_TalonSRX(BACKLEFTCANPORT);
	BackRight = new WPI_TalonSRX(BACKRIGHTCANPORT);

	FrontLeftQuadrature = new FeedbackDevice(QuadEncoder);

    Gyro = new ADXRS450_Gyro();
	AnInput = new AnalogInput(0);
}

/**
	Sets the speeds of each Talon SRX individually
	@param fls : the desired speed of FrontLeft
	@param frs : the desired speed of FrontRight
	@param bls : the desired speed of BackLeft
	@param brs : the desired speed of BackRight

	@return void
*/
void DriveTrain::DriveInternal(double fls, double bls, double brs, double frs) {
	this->FrontLeft->Set(fls);
	this->FrontRight->Set(frs);
	this->BackLeft->Set(bls);
	this->BackRight->Set(brs);

	return;
}

void DriveTrain::Drive(double s){
    this->FrontLeft->Set(s);
    this->BackRight->Set(s);
}

void DriveTrain::CheckInches(double inches) {
    double distance = this->FrontLeft->GetSelectedSensorPosition(0) / 1440 * 6 * M_PI;
    while (distance <= inches)
    {
        this->Drive(1);
    }
}

void DriveTrain::SetEncoder(){
    FrontLeft->ConfigSelectedFeedbackSensor(*FrontLeftQuadrature, 0, 0);
}

double DriveTrain::GetEncoder(){
	return this->FrontLeft->GetSelectedSensorPosition(0) / 1440 * 6 * M_PI;

}
double DriveTrain::GetGyro(){
   return this->Gyro->GetAngle();
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
	Public-facing interface to set the speeds of the Talon SRX's
	@param leftSpeed : the desired speed of the left side of the DriveTrain
	@param rightSpeed : the desired speed of the right side of the DriveTrain

	@return void
*/
void DriveTrain::Drive(double leftSpeed, double rightSpeed) {
	this->DriveInternal(leftSpeed, leftSpeed, rightSpeed, rightSpeed);

	return;
}

/**
	Public-facing interface to set the speeds of the Talon SRX's; drives only forwards or backwards
	@param speed : the desired speed of the DriveTrain

	@return void
*/
/*void DriveTrain::Drive(double speed) {
	this->DriveInternal(-speed, -speed, speed, speed);

	return;
}*/

/**
	Drives robot laterally without changing orientation
	@param speed : the desired speed of the DriveTrain

	@return void
*/
void DriveTrain::Traverse(double speed) {
	this->DriveInternal(speed, -speed, -speed, speed);

	return;
}

/**
	Stops all Talon SRX's

	@return void
*/
void DriveTrain::KillDrive() {
	this->DriveInternal(0,0,0,0);

	return;
}
