// Stop recursive includes
#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#include "Variables.c"
#include "AutonControl.c"
#include "GyroPid.c"

// Naming conventions: "matchAuton_COLOR_PTVALUE"
// NUM_CONE DOES NOT COUNT THE PRELOAD

task deploy()
{
	startTask(intakeCone);
	sleep(200); // wait for cone to get into intake
	motor[lLift] = motor[rLift] = 75;
	while(SensorValue[liftPot] < LIFT_MIN + 400);
	motor[lLift] = motor[rLift] = 10;
	startTask(moveMoGoDown);
	while(moGoIsUp);
}

// 22_Left
void auton1()
{
	writeDebugStreamLine("%d", SensorValue[gyroscope]);
	clearTimer(T3);
	startTask(barSet);

	/*
	startTask(intakeCone);
	sleep(100); // wait for cone to get into intake
	motor[lLift] = motor[rLift] = 75;
	while(SensorValue[liftPot] < LIFT_MIN + 400);
	motor[lLift] = motor[rLift] = 10;
	startTask(moveMoGoDown);
  //while(SensorValue[moGoPot] > MOGO_DOWN + 100);
	*/

	// Replaced with task... see how it works. If it doesn't just replace with above
	startTask(deploy);
	while(SensorValue[liftPot] < LIFT_MIN + 400);

  forward(1400);
  barIsUp = false;
  while(SensorValue(barPot) < BAR_DOWN - 500);

	motor[lLift] = motor[rLift] = -75;
	while(SensorValue[liftPot] > LIFT_MIN + 200);
	motor[lLift] = motor[rLift] = 10;

	// Could replace with startTask(releaseCone)
	motor[intake] = -50;
	wait10Msec(50);
	motor[intake] = 0;

  barIsUp = true;
  while(SensorValue(barPot) > BAR_UP + 100);

	motor[lLift] = motor[rLift] = 75;
	while(SensorValue[liftPot] < LIFT_MIN + 300);
	motor[lLift] = motor[rLift] = 10;

	motor[moGo] = -100;
	while(SensorValue[moGoPot] < MOGO_UP)
	{
		motor[moGo] = -100;
	}
	motor[moGo] = 0;

	writeDebugStream("%d", SensorValue[gyroscope]);
	if(abs(SensorValue[gyroscope]) > 30)
		turnTo(0);
	writeDebugStream("%d", SensorValue[gyroscope]);

	// Pick up second cone
	/*forwardNonPID(125, 45);
	barIsUp = false;
	//turnTo(0);
	wait1Msec(100);
	motor[intake] = 100;
	motor[lLift] = motor[rLift] = -75;
	while(SensorValue[liftPot] > LIFT_MIN);
	motor[lLift] = motor[rLift] = 0;
	runAutoStack(conesHeight[1], coneDown[1], coneDown[1], false);
	//turnTo(0);
	*/

	barIsUp = true;
	backward(1200);

	motor[lLift] = motor[rLift] = 75;
	while(SensorValue[liftPot] < LIFT_MIN+300);
	motor[lLift] = motor[rLift] = 10;

	turnPD(450, true);
	backward(800);
	turnPD(900, true);

	forwardNonPID(200, 75);
	startTask(moveMoGoDown);
	forwardNonPID(200, 75);
	stopTask(moveMoGoDown);

	motor[moGo] = -100;
	while(SensorValue[moGoPot] < MOGO_UP)
	{
		motor[moGo] = -100;
	}
	motor[moGo] = 0;

	backward(700);
	writeDebugStreamLine("%d", time1[T3]);
}

void stationary()
{
	clearTimer(T3);
	startTask(barSet);

	startTask(intakeCone);
	sleep(200);
	startTask(moveMoGoDown);

	motor[lLift] = motor[rLift] = 75;
	while(SensorValue[liftPot] < 2100);
	motor[lLift] = motor[rLift] = 0;

	forwardNonPID(540, 60);
	barIsUp = false;
	sleep(500);

	motor[lLift] = motor[rLift] = -50;
	startTask(releaseCone);
	sleep(200);
	stopTask(releaseCone);
	motor[lLift] = motor[rLift] = 0;
	barIsUp = true;

	sleep(100);

	backward(470);

	turnTo(0, true);
	// Initiate swing turn
	// driveR(25);
	// while(SensorValue[gyroscope] < 0);
	// driveR(0);

	writeDebugStream("Gyro: %d\n", SensorValue[gyroscope]);

	motor[moGo] = 100;
	while(SensorValue[moGoPot] > MOGO_DOWN)
	{
		motor[moGo] = 100;
	}
	motor[moGo] = 0;

	motor[lLift] = motor[rLift] = -75;
	while(SensorValue[liftPot] > LIFT_MIN + 600);
	motor[lLift] = motor[rLift] = 10;

	forward(1250);
	forwardNonPID(20, 45);
	motor[moGo] = -100;

	while(SensorValue[moGoPot] < MOGO_UP)
	{
		motor[moGo] = -100;
	}
	turnTo(0);
	barIsUp = false;
	while (SensorValue(barPot) < BAR_DOWN - 1000) {}

	forwardNonPID(150, 45);
	motor[moGo] = 0;

	//turnTo(0);
	wait1Msec(100);
	motor[intake] = 100;
	motor[lLift] = motor[rLift] = -75;

	clearTimer(T1);
	while(SensorValue[liftPot] > LIFT_MIN + 50 && time1[T1] < 1000);
	motor[lLift] = motor[rLift] = 0;

	turnTo(-15);

	runAutoStack(conesHeight[0], coneDown[0], coneDown[0], false, false);
	barIsUp = true;
	backward(1400);

	turnTo(1800);

	motor[lLift] = motor[rLift] = 75;
	clearTimer(T1);
	while(SensorValue[liftPot] < LIFT_MIN + 400 && time1[T1] < 1000);
	motor[lLift] = motor[rLift] = 0;

	moGoIsUp = true;
	startTask(moveMoGoDown);
	while(moGoIsUp);
	backward(400);

	motor[moGo] = -100;
	while(SensorValue[moGoPot] < MOGO_UP)
	{
		motor[moGo] = -100;
	}
	motor[moGo] = 0;
	
	writeDebugStream("%d", time1[T3]);
}

void auton2()
{
	clearTimer(T3);
	motor[intake] = 50;
	wait10Msec(75);
	motor[intake] = 20;
	motor[lLift] = motor[rLift] = 75;
	while(SensorValue[liftPot] < LIFT_MIN + 400);
	motor[lLift] = motor[rLift] = 10;
	startTask(moveMoGoDown);
  //while(SensorValue[moGoPot] > MOGO_DOWN + 100);
  forward(1400);
	//forwardNonPID(200, 45);
	startTask(barSet);
  barIsUp = false;
  while(SensorValue(barPot) < BAR_DOWN - 500);
 	motor[lLift] = motor[rLift] = -75;
	while(SensorValue[liftPot] > LIFT_MIN + 200);
	motor[lLift] = motor[rLift] = 10;

	motor[intake] = -50;
	wait10Msec(50);
	motor[intake] = 0;

  barIsUp = true;
  while(SensorValue(barPot) > BAR_UP + 100);
	motor[lLift] = motor[rLift] = 75;
	while(SensorValue[liftPot] < LIFT_MIN + 300);
	motor[lLift] = motor[rLift] = 10;

	motor[moGo] = -100;
	int start1 = SensorValue[moGoPot];
	while(SensorValue[moGoPot] < MOGO_UP)
	{
		motor[moGo] = -100;// * (SensorValue[moGoPot]/MOGO_UP);
	}
	motor[moGo] = 0;

	turnPD((0 - SensorValue[gyroscope]), true, false);

	forwardNonPID(125, 45);
	barIsUp = false;
	//turnPD((0 - SensorValue[gyroscope]), false);;
	wait1Msec(100);
	motor[intake] = 100;
	motor[lLift] = motor[rLift] = -75;
	while(SensorValue[liftPot] > LIFT_MIN);
	motor[lLift] = motor[rLift] = 0;

	wait10Msec(20);
	runAutoStack(conesHeight[1], coneDown[1], coneDown[1], false);
	forwardNonPID(125, 45);
	runAutoStack(conesHeight[2], coneDown[2], coneDown[1], false);
	//turnPD((0 - SensorValue[gyroscope]), true);;
	backward(1325);
	motor[lLift] = motor[rLift] = 75;
	while(SensorValue[liftPot] < LIFT_MIN+300);
	motor[lLift] = motor[rLift] = 10;
	turnPD(900, true);
	turnPD(900, true);
	startTask(moveMoGoDown);
	wait10Msec(20);
	motor[moGo] = -100;
	while(SensorValue[moGoPot] < MOGO_UP)
	{
		motor[moGo] = -100;// * (SensorValue[moGoPot]/MOGO_UP);
	}
	barIsUp = true;
	backward(800);
	turnPD(900, true);
	forwardNonPID(200, 75);

	forwardNonPID(200, 75);
	stopTask(moveMoGoDown);

	motor[moGo] = 0;

	backward(700);
	writeDebugStreamLine("%d", time1[T3]);
}

task autonomous()
{
    clearDebugStream();
    datalogClear();
  ///  stopTask(runLCD);
    clearLCDLine(0);
    clearLCDLine(1);

    // 0 - 20 Pt Right Red
    // 1 - 20 Pt Left Blue
    // 2 - 10 Pt Red
    // 3 - 10 Pt Blue
    // 4 - 5 Pt Red
    // 5 - 5 Pt Blue
	clearDebugStream();
//turnBangBang(450);
	//turnBrake(fale);
	//turnPD(-900, false);
	//turnTo(-900);
	stationary();
	//forward(1050);
	wait10Msec(100);
	//backward(1050);
/*	writeDebugStreamLine("Gyro at: %d", GyroGetAngle());
	sleep(3000);
	//turnTo(0);
	writeDebugStreamLine("Gyro at: %d", GyroGetAngle());
	autonCount = -1;*/

}

#endif
