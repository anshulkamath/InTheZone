#ifndef AUTONCONTROL_H
#define AUTONCONTROL_H
#include "GyroPid.c"

//Power right drive motors
void driveR(int val)
{
	if(abs(val) > 100)
		val = sgn(val) * 100;

	motor[rightB] = motor[rightF] = val;
}

void driveL(int val)
{
	if(abs(val) > 100)
		val = sgn(val) * 100;

	motor[leftB] = motor[leftF] = val;
}

// Intake
task intakeCone()
{
  motor[intake] = 100;
  sleep(300);
  motor[intake] = 20;
}

// Turn Functions
void turnBrake(bool clockwise)
{
  if (clockwise)
  {
    driveR(10);
    driveL(-10);
  }
  else
  {
    driveR(-10);
    driveL(10);
  }

    sleep (150);

    driveR(0);
    driveL(0);
}

void turnPD(int target, bool mogo1 = false, bool change = true)
{

  float kp = .03;
  float kd = .07;
  if (abs(target) - 450 < 150 && !mogo1) // normal
  {
  	kp = .09;
  	kd = .1;
  }
  else if (abs(target) - 450 < 150 && mogo1) // mogo
  {
  	kp = .09;
  	kd = .1;
  }
  else if (abs(target) - 900 < 150 && mogo1) // mogo
  {
  	kp = .07;
  	kd = .1;
  }
  else if (abs(target) - 900 < 150 && !mogo1) // mogo
  {
  	kp = .06;
  	kd = .07;
  }

  int P = 0;
  int D = 0;

  int error, lastError, pwr;

  bool PDOn = true;
	int begin = SensorValue[gyroscope];
  while (abs(SensorValue(gyroscope) ) < abs(target + begin))
  {
    error = target + begin - SensorValue(gyroscope);
    P = error * kp;
    D = (error - lastError) * kd;

    pwr = P - D;

    if (pwr > 100) pwr = 100;
    if (pwr < -100) pwr = -100;

    if((D == 0 && abs(error) < 300) &&  change || !PDOn)
		{
			pwr = sgn(target) * 40;
			PDOn = false;
		}else if(!change && D==0)
		{
			pwr = sgn(target) * 20;
			PDOn = false;
		}

    driveL(-pwr);
    driveR(pwr);

    lastError = error;
    sleep (50);
  }
  if (target < 0) turnBrake (true);
  else turnBrake (false);
}

void turnTo(int value, bool swingTurn = false)
{
	int error = value - SensorValue(gyroscope);

	// If it is too far away from the target, turn to the target (should not have to be used)
	if (abs(error) > 200)
	{
		turnPD(value - SensorValue(gyroscope) - sgn(error) * 200);
		if (error > 0)
			turnBrake(false);
		else
			turnBrake(true);
	}

	error = value - SensorValue(gyroscope);

	// When it is close to the target, turn to to the target
  if (error > 0)
  {
    driveL(-TURN_PWR);
    driveR(TURN_PWR);
    while (SensorValue(gyroscope) < value - 20) {}
    turnBrake(false);
  }
	else if (error < 0)
  {
    driveL(TURN_PWR);
    driveR(-TURN_PWR);
    while (SensorValue(gyroscope) > value +20) {}
    turnBrake(true);
  }

	error = value - SensorValue(gyroscope);

	// This is very time expensive
	if (swingTurn)
	{
		if (error > 0)
		{
			driveR(25);
			while (SensorValue(gyroscope) > value) {}
			driveR(0);
		}
		else if (error < 0)
		{
			driveL(25);
			while (SensorValue(gyroscope) < value) {}
			driveL(0);
		}
	}
}

task lDrivePID()
{
	SensorValue(lDriveQuad) = 0;
	clearTimer(T2);

	float P, I , D;
	P=0;
	I=0;
	D=0;

	float kp;
	float ki;
	float kd;
	int range;
	float tempy = .25;
	if(!isOpposite)
	{
		kp = .7;
		ki = 0.15;
		kd = 1.25;
		range = 100;
	}
	else
	{
		kp = .35;
		ki = 0.03;//.1;
		kd = .4;
		range = 25;
	}

	int target = 0;
	float error = 0;
	int lastError = 0;
	const float gyrostart = SensorValue[gyroscope];
	int debugval = 0;


	while (true)
	{
		float g = SensorValue[gyroscope];
		//if(isOpposite)
		//display( (int)P , (int)I , (int)D ,error,lDrivePwr,driveTarget,g);
		//display( (int)P , (int)I , (int)D, error, lDrivePwr, driveTarget, debugval, rDrivePwr);

		target = driveTarget;

		if(!isOpposite)
		{
			error = target - SensorValue(lDriveQuad);
			debugval = SensorValue(lDriveQuad);
		}
		else
		{
			error = target - (g - gyrostart);
			error *=-1;
			debugval = g - gyrostart;
		}

		P = error * kp;
		D = (error - lastError) * kd;

		if (error > -range && error < range)
			I += error * ki;
		else
			I=0;

		lastError = error;
		lDrivePwr = P + D;
		lDrivePwr += I;

		if(lDrivePwr > 100)
			lDrivePwr = 100;
		if(lDrivePwr < -100)
			lDrivePwr = -100;

		if(time1[T2] < 200){
			if(lDrivePwr > 50)
				lDrivePwr = 50;
			if(lDrivePwr < -50)
				lDrivePwr = -50;
		}

		motor[leftB] = motor[leftF] = lDrivePwr * tempy;
		if(tempy < 1) tempy += .05;

		sleep (50);
	}
}

task rDrivePID()
{
	SensorValue(rDriveQuad) = 0;
	clearTimer(T3);

	float P, I, D;
	P = 0;
	I = 0;
	D = 0;

	float kp;
	float ki;
	float kd;
	int range;

	if(!isOpposite)
	{
		kp = .9;//.6;
		ki = 0;//0.02;
		kd = .1;//.06;
		range = 500;
	}
	else
	{
		kp = .5;
		ki = 0.1;
		kd = 1.5;
		range = 30;
	}

	int target = 0;
	int error = 0;
	int lastError = 0;
	int debugval = 0;
	int startangle = SensorValue[gyroscope];
	float tempy = .25;
	while (true)
	{
		//if(!isOpposite)
		//display( (inht)P , (int)I , (int)D ,error,rDrivePwr,target,debugval , lDrivePwr);
		//display( (int)P , (int)I , (int)D ,error,rDrivePwr,target,debugval);

		if(!isOpposite)
		{
			error = startangle - SensorValue[gyroscope];
			target = startangle;
			debugval = SensorValue[gyroscope];
		}
		else
		{
			error = - (SensorValue(lDriveQuad) + SensorValue(rDriveQuad));
			target = -SensorValue(lDriveQuad);
			debugval = SensorValue(rDriveQuad);
		}

		//if(isOpposite)
		//    error*=-1;

		P = error * kp;
		if (lDrivePwr > -range && lDrivePwr < range)
			I += (error * ki);
		else
			I=0;
		D = (error - lastError) * kd;

		lastError = error;

		if(!isOpposite)
			rDrivePwr = lDrivePwr + P + I + D;
		else
			rDrivePwr = -1 * (lDrivePwr) + P + I + D;

		if(rDrivePwr > 100)
			rDrivePwr = 100;
		if(rDrivePwr < -100)
			rDrivePwr = -100;

		if(time1[T3] < 200){
			if(rDrivePwr > 55)
				rDrivePwr = 55;
			if(rDrivePwr < -55)
				rDrivePwr = -55;
		}

		motor[rightB] = motor[rightF] = rDrivePwr * tempy;
		if(tempy < 1) tempy += .05;
		//display( (int)P , (int)I , (int)D ,error,rDrivePwr,target,SensorValue(rDriveQuad));
		//writeDebugStreamLine("%d , %d", rDrivePwr, lDrivePwr);

		sleep (50);
	}
}

// Drive Functions
void forward(int len)
{
	isOpposite = false;
	driveTarget = len;
	startTask(lDrivePID);
	startTask(rDrivePID);
	while(SensorValue(lDriveQuad) < (len - driveRange));
	sleep(500);
	stopTask(lDrivePID);
	stopTask(rDrivePID);
	motor[rightB] = motor[rightF] = motor[leftB] = motor[leftF] = 0;
}

void forwardNonPID(int len)
{
	motor[rightB] = motor[rightF] = motor[leftB] = motor[leftF] = 100;
	int temp = SensorValue[lDriveQuad];
	//motor[moGo] = -40;
	while(SensorValue(lDriveQuad) -temp < (len - driveRange));
	motor[rightB] = motor[rightF] = motor[leftB] = motor[leftF] = 0;
}

void forwardNonPID(int len, int power)
{
	motor[rightB] = motor[rightF] = motor[leftB] = motor[leftF] = power;
	int temp = SensorValue[lDriveQuad];
	//motor[moGo] = -40;
	while(SensorValue(lDriveQuad) -temp < (len - driveRange));
	motor[rightB] = motor[rightF] = motor[leftB] = motor[leftF] = 0;
}

void backward(int len)
{
	isOpposite = false;
	driveTarget = -len;
	startTask(lDrivePID);
	startTask(rDrivePID);
	while(SensorValue(lDriveQuad) > (-len + driveRange));
	sleep(500);
	stopTask(lDrivePID);
	stopTask(rDrivePID);
	motor[rightB] = motor[rightF] = motor[leftB] = motor[leftF] = 0;
}

// Mobile Goal
task mGoalAuton()
{
	if (moGoIsUp)
	{
		while (SensorValue(moGoPot) > MOGO_DOWN + 300)
			motor[moGo] = 100;
		while (SensorValue(moGoPot) > MOGO_DOWN)
			motor[moGo] = 40;

		motor[moGo] = 20;

		moGoIsUp = false;
	}
	else
	{
		while (SensorValue(moGoPot) < MOGO_UP - 300)
			motor[moGo] = -100;
		while (SensorValue(moGoPot) < MOGO_UP - 150)
			motor[moGo] = -40;

		motor[moGo] = 0;

		moGoIsUp = true;
	}
}

task moveMoGoDown()
{
	motor[moGo] = 100;

	while(SensorValue[moGoPot] > MOGO_DOWN)
	{
		motor[moGo] = 100;
	}

	motor[moGo] = 0;
  moGoIsUp = false;
}

// Vestiges
const int size1 = 10;
struct PControlStruct
{
  int SensorPort;
  int motorPorts[size1];
  int pValue[size1];
  int target;
  bool highPrecision;

};

struct Structy
{
	int power;
	float thres;
};

task lLiftPID()
{
	float P, I, D;
	// period = .8
	float kp = 0.3; //.5
	float ki = 0.075;
	float kd = 0.4;

	int error = 0;
	int lastError = 0;
	int range = 150;

	// 16.38 ticks per degree
	while (true)
	{
		error = liftTarget - SensorValue(liftPot);

		P = error * kp;
		D = (error - lastError) * kd;

		if (error > -range && error < range)
			I += error * ki;
		else
			I=0;

		lastError = error;
		lLiftPwr = P + I + D;
		motor[lLift] = lLiftPwr * 1.1;
		motor[rLift] = rLiftPwr * 1.1;

		//display( (int)P , (int)I , (int)D ,error,lLiftPwr,liftTarget,SensorValue(liftPot));
		sleep (100);
	}
}

/*int powerExtrap(Structy [] x, int size)
{
	int closest = 0;
	for(int i = 0; i<size; i++)
	{
		if(abs(nAvgBatteryLevel - x[i].power) <  abs(nAvgBatteryLevel - x[i].power))
		{
			closest = i;
		}
	}
	if(x[closest].power > nAvgBatteryLevel)
	{
		float slope = (x[closest].thres - x[closest != 0 ? closest - 1 : 0]) /(x[closest].power - x[closest > 0 ? closest - 1 : 0]);
		float b = slope * x[closest].power * -1 + x[closest].thres;
		return (int)(slope * nAvgBatteryLevel + b);
	}
	float slope = (-x[closest].thres + x[closest +1 != size ? closest + 1 : 0]) /(-x[closest].power + x[closest +1 != size ? closest + 1 : 0]);
	float b = slope * x[closest].power * -1 + x[closest].thres;
	return (int)(slope * nAvgBatteryLevel + b);
}*/

#endif
