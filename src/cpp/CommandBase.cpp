#include "CommandBase.h"
#include <WPILib.h>
#include "Subsystems/DriveTrain.h"

using namespace frc;

DriveTrain * CommandBase::drivetrain = nullptr;
OI* CommandBase::controls = nullptr;
Elevator* CommandBase::elevator = nullptr;
FieldInfo* CommandBase::Field = nullptr;
CubeGrabber* CommandBase::cubegrabber = nullptr;

CommandBase::CommandBase(char const *name): Command(name) {}
CommandBase::CommandBase(): Command() {}

void CommandBase::Init() {
	drivetrain = new DriveTrain();
	controls = new OI();
	elevator = new Elevator();
	Field = new FieldInfo();
	cubegrabber = new CubeGrabber();
}
