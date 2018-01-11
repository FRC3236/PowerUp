#ifndef DriveTrain_H
#define DriveTrain_H

#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include "WPILib.h"

class DriveTrain : public frc::Subsystem {
private:
	WPI_TalonSRX *FrontLeft, *BackLeft, *FrontRight, *BackRight;
	void DriveInternal(double,double,double,double);
	AnalogInput * AnInput;
public:
	DriveTrain();
	void Initialize();
	void Drive(double,double);
	void Drive(double);
	void Traverse(double);
	void KillDrive();

	double GetDistance();
};

#endif  // DriveTrain_H
