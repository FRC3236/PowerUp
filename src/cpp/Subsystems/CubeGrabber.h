//
// Created by robotics on 2/3/2018.
//

#ifndef NEWPOWERUP_CUBEGRABBER_H
#define NEWPOWERUP_CUBEGRABBER_H
#include "WPILib.h"
#include <ctre/Phoenix.h>

class CubeGrabber : public frc::Subsystem {
private:
	Compressor * Comp;
	WPI_TalonSRX * IntakeLeft, * IntakeRight;
	DoubleSolenoid * Solenoid1, * Solenoid2;
public:
	CubeGrabber();
	void Initialize();
	void Extend();
	void Retract();
	void ExtendArm();
	void RetractArm();

	bool IsOpen();

	void SpinIntake(double);

	void Stop();
	void StartCompressor();
	void StopCompressor();
	void ToggleCompressor();
	bool GetCompressor();
	bool Opened;
	bool ArmDown;
};


#endif //NEWPOWERUP_CUBEGRABBER_H
