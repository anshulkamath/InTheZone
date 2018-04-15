// Stop recursive includes
#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#include "Variables.c"
#include "AutonControl.c"
#include "GyroPid.c"

// Naming conventions: "matchAuton_COLOR_PTVALUE"
// NUM_CONE DOES NOT COUNT THE PRELOAD

void auton1()
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

	/*forwardNonPID(125, 45);
	barIsUp = false;
	//turnPD((0 - SensorValue[gyroscope]), false);;
	wait1Msec(100);
	motor[intake] = 100;
	motor[lLift] = motor[rLift] = -75;
	while(SensorValue[liftPot] > LIFT_MIN);
	motor[lLift] = motor[rLift] = 0;

	wait10Msec(20);
	runAutoStack(conesHeight[1], coneDown[1], coneDown[1], false);
	//turnPD((0 - SensorValue[gyroscope]), true);;*/
	backward(1200);
	motor[lLift] = motor[rLift] = 75;
	while(SensorValue[liftPot] < LIFT_MIN+300);
	motor[lLift] = motor[rLift] = 10;
	turnPD(450, true);
	barIsUp = true;
	backward(800);
	turnPD(900, true);
	forwardNonPID(200, 75);
	startTask(moveMoGoDown);
	forwardNonPID(200, 75);
	stopTask(moveMoGoDown);
	motor[moGo] = -100;
	while(SensorValue[moGoPot] < MOGO_UP)
	{
		motor[moGo] = -100;// * (SensorValue[moGoPot]/MOGO_UP);
	}
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
	auton1();
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
