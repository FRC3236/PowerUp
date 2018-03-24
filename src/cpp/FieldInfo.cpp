//
// Created by robotics on 2/1/2018.
// 0 IS LEFT, 1 IS RIGHT
//

#include "FieldInfo.h"
#include "WPILib.h"
using namespace std;

FieldInfo::FieldInfo() {
	Switch = 0;
	Scale = 0;
	FieldTime = new Timer();
}

void FieldInfo::SetInformation(int sw, int scale) {
	this->Switch = sw;
	this->Scale = scale;
}

void FieldInfo::SetInformation() {
	string INFOS = frc::DriverStation::GetInstance().GetGameSpecificMessage();
	string RIGHT = "R";
	this->Switch = (INFOS[0] == RIGHT[0]);
	this->Scale = (INFOS[1] == RIGHT[0]);
}

int FieldInfo::GetSwitch() {
	return this->Switch;
}

int FieldInfo::GetScale() {
	return this->Scale;
}

std::pair<int, int> FieldInfo::GetFieldInfo() {
	return std::make_pair(this->Switch, this->Scale);
}