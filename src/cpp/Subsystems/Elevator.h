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

public:
	DoubleSolenoid *Solenoid1, *Solenoid2, *Solenoid3, *Solenoid4;
	Compressor *CompressorPort;

	Elevator();
	void Initialize();
};


#endif //NEWPOWERUP_ELEVATOR_H
