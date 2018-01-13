#ifndef DriveTrain_H
#define DriveTrain_H

#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include "WPILib.h"

class DriveTrain : public frc::Subsystem {
private:
	WPI_TalonSRX *FrontLeft, *BackLeft, *FrontRight, *BackRight;
	//void DriveInternal(double,double,double,double);

	FeedbackDevice *FrontLeftQuadrature;

	AnalogInput * AnInput;
    ADXRS450_Gyro * Gyro;
public:
	DriveTrain();
	void Initialize();
	void Drive(double,double);
	void Drive(double);
	void Traverse(double);
	void KillDrive();
	void DriveInternal(double,double,double,double);

    void CheckInches(double);
    void SetEncoder();
	double GetEncoder();
	double GetDistance();
    double GetGyro();
    void Calibrate();
};

#endif  // DriveTrain_H
