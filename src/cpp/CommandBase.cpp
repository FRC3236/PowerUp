#include "CommandBase.h"
#include <WPILib.h>
#include "Subsystems/DriveTrain.h"

using namespace frc;

DriveTrain * CommandBase::drivetrain = NULL;
OI* CommandBase::controls = NULL;

CommandBase::CommandBase(char const *name): Command(name) {}
CommandBase::CommandBase(): Command() {}

void CommandBase::Init() {
	drivetrain = new DriveTrain();
	controls = new OI();
}
