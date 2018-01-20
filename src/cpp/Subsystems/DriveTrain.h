#ifndef DriveTrain_H
#define DriveTrain_H

#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include "WPILib.h"
#include "../PID.h"

class DriveTrain : public frc::Subsystem {
private:
	WPI_TalonSRX *LeftSideA, *LeftSideB, *RightSideA, *RightSideB;
	//void DriveInternal(double,double,double,double);

	FeedbackDevice *LeftSideQuadrature, *RightSideQuadrature;

	DigitalInput *LeftSwitch, *RightSwitch;

	AnalogInput * AnInput;
    ADXRS450_Gyro * Gyro;
	double RefAngle;
	PID * pid;

public:
	DriveTrain();
	bool GetLeftSwitch();
	bool GetRightSwitch();
	void Initialize();
	void Drive(double);
	void Drive(double,double);
	void KillDrive();
	void DriveStraight(double, double);
    bool DriveInches(double, double);
    void SetEncoder();
	double GetEncoder();
	double GetDistance();
    double GetGyro();
    void Calibrate();
    bool TurnAngle(double);
    void Turn(double);

	void SetLeft(double);
	void SetRight(double);

	void SetPID(double);



	double GetRefAngle();
	void SetRefAngle(double);
};

#endif  // DriveTrain_H
