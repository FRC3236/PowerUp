/*
*
*  $$$$$$$$\        $$\ $$$$$$$$\                                             $$$$$$\   $$$$$$\   $$$$$$\   $$$$$$\
*  \__$$  __|       \__|$$  _____|                                           $$ ___$$\ $$  __$$\ $$ ___$$\ $$  __$$\
*     $$ | $$$$$$\  $$\ $$ |    $$$$$$\   $$$$$$\   $$$$$$$\  $$$$$$\        \_/   $$ |\__/  $$ |\_/   $$ |$$ /  \__|
*     $$ |$$  __$$\ $$ |$$$$$\ $$  __$$\ $$  __$$\ $$  _____|$$  __$$\         $$$$$ /  $$$$$$  |  $$$$$ / $$$$$$$\
*     $$ |$$ |  \__|$$ |$$  __|$$ /  $$ |$$ |  \__|$$ /      $$$$$$$$ |        \___$$\ $$  ____/   \___$$\ $$  __$$\
*     $$ |$$ |      $$ |$$ |   $$ |  $$ |$$ |      $$ |      $$   ____|      $$\   $$ |$$ |      $$\   $$ |$$ /  $$ |
*     $$ |$$ |      $$ |$$ |   \$$$$$$  |$$ |      \$$$$$$$\ \$$$$$$$\       \$$$$$$  |$$$$$$$$\ \$$$$$$  | $$$$$$  |
*     \__|\__|      \__|\__|    \______/ \__|       \_______| \_______|       \______/ \________| \______/  \______/
*
*  =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*
*  Lead Programmers: Eric Bernard, Michael Barba
*  Written in 2018 for FIRST PowerUp!
*
*  Thanks to all the teams who helped us
*  out via email and through ChiefDelphi!
*/

#include <string>
#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <TimedRobot.h>
#include "CommandBase.h"
#include "Commands/TeleopDefault.h"
#include "Commands/Auto/Default.h"
#include "Commands/Auto/PrioritizeSwitchLeft.h"
#include "Commands/Auto/PrioritizeScaleLeft.h"
#include "Commands/Auto/DeferScaleRight.h"
#include "Commands/Auto/DeferScaleRightNoSwitch.h"
#include <iostream>
#include <opencv2/core/core.hpp>


using namespace frc;
using namespace std;

class Robot : public TimedRobot {
private:
	SendableChooser<int> PriorityChooser;

	Command * Teleop = new TeleopDefault();
	Command * DeferScale, *DeferScaleNoSwitch, * AutoLeftSwitch, * AutoLeftScale, * Default;

public:
	void RobotInit() override {
        CommandBase::Init();
		CommandBase::drivetrain->Calibrate();
		CommandBase::elevator->SetEncoder();

		AutoLeftSwitch = new AutoPrioritizeSwitchLeft();
		AutoLeftScale = new AutoPrioritizeScaleLeft();
		Default = new AutoDefault();
		DeferScale = new DeferScaleRight();
		DeferScaleNoSwitch = new DeferScaleRightNoSwitch();
	}

	void DisabledInit() override {
        Scheduler::GetInstance()->ResetAll();
        Scheduler::GetInstance()->RemoveAll();

		PriorityChooser.AddDefault("SCALE", 1);
		PriorityChooser.AddObject("SWITCH", 0);
		PriorityChooser.AddObject("DEFAULT", 2);
		PriorityChooser.AddObject("DEFER SCALE", 3);
		PriorityChooser.AddObject("DEFER SCALE NS", 4);

		CommandBase::drivetrain->ResetGyro();
		CommandBase::drivetrain->SetRefAngle(CommandBase::drivetrain->GetGyro());

		SmartDashboard::PutData("Auto Priority", &PriorityChooser);
		// Place a bunch of text displays for use or whatever //
		SmartDashboard::PutNumber("TIME LEFT", DriverStation::GetInstance().GetMatchTime());
		SmartDashboard::PutNumber("VOLTAGE", DriverStation::GetInstance().GetBatteryVoltage());
		std::string matchType;
		matchType = to_string(DriverStation::GetInstance().GetMatchType());
		SmartDashboard::PutString("MATCH INFORMATION", /*matchType*/ + "Playoff " + to_string(DriverStation::GetInstance().GetMatchNumber()));

        SmartDashboard::PutNumber("GYRO", 0);

		SmartDashboard::PutBoolean("COMPRESSOR", true);

		CommandBase::cubegrabber->Stop();
	}

	void DisabledPeriodic() override {
		SmartDashboard::PutNumber("GYRO", CommandBase::drivetrain->GetGyro());
		SmartDashboard::PutNumber("ELEVATOR ENCODER", CommandBase::elevator->GetEncoder());
	}

	void AutonomousInit() override {

		Scheduler::GetInstance()->ResetAll();
		Scheduler::GetInstance()->RemoveAll();

		CommandBase::Field->SetInformation();
		CommandBase::drivetrain->ResetGyro();

		int Priority = PriorityChooser.GetSelected();
		std::cout << "[Robot.cpp] Priority: " << Priority << std::endl;

		switch (Priority) {
			default: {
				std::cout << "[Auto] LEFT AUTO ERROR" << std::endl;
				CommandBase::drivetrain->KillDrive();
				return;
			}
			case 0: {
				std::cout << "[Auto] Starting CENTER SWITCH AUTO" << std::endl;
				AutoLeftSwitch->Start();
				return;
			}
			case 1: {
				std::cout << "[Auto] Starting LEFT SCALE AUTO" << std::endl;
				AutoLeftScale->Start();
				return;
			}
			case 2: {
				std::cout << "[Auto] Starting DEFAULT AUTO" << std::endl;
				Default->Start();
				return;
			}
			case 3: {
				std::cout << "[Auto] Starting LEFT SCALE DEFERMENT AUTO" << std::endl;
				DeferScale->Start();
				return;
			}
			case 4: {
				std::cout << "[Auto] Starting LEFT SCALE DEFERMENT AUTO WITH NO SWITCH" << std::endl;
				DeferScaleNoSwitch->Start();
				return;
			}
		}
	}

	void AutonomousPeriodic() override {
		SmartDashboard::PutNumber("GYRO", CommandBase::drivetrain->GetGyro());
		SmartDashboard::PutNumber("VOLTAGE", DriverStation::GetInstance().GetBatteryVoltage());
		SmartDashboard::PutNumber("ELEVATOR ENCODER", CommandBase::elevator->GetEncoder());

		Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
		Teleop->Start();
	}

	void TeleopPeriodic() override {
		SmartDashboard::PutNumber("VOLTAGE", DriverStation::GetInstance().GetBatteryVoltage());

		Scheduler::GetInstance()->Run();
	}

	void TestInit() override {
		CommandBase::drivetrain->KillDrive();
		return;
	}

	void TestPeriodic() override {
		CommandBase::drivetrain->KillDrive();
		return;
	}

};

START_ROBOT_CLASS(Robot);
