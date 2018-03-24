# Changelog

This file replaces the old "how to set up your system" page that wasn't useful or completely accurate. Thanks, Eric. `-.-`

## March 24, 2018
**REV 2 : Updated at 7:35am @ the hotel**  
*CHANGES SINCE `REV 1` HAVE NOT BEEN TESTED!*
### Changes / Additions
+ *None as of yet*
### Removals
+ `RightSideQuadrature` and other encoder information for the right half of the drive train, since we need it for the elevator.

## March 23, 2018
**REV 1 : Updated at 9:01pm @ Bryant University**  
*THESE CHANGES HAVE NOT BEEN TESTED YET!*

### Changes / Additions
+ Deferment Autos
	+ Used for when the bot starting in the right position  has a consistent right-side auto. 
	+ Two autonomous modes: `DeferScaleRight` and `DefereScaleRightNoSwitch`
	+ Both autos examine the field locations at initialization. If the scale is on the left, the auto runs the default left-scale auto. If the scale is on the right, the auto examines which orientation the switch is in. If on the left, the auto will place the cube in the switch. If on the right, `DeferScaleRight` will attempt to place the cube in the right side, while `DeferScaleRightNoSwitch` will not.
+ New Shuffleboard Stuff
	+ `MATCH INFO`
		+ Shows `MatchType` and `MatchNumber` from the DriverStation
		+ Mostly for when examining logs and match performance, a visual cue as to which match the bot was on is recrded
	+ `TIME LEFT`
		+ Displays the approximate time left in the match (straight from `DriveTrain::GetInstance().GetMatchTime()`).
		+ May use this number in the future to toggle a bool-box on the dashboard to indicate time to climb.
	+ Renamed `Gyro` to `GYRO` to match other field-information case scheme.
+ Made `Elevator::GoToPosition()` *(hopefully)* scale speeds to locations other than the very top of the elevator - useful for switch auto.
+ Made `drivetrain->SetEncoder()` perform the while loop to reset the encoders, rather than have every use of the function wrapped in a while loop.
+ Added new motor to `Elevator`
	+ Renamed `Motor` to `MotorA` - added `MotorB`
	+ Removed `TRAYCAN` macro and added `LIFTCAN2` macro to RobotMap.h
+ Fixed a mistake in `FieldInfo` regarding local `int`s in the initialize function.

### Removals
+ `Error`, `StartingPositionChooser` and CommandButtons from Shuffleboard
	+ Also removed corresponding Commands from Robot.cpp but not from the project (just in case)
+ Unused headers from Robot.cpp
+ Lots of commented-out code that will not be used
+ Removed lots of unnecessary `SmartDashboard::Put` calls