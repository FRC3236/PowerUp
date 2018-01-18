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
*  Lead Programmers: Eric Bernard, Michael Barba, and Tyler Mello
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
#include "Commands/AutoDefault.h"
#include "Commands/ResetGyro.h"
#include "Commands/DoNothing.h"
#include "Commands/AutoPrioritizeSwitchLeft.h"
#include "Commands/AutoPrioritizeSwitchRight.h"
#include <iostream>


using namespace frc;
using namespace std;

class Robot : public TimedRobot {
private:
	SendableChooser<Command*>AutonomousChooser;
	SendableChooser<Command*> TeleopChooser;
	unique_ptr<Command> AutoMode;
	unique_ptr<Command> TeleMode;
	Command * resetGyro;

public:
	void RobotInit() override {
        CommandBase::Init();
		resetGyro = new ResetGyro();
		CommandBase::drivetrain->CalibrateGyro();
	}

	void DisabledInit() override {
        Scheduler::GetInstance()->ResetAll();
        Scheduler::GetInstance()->RemoveAll();

		TeleopChooser.AddDefault("Default Driver", new TeleopDefault());
		AutonomousChooser.AddDefault("Default Auto", new AutoDefault());

		AutonomousChooser.AddObject("[LEFT] Switch", new AutoPrioritizeSwitchLeft());
		AutonomousChooser.AddObject("[RIGHT] Switch", new AutoPrioritizeSwitchRight());

		CommandBase::drivetrain->SetRefAngle(CommandBase::drivetrain->GetGyro());

		SmartDashboard::PutData("Teleop Modes", &TeleopChooser);
		SmartDashboard::PutData("Auto Modes", &AutonomousChooser);

		SmartDashboard::PutData("Reset Gyro", new ResetGyro());

        SmartDashboard::PutNumber("Gyro", 0);
		SmartDashboard::PutNumber("Error", 0);

		SmartDashboard::PutString("Field Layout", "Unknown");
	}

	void DisabledPeriodic() override {
		SmartDashboard::PutNumber("Gyro", CommandBase::drivetrain->GetGyro());
		if (Scheduler::GetInstance() != nullptr) {
			Scheduler::GetInstance()->Run();
		}

	}
	void AutonomousInit() override {
		AutoMode.release();
		AutoMode.reset(AutonomousChooser.GetSelected());
		if (AutoMode != nullptr) {
			AutoMode->Start();
		}
	}

	void AutonomousPeriodic() override {
		Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
		TeleMode.release();
		TeleMode.reset(TeleopChooser.GetSelected());
		if (TeleMode != nullptr) {
			TeleMode->Start();
		}
	}

	void TeleopPeriodic() override {
		Scheduler::GetInstance()->Run();
	}

	void TestPeriodic() override {

	}

};

START_ROBOT_CLASS(Robot);
