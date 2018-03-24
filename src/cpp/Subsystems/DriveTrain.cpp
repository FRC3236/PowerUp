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
	this->pid->Reset(fac);
}

void DriveTrain::SetRight(double speed) {
	RightSideA->Set(speed);
	RightSideB->Set(speed);
}

void DriveTrain::Drive(double leftSpeed, double rightSpeed) {
	SetLeft(leftSpeed);
	SetRight(rightSpeed);
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
	double err = fabs((inches - distance) / inches);
	std::cout << "[DriveInches] Dist:" << distance << " Dest:" << inches << std::endl;
	if (err < 0.03) {
		speed = 0;
	}

	if (speed >= 0) {
		DriveStraight(fmax(speed * err, 0.25), RefAngle);
		return (distance > inches);
	} else {
		Drive(fmax(-(fabs(speed) * err), -0.25));
		return (distance < inches);
	}
	//SmartDashboard::PutNumber("Error", distance);

	//std::cout << "[DriveTrain](DriveInches) -> Target: " << inches << " | Current: " << distance << " | Error: "  << err << " | Speed: " << speed << std::endl;

}

bool DriveTrain::DriveInchesFast(double inches, double speed) {
	double distance = GetEncoder();
	double startPos = inches/2;
	double err;
	if (distance > startPos) {
		err = fabs(((inches-startPos) - (distance-startPos))/(inches-startPos));
	} else {
		err = 1;
	}

	std::cout << "[DriveTrain DIF] " << err << " " << speed * err << " " << startPos << std::endl;

	if (err < 0.03) {
		speed = 0;
	}

	if (speed >= 0) {
		DriveStraight(fmax(speed * err, 0.25), RefAngle);
		return (distance > inches);
	} else {
		std::cout << speed * err <<  std::endl;
		Drive(fmax(-(fabs(speed) * err), -0.25));
		std::cout << (distance > inches) << std::endl;
		return (distance < inches);
	}
}


double DriveTrain::GetGyro() {
	return Gyro->GetAngle();
}

void DriveTrain::SetEncoder() {
	while (GetEncoder() != 0) {
		LeftSideA->SetSelectedSensorPosition(0, 0, 0);
		RightSideA->SetSelectedSensorPosition(0, 0, 0);
	}
}

double DriveTrain::GetEncoder() {
	return LeftSideA->GetSelectedSensorPosition(0) / 1440.0 * 6.0 * M_PI; // was left side but i just switched it
}

void DriveTrain::DriveStraight(double speed, double refAngle) {
	double currentAngle = Gyro->GetAngle();
	double error = currentAngle - refAngle;
	double marginOfError = 1.6;

	// PID is still in beta and if it doesn't work we can revert //
	//              to pure proportional control                 //
	this->pid->Update(currentAngle);
	double correction = (this->pid->GetPI() / 100)/2; // divide by 2
	correction = fmin(speed - correction, speed - 0.2);
	//std::cout << "[DriveTrain Correction] " << correction << std::endl;

	if (fabs(error) > marginOfError) {
		if (currentAngle > refAngle) {
			std::cout << "[DriveTrain DS] " << correction << ", " << -(fabs(speed)) << std::endl;
			Drive(correction, -(fabs(speed)));
		} else {
			Drive(speed, -(fabs(correction)));
			std::cout << "[DriveTrain DS] " << -(fabs(correction)) << ", " << speed << std::endl;
		}
	} else {
		std::cout << "[DriveTrain DS] " << speed << std::endl;
		Drive(speed);
	}

}

bool DriveTrain::TurnAngle(double angle) {
    double turn = 0.75;

    double current = Gyro->GetAngle();

	double targetAngle = RefAngle + angle;
	double error = ((targetAngle - current) / angle);
	this->pid->Update(current);
	double speed = fmax((turn * error) /2, 0.1);


	if (targetAngle < current) {
		speed = -speed;
	}
	//std::cout << speed << std::endl;
	Turn(speed);
	//std::cout << Gyro->GetAngle() << " " << targetAngle << std::endl;
	if (fabs(Gyro->GetAngle()) >  fabs(targetAngle)) {
		Turn(0);
	}

	SmartDashboard::PutNumber("GYRO", current);
	//SmartDashboard::PutNumber("Error", error);
	SmartDashboard::PutNumber("Drive Encoder", this->GetEncoder());

	if (fabs(targetAngle) - fabs(current) < 4) {
		return true;
	}

	//SmartDashboard::PutNumber("Error", speed);
	return (fabs(Gyro->GetAngle()) > fabs(targetAngle));
}

bool DriveTrain::TurnToAngle(double target) {
	double current = Gyro->GetAngle();
	double error;
	double speed;
	double turn = 0.5;
	if (target == 0) {
		turn = 0.2;
		error = fabs(target-current)*0.05;
		speed = fmax(turn * error, 0.2);
	} else {
		error = ((fabs(target) - fabs(current)) / fabs(target));
		speed = fmax(turn * error, 0.4);
	}

	if (target < current) {
		Turn(-speed);
	} else {
		Turn(speed);
	}
	return (fabs(error) < 0.02);
}

bool DriveTrain::TurnToAngle(double target, double turn) {
	double current = Gyro->GetAngle();
	double error;
	double speed;
	if (target == 0) {
		turn = 0.2;
		error = fabs(target-current)*0.1;
		speed = fmax(turn * error, 0.2);
		//std::cout << "[DriveTrain] " << speed << std::endl;
	} else {
		error = ((fabs(target) - fabs(current)) / fabs(target));
		speed = fmax(turn * error, 0.4);
	}
	//std::cout << error << std::endl;

	//std::cout << "[DriveTrain] " << target << " " << current << " " << error << std::endl;

	if (target < current) {
		Turn(-speed);
	} else {
		Turn(speed);
	}
	return (fabs(error) < 0.02);
}

void DriveTrain::ResetGyro() {
	Gyro->Reset();
}

void DriveTrain::Calibrate() {
    Gyro->Calibrate();
}

double DriveTrain::GetDistance() {
	return this->AnInput->GetVoltage() / 0.0049 / 2.54 / 12;
}

void DriveTrain::Initialize() {
	KillDrive();

	return;
}

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

double DriveTrain::GetLeftTalon() {
	return LeftSideA->Get();
}
double DriveTrain::GetRightTalon() {
	return RightSideA->Get();
}