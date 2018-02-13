//
// Created by robotics on 2/13/2018.
//

#include "ReleaseCube.h"

ReleaseCube::ReleaseCube() {
	Requires(cubegrabber);
}

void ReleaseCube::Initialize() {
	cubegrabber->Stop();
}

void ReleaseCube::Execute() {
	cubegrabber->Extend();
}

void ReleaseCube::Interrupted() {
	cubegrabber->Stop();
}

void ReleaseCube::End() {
	//
}

bool ReleaseCube::IsFinished() {
	return true;
}