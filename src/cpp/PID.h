//
// Created by robotics on 1/17/2018.
//

#ifndef NEWPOWERUP_PID_H
#define NEWPOWERUP_PID_H


class PID {
public:
	double PFac, IFac, DFac, P, I, D, preverror, point;
	PID(double);

	void Update(double);
	double Point();
	void Point(double);

	double GetPI();
	void Reset(double);
};


#endif //NEWPOWERUP_PID_H
