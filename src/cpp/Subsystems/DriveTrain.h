#ifndef DriveTrain_H
#define DriveTrain_H

#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include "WPILib.h"
#include "../PID.h"

class DriveTrain : public frc::Subsystem {
private:
	// Delineate Objects //
	WPI_TalonSRX *LeftSideA, *LeftSideB, *RightSideA, *RightSideB, *Lift;
	FeedbackDevice *LeftSideQuadrature, *RightSideQuadrature, *LiftQuadrature;
	DigitalInput *LeftSwitch, *RightSwitch;
	AnalogInput * AnInput;
    ADXRS450_Gyro * Gyro;
	PID * pid;

	// Delineate Data //
	double RefAngle;

public:
	DriveTrain();
	void Initialize();

	// Drive Functions //
	void Drive(double);
	void Drive(double,double);
	void KillDrive();
	void DriveStraight(double, double);
	bool DriveInchesFast(double,double);
	bool DriveInches(double, double);

	bool TurnAngle(double);
	bool TurnToAngle(double);
	bool TurnToAngle(double,double);
	void Turn(double);

	void SetLeft(double);
	void SetRight(double);
	//void SetLift(double);

	// Data Getters //
	bool GetLeftSwitch();
	bool GetRightSwitch();
	double GetEncoder();
	double GetLiftEncoder();
	double GetDistance();
	double GetGyro();
	double GetLeftTalon();
	double GetRightTalon();
	double GetRefAngle();

	// Data Setters //
	void SetEncoder();
    void Calibrate();
	void ResetGyro();
	void SetPID(double);
	void SetRefAngle(double);
};

#endif  // DriveTrain_H
