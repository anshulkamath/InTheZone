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
	motor[intake] = 50;
	wait10Msec(75);
	motor[intake] = 20;
	motor[lLift] = motor[rLift] = 75;
	while(SensorValue[liftPot] < LIFT_MIN + 400);
	motor[lLift] = motor[rLift] = 0;
	startTask(moveMoGoDown);
  while(SensorValue[moGoPot] > MOGO_DOWN + 100);
  forward(1100);
  wait10Msec(10);
	forwardNonPID(200, 45);
	startTask(barSet);
  barIsUp = false;
  while(SensorValue(barPot) < BAR_DOWN - 100);
 	motor[lLift] = motor[rLift] = -75;
	while(SensorValue[liftPot] > LIFT_MIN + 200);
	motor[lLift] = motor[rLift] = 0;

	motor[intake] = -50;
	wait10Msec(50);
	motor[intake] = 0;

  barIsUp = true;
  while(SensorValue(barPot) > BAR_UP + 100);
	motor[lLift] = motor[rLift] = 75;
	while(SensorValue[liftPot] < LIFT_MIN + 100);
	motor[lLift] = motor[rLift] = 0;

	motor[moGo] = -100;
	int start1 = SensorValue[moGoPot];
	while(SensorValue[moGoPot] < MOGO_UP)
	{
		motor[moGo] = -100;// * (SensorValue[moGoPot]/MOGO_UP);
	}
	motor[moGo] = 0;
	turnV3(0);
	forwardNonPID(125, 45);
	barIsUp = false;
	wait1Msec(100);

	motor[lLift] = motor[rLift] = -75;
	while(SensorValue[liftPot] > LIFT_MIN);
	motor[lLift] = motor[rLift] = 0;
	motor[intake] = 50;
	wait10Msec(50);
	motor[intake] = 30;

	runAutoStack(conesHeight[1], coneDown[1], coneDown[1], false);

	backward(1400);

	turnV3(-45);
	backward(600);
	//turnV3(SensorValue[
	// move backwards
	// turn
	// move backwards again
	// turn
	// forward
	// drop in high cone
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
