//
// Created by robotics on 2/13/2018.
//

#include "GrabCube.h"

GrabCube::GrabCube() {
	Requires(cubegrabber);
}

void GrabCube::Initialize() {
	cubegrabber->Stop();
}

void GrabCube::Execute() {
	cubegrabber->Retract();
}

void GrabCube::Interrupted() {
	cubegrabber->Stop();
}

void GrabCube::End() {
	//
}

bool GrabCube::IsFinished() {
	return true;
}