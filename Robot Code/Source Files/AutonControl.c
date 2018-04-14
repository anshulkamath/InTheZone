#ifndef AUTONCONTROL_H
#define AUTONCONTROL_H
#include "GyroPid.c"

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

task moveMoGoDown()
{
	motor[moGo] = 100;
	int start1 = SensorValue[moGoPot];
	while(SensorValue[moGoPot] > MOGO_DOWN)
	{
		motor[moGo] = 100 * SensorValue[moGoPot];
	}
	motor[moGo] = 0;
}

void pControlFunction(PControlStruct control)
{
  //int currSensorValue = SensorValue[control.SensorPort];
  bool done = false;
  int rangeHigh = 20;
  int prev = 0;
  while(SensorValue[control.SensorPort] < control.target + control.highPrecision ? control.target : 0 && !done)
  {
    int cumPower = 0;

    for(int i = 0; i<size; i++)
      cumPower += control.pValue[i] * (SensorValue[control.SensorPort];

    for(int i = 0; i<size; i++)
      motor[control.motorPorts[i]] = cumPower;

    if(abs(prev - SensorValue[control.SensorPort]) < rangeHigh && abs(SensorValue[control.SensorPort] - control.target) < rangeHigh)
      done = true;

    prev = SensorValue[control.SensorPort];
  }
}

float stopThres = .75;
float end = 0;
void autoTune(int degrees)
{
  bool done = false;

  while(!done)
  {
    int i = 0;
    float off = 0;
    while(i<4)
    {
      while(GyroGetAngle() < degrees*stopThres)
      {
        motor[rightB] = motor[rightF] = -80*(GyroGetAngle() - degrees)/(degrees*.95)+10;
        motor[leftB] = motor[leftF] = 80*(GyroGetAngle() - degrees)/(degrees*.95)-10;

      }
      //display(GyroGetAngle(), stopThres*100, off, 0, 0, 0, 0, 0);
          motor[rightB] = motor[rightF] = 10;
          motor[leftB] = motor[leftF] = -10;
      off += GyroGetAngle() - degrees;
      sleep(2000);
      pre_auton();
      i++;
    }

    if(abs(off/4) < 10)
      done = true;
    else if(off > 0)
      stopThres -= abs(off/4.0)/100.0;
    else
      stopThres += abs(off/4.0)/100.0;

  }
  writeDebugStreamLine("Value: %d With Bat Of %d", stopThres, nAvgBatteryLevel);
  end = stopThres;
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




void driveL(int val)
{
	if(abs(val) > 127)
		val = 127 * val/abs(val);

	motor[leftB] = motor[leftF] = val;
}

//Power right drive motors
void driveR(int val)
{
	if(abs(val) > 127)
		val = 127 * val/abs(val);

	motor[rightB] = motor[rightF] = val;
}


void turnV3(int degrees1, int timeStopMS = 100000, bool doCorrection = false) {
	clearTimer(T4)
	const int DEGREES10 = degrees1 * 10;
	const float Kt = 0.08;
	const int GYRO_START = SensorValue[gyroscope];
	const int TARGET = (fabs(GYRO_START + DEGREES10) > 3600) ? (sgn(degrees) * (fabs(GYRO_START + DEGREES10) - 3600)) : (GYRO_START + DEGREES10);
	int dist = TARGET - SensorValue[gyroscope];
	int pwr = (int) (dist * Kt);
	while (fabs(pwr) > 5 && time1[T4] < timeStopMS) {
		dist = TARGET - SensorValue[gyroscope];
		pwr = (int) (dist * Kt);
		driveR(pwr);
		driveL(-pwr);
	}
	driveL(0);
	driveR(0);
	if (doCorrection) {
		writeDebugStreamLine("Attempting Correction");
		int dist = degrees1 - SensorValue[gyroscope];
		int b = dist;
		while (fabs(dist) > 10) {
			dist = degrees1 - SensorValue[gyroscope];
			driveR(sgn(dist) * 30);
			driveL(-sgn(dist) * 30);
			writeDebugStreamLine("Right Drive: %i", sgn(dist) * 30);
			writeDebugStreamLine("Left power %i", -sgn(dist) * 30);
		}
		driveL(sgn(b) * 10);
		driveR(-sgn(b) * 10);
	}
}

void right(int deg)
{
	turnV3(900);
}

void left(int deg)
{
	//gyroTurn((-deg + (SensorValue[gyroscope] - gyro.gyroOffset))%3600);
}
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
	const float gyrostart = GyroGetAngle();
	int debugval = 0;


	while (true)
	{
		float g = GyroGetAngle();
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
	int startangle = GyroGetAngle();
	float tempy = .25;
	while (true)
	{
		//if(!isOpposite)
		//display( (int)P , (int)I , (int)D ,error,rDrivePwr,target,debugval , lDrivePwr);
		//display( (int)P , (int)I , (int)D ,error,rDrivePwr,target,debugval);

		if(!isOpposite)
		{
			error = startangle - GyroGetAngle();
			target = startangle;
			debugval = GyroGetAngle();
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

// Lift PID (not specifically lLift)
task stabilizeLift()
{
	while(true)
	{
		float kp = .8;
		float P = kp * (SensorValue[liftPot] + 40 - SensorValue[liftPot2]);
		motor[lLift] -= P + 13;
		motor[rLift] += P -.25*60;
		sleep(10);
	}
}

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

#endif
