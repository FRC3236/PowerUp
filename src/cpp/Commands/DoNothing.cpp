//
// Created by robotics on 1/13/2018.
//

#include "DoNothing.h"

DoNothing::DoNothing() {
}

void DoNothing::Initialize() {

}

void DoNothing::Execute() {
	End();
}

void DoNothing::End() {

}

void DoNothing::Interrupted() {
	End();
}

bool DoNothing::IsFinished() {
	return true;
}