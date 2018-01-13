#ifndef DriveTrain_H
#define DriveTrain_H

#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include "WPILib.h"

class DriveTrain : public frc::Subsystem {
private:
	WPI_TalonSRX *LeftSide, *RightSide;
	//void DriveInternal(double,double,double,double);

	FeedbackDevice *LeftSideQuadrature, *RightSideQuadrature;

	AnalogInput * AnInput;
    ADXRS450_Gyro * Gyro;
	double RefAngle;
public:
	DriveTrain();
	void Initialize();
	void Drive(double);
	void KillDrive();
	void DriveInternal(double,double);
	void DriveStraight(double, double);
    bool DriveInches(double, double);
    void SetEncoder();
	double GetEncoder();
	double GetDistance();
    double GetGyro();
    void Calibrate();
    bool TurnAngle(double);
    void Turn(double);

	double GetRefAngle();
	void SetRefAngle(double);
};

#endif  // DriveTrain_H
