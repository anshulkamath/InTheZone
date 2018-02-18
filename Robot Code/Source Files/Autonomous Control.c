// Stop recursive includes
#ifndef AUTONOMOUS_CONTROL_H
#define AUTONOMOUS_CONTROL_H

#include "Debug.c"

// Autonomous Tasks

// Drive PID
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
		range = 75;
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
		display( (int)P , (int)I , (int)D, error, lDrivePwr, driveTarget, debugval, rDrivePwr);

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

		motor[leftB] = motor[leftF] = lDrivePwr*.95;

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
		range = 50;
	}

	int target = 0;
	int error = 0;
	int lastError = 0;
	int debugval = 0;
	int startangle = GyroGetAngle();

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

		motor[rightB] = motor[rightF] = rDrivePwr*.95;

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
		float P = kp * (SensorValue[liftPot] + 60 - SensorValue[liftPot2]);
		motor[lLift] += P + 13;
		motor[rLift] -= P -.25*60;
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
		motor[lLift] = lLiftPwr ;
		motor[rLift] = rLiftPwr ;

		//display( (int)P , (int)I , (int)D ,error,lLiftPwr,liftTarget,SensorValue(rLiftPot));
		sleep (100);
	}
}

// Mobile Goal Control
task mGoalAuton()
{
  // mGoalIsUp is initialized to true
  if (moGoIsUp) // If it is up, run it down
  {
    motor[moGo] = 100;
  	while(SensorValue[moGoPot] > MOGO_DOWN) {}
  	motor[moGo] = 0;
    moGoIsUp = false;
  }
  else
  {
    motor[moGo] = -100;
  	while(SensorValue[moGoPot] < MOGO_UP - 300) {}
  	motor[moGo] = 0;
  	moGoIsUp = true;

    sleep(200);
    intakeCone(0);
    cones = 1;
  }
}

// Auton Control functions

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

// Gyro Functions
void right(int len)
{
	int startangle = GyroGetAngle();
	isOpposite = true;
	driveTarget = -len;
	startTask(lDrivePID);
	startTask(rDrivePID);
	while((GyroGetAngle() - startangle) > ((- len) + turnRange))
	{
		//writeDebugStreamLine("%f",GyroAngleAbsGet());
	}
	sleep(500);
	stopTask(lDrivePID);
	stopTask(rDrivePID);
	motor[rightB] = motor[rightF] = motor[leftB] = motor[leftF] = 0;
}

void left(int len)
{
	int startangle = GyroGetAngle();
	isOpposite = true;
	driveTarget = len;
	startTask(lDrivePID);
	startTask(rDrivePID);
	while((GyroGetAngle() - startangle) < (len - turnRange));
	sleep(500);
	stopTask(lDrivePID);
	stopTask(rDrivePID);
	motor[rightB] = motor[rightF] = motor[leftB] = motor[leftF] = 0;
}

void turnTo(int angle)
{
	const int range = 5;
	const int pwr = 30;
	if(angle < GyroGetAngle())
	{
		motor[leftB] = motor[leftF] = pwr;
		motor[rightB] = motor[rightF] = -pwr;
	}
	else
	{
		motor[leftB] = motor[leftF] = -pwr;
		motor[rightB] = motor[rightF] = pwr;
	}
	while(abs(GyroGetAngle() - angle) > range){}
}

#endif
