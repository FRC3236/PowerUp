//
// Created by robotics on 1/20/2018.
//

#ifndef NEWPOWERUP_ELEVATOR_H
#define NEWPOWERUP_ELEVATOR_H

#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include "WPILib.h"
#include "../PID.h"

class Elevator : public frc::Subsystem {
private:

	FeedbackDevice * LiftQuadrature;
public:
	WPI_TalonSRX * Motor, * Tray;
	Elevator();
	void SetEncoder();
	double GetEncoder();
	bool GoToPosition(double);
	bool GoToPosition(double,double);
	void Ascend(double);
	void AscendTo(double, double);
	void Descend(double);
	void SetMotor(double);
	void Initialize();
	void GoToSwitch();
	bool DeadZone();
	void SetTray(double);
	void ExtendTray();
	void RetractTray();
};


#endif //NEWPOWERUP_ELEVATOR_H
