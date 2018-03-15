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
#include "Commands/DoNothing.h"
#include "Commands/ResetGyro.h"
#include "Commands/ResetEncoders.h"
#include "Commands/Auto/PrioritizeSwitchLeft.h"
#include "Commands/Auto/PrioritizeSwitchRight.h"
#include "Commands/Auto/PrioritizeScaleLeft.h"
#include "Commands/Auto/PrioritizeScaleRight.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace frc;
using namespace std;

class Robot : public TimedRobot {
private:
	SendableChooser<int> StartingPositionChooser;
	SendableChooser<int> PriorityChooser;

	Command * Teleop = new TeleopDefault();
	Command * DashResetGyro, * DashResetEncoders, * AutoLeftSwitch, * AutoLeftScale, * Default;

public:
	void RobotInit() override {
        CommandBase::Init();
		CommandBase::drivetrain->Calibrate();
		CommandBase::elevator->SetEncoder();

		AutoLeftSwitch = new AutoPrioritizeSwitchLeft();
		AutoLeftScale = new AutoPrioritizeScaleLeft();
		Default = new AutoDefault();
		DashResetGyro = new ResetGyro();
		DashResetEncoders = new ResetEncoders();
	}

	void DisabledInit() override {
        Scheduler::GetInstance()->ResetAll();
        Scheduler::GetInstance()->RemoveAll();

		StartingPositionChooser.AddDefault("LEFT", 0);
		StartingPositionChooser.AddObject("CENTER [DONT CHOOSE ME]", 1);
		StartingPositionChooser.AddObject("RIGHT [DONT CHOOSE ME]", 2);
		StartingPositionChooser.AddObject("EMERGENCY DEFAULT", 3);

		PriorityChooser.AddDefault("SWITCH", 0);
		PriorityChooser.AddObject("SCALE", 1);
		PriorityChooser.AddObject("DEFAULT", 2);
		CommandBase::drivetrain->ResetGyro();
		CommandBase::drivetrain->SetRefAngle(CommandBase::drivetrain->GetGyro());

		SmartDashboard::PutData("Starting Position", &StartingPositionChooser);
		SmartDashboard::PutData("Auto Priority", &PriorityChooser);
		// Place a bunch of text displays for use or whatever //

        SmartDashboard::PutNumber("Gyro", 0);
		SmartDashboard::PutNumber("Error", 0);

		SmartDashboard::PutString("Field Layout", "Unknown");
		SmartDashboard::PutData("Reset Gyro", DashResetGyro);
		SmartDashboard::PutData("Reset Encoders", DashResetEncoders);

		SmartDashboard::PutBoolean("COMPRESSOR", true);

		CommandBase::cubegrabber->Stop();
	}

	void DisabledPeriodic() override {
		SmartDashboard::PutNumber("Gyro", CommandBase::drivetrain->GetGyro());
		SmartDashboard::PutNumber("ELEVATOR ENCODER", CommandBase::elevator->GetEncoder());
	}

	void AutonomousInit() override {

		Scheduler::GetInstance()->ResetAll();
		Scheduler::GetInstance()->RemoveAll();

		/*
		 * StartPos Cases:
		 * 		0: Left
		 * 		1: Center
		 * 		2: Right
		 * 		3: Emergency Default
		 *
		 * Priority Cases:
		 * 		0: Switch
		 * 		1: Scale
		 */

		CommandBase::Field->SetInformation();
		CommandBase::drivetrain->ResetGyro();

		int StartPos = StartingPositionChooser.GetSelected();
		int Priority = PriorityChooser.GetSelected();
		std::cout << "[Robot.cpp] Start Pos: " << StartPos << std::endl;
		std::cout << "[Robot.cpp] Priority: " << Priority << std::endl;

		switch (Priority) {
			default: {
				std::cout << "[Auto] LEFT AUTO ERROR" << std::endl;
				CommandBase::drivetrain->KillDrive();
				return;
			}
			case 0: {
				std::cout << "[Auto] Starting LEFT SWITCH AUTO" << std::endl;
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
		}
	}

	void AutonomousPeriodic() override {
		Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
		Teleop->Start();
	}

	void TeleopPeriodic() override {
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
