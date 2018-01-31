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
#include "Commands/Auto/Default.h"
#include "Commands/DoNothing.h"
#include "Commands/ResetGyro.h"
#include "Commands/Auto/PrioritizeSwitchLeft.h"
#include "Commands/Auto/PrioritizeSwitchRight.h"
#include "Commands/Auto/PrioritizeScaleLeft.h"
#include "Commands/Auto/PrioritizeScaleRight.h"
#include <iostream>


using namespace frc;
using namespace std;

class Robot : public TimedRobot {
private:
	SendableChooser<Command*>AutonomousChooser;
	SendableChooser<Command*> TeleopChooser;
	SendableChooser<int> StartingPositionChooser;
	SendableChooser<int> PriorityChooser;
	unique_ptr<Command> AutoMode;
	unique_ptr<Command> TeleMode;

	Command * Teleop = new TeleopDefault();
	Command * DashResetGyro;
	Command * AutoLeftSwitch; //, AutoLeftScale, AutoCenterSwitch, AutoCenterScale, AutoRightSwitch, AutoRightScale, AutoDefault;

public:
	void RobotInit() override {
        CommandBase::Init();
		CommandBase::drivetrain->Calibrate();

		AutoLeftSwitch = new AutoPrioritizeSwitchLeft();
		DashResetGyro = new ResetGyro();
	}

	void DisabledInit() override {
        Scheduler::GetInstance()->ResetAll();
        Scheduler::GetInstance()->RemoveAll();

		StartingPositionChooser.AddDefault("LEFT", 0);
		StartingPositionChooser.AddObject("CENTER", 1);
		StartingPositionChooser.AddObject("RIGHT", 2);

		PriorityChooser.AddDefault("SWITCH", 0);
		PriorityChooser.AddObject("SCALE", 1);

		CommandBase::drivetrain->ResetGyro();
		CommandBase::drivetrain->SetRefAngle(CommandBase::drivetrain->GetGyro());

		SmartDashboard::PutData("Starting Position", &StartingPositionChooser);
		SmartDashboard::PutData("Auto Priority", &PriorityChooser);

		// Place a bunch of text displays for use or whatever //
		SmartDashboard::PutString("Text Display 1", "");
		SmartDashboard::PutString("Text Display 2", "");
		SmartDashboard::PutString("Text Display 3", "");

        SmartDashboard::PutNumber("Gyro", 0);
		SmartDashboard::PutNumber("Error", 0);

		SmartDashboard::PutString("Field Layout", "Unknown");
		SmartDashboard::PutData("Reset Gyro", DashResetGyro);
	}

	void DisabledPeriodic() override {
		SmartDashboard::PutNumber("Gyro", CommandBase::drivetrain->GetGyro());
	}

	void AutonomousInit() override {

		/*
		 * StartPos Cases:
		 * 		0: Left
		 * 		1: Center
		 * 		2: Right
		 *
		 * Priority Cases:
		 * 		0: Switch
		 * 		1: Scale
		 */

		int StartPos = StartingPositionChooser.GetSelected();
		int Priority = PriorityChooser.GetSelected();

		switch (StartPos) {
			default: {
				CommandBase::drivetrain->KillDrive();
			}
			case 0: {
				switch (Priority) {
					default: {
						CommandBase::drivetrain->KillDrive();
					}
					case 0: {
						AutoLeftSwitch->Start();
					}
					case 1: {
						// AutoLeftScale()->Start(); //
					}
				}
			}
			case 1: {
				switch (Priority) {
					default: {
						CommandBase::drivetrain->KillDrive();
					}
					case 0: {

					}
					case 1: {

					}
				}
			}
			case 2: {
				switch (Priority) {
					default: {
						CommandBase::drivetrain->KillDrive();
					}
					case 0: {

					}
					case 1: {

					}
				}
			}
		}
	}

	void AutonomousPeriodic() override {
		Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
		/*TeleMode.release();
		TeleMode.reset(TeleopChooser.GetSelected());
		if (TeleMode != nullptr) {
			TeleMode->Start();
		}*/
		Teleop->Start();
	}

	void TeleopPeriodic() override {
		Scheduler::GetInstance()->Run();
	}

	void TestInit() override {

	}

	void TestPeriodic() override {
	}

};

START_ROBOT_CLASS(Robot);
