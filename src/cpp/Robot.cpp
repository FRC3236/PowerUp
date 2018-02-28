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
	//SendableChooser<Command*>AutonomousChooser;
	//SendableChooser<Command*> TeleopChooser;
	SendableChooser<int> StartingPositionChooser;
	SendableChooser<int> PriorityChooser;
	//unique_ptr<Command> AutoMode;
	//unique_ptr<Command> TeleMode;

	Command * Teleop = new TeleopDefault();
	Command * DashResetGyro, * DashResetEncoders, * AutoLeftSwitch, * AutoLeftScale, * Default; //, AutoLeftScale, AutoCenterSwitch, AutoCenterScale, AutoRightSwitch, AutoRightScale, AutoDefault;

	/*static void VisionThread() {
		cs::VideoSource * source = new cs::VideoSource();
		cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
		camera.SetBrightness(20);
		if (camera.IsConnected()) {
			camera.SetResolution(640,480);
			camera.SetFPS(60);
			cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
			cs::CvSource outputStreamStd = CameraServer::GetInstance()->PutVideo("Color", 640, 480);
			cv::Mat source;
			cv::Mat output;
			while (true) {
				cvSink.GrabFrame(source);
				cvtColor(source, output, cv::COLOR_BGR2RGB);
				outputStreamStd.PutFrame(output);
			}
		}
	}*/

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
		StartingPositionChooser.AddObject("CENTER", 1);
		StartingPositionChooser.AddObject("RIGHT", 2);
		StartingPositionChooser.AddObject("EMERGENCY DEFAULT", 3);

		PriorityChooser.AddDefault("SWITCH", 0);
		PriorityChooser.AddObject("SCALE", 1);

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
	}

	void AutonomousInit() override {

		Scheduler::GetInstance()->ResetAll();
		Scheduler::GetInstance()->RemoveAll();

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

		CommandBase::Field->SetInformation();

		int StartPos = StartingPositionChooser.GetSelected();
		int Priority = PriorityChooser.GetSelected();
		std::cout << "[Robot.cpp] Start Pos: " << StartPos << std::endl;
		std::cout << "[Robot.cpp] Priority: " << Priority << std::endl;

		/*switch (StartPos) {
			default: {
				CommandBase::drivetrain->KillDrive();
			}
			case 0: {
				switch (Priority) {
					default: {
						std::cout << "[Auto] LEFT AUTO ERROR" << std::endl;
						CommandBase::drivetrain->KillDrive();
						break;
					}
					case 0: {
						std::cout << "[Auto] Starting LEFT SWITCH AUTO" << std::endl;
						AutoLeftSwitch->Start();
						break;
					}
					case 1: {
						std::cout << "[Auto] Starting LEFT SCALE AUTO" << std::endl;
						AutoLeftScale->Start();
						break;
					}
				}
			}
			case 1: {
				switch (Priority) {
					default: {
						CommandBase::drivetrain->KillDrive();
						break;
					}
					case 0: {
						break;
					}
					case 1: {
						break;
					}
				}
			}
			case 2: {
				switch (Priority) {
					default: {
						CommandBase::drivetrain->KillDrive();
					}
					case 0: {
						break;
					}
					case 1: {
						break;
					}
				}
			}
			case 3: {
				Default->Start();
				break;
			}
		}*/
		Default->Start();
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
