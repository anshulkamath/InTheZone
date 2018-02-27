#pragma config(Sensor, in1,    liftPot,        sensorPotentiometer)
#pragma config(Sensor, in2,    moGoPot,        sensorPotentiometer)
#pragma config(Sensor, in3,    barPot,         sensorPotentiometer)
#pragma config(Sensor, in4,    gyroscope,      sensorGyro)
#pragma config(Sensor, in5,    liftPot2,       sensorPotentiometer)
#pragma config(Sensor, dgtl4,  moGoLim,      sensorTouch)
#pragma config(Sensor, dgtl7,  lDriveQuad,     sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  rDriveQuad,     sensorQuadEncoder)
#pragma config(Motor,  port1,           barL,          tmotorVex393HighSpeed_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           leftB,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           leftF,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           lLift,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           moGo,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           intake,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           rLift,         tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           rightB,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           rightF,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          barR,          tmotorVex393HighSpeed_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Prevents recursive includes
#ifndef MAIN_H
#define MAIN_H

// All includes
#pragma platform(VEX2)
#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"
#include "MainControl.c"
#include "Variables.c"
#include "GyroLib.c"
#include "AutoStack.c"
#include "LCDCode.c"
#include "Autonomous.c"

// Pre-Auton
void pre_auton()
{
	bDisplayCompetitionStatusOnLcd = false;
	bStopTasksBetweenModes = false;

	// Initializes the cones arrays
	autoConeInitVals();

	gyroIsCalibrating = true;
	writeDebugStreamLine("%d", SensorValue[liftPot]);
	startTask(runLCD);

	// Calibrates Gyroscope
	GyroInit(in4);
	wait1Msec(1000);
	wait1Msec(2000);
	SensorFullCount[in4] = 3600 * 100;
	SensorScale[in4] = 130;
	gyroIsCalibrating = false;
}

task autonomous()
{
    clearDebugStream();
    datalogClear();
    clearLCDLine(0);
    clearLCDLine(1);

		// writeDebugStreamLine("Gyro at: %d", GyroGetAngle());
		// sleep(3000);
		// writeDebugStreamLine("Gyro at: %d", GyroGetAngle());

    switch(autonCount)
    {
      case 0:
        matchAuton_BLUE_24();
        break;
      case 1:
        matchAuton_RED_24();
        break;
      case 2:
        matchAuton_BLUE_7();
      case 3:
        matchAuton_RED_7();
        break;
      case 4:
        matchAuton_RED_7();
        break;
      case 5:
        matchAuton_BLUE_7();
        break;
    }
}

// User Control
task usercontrol()
{
	// Clearing all output streams
	datalogClear();
	clearLCDLine(0);
	clearLCDLine(1);

	// Stopping all auton tasks
	stopTask(lDrivePID);
	stopTask(rDrivePID);

	// Starting Tasks
	// startTask(stabilizeLift);
	// startTask(autoStack);
	startTask(controller);
	startTask(robotControl);
	startTask(runLCD);

	while (true)
	{
		//int leftPot = SensorValue(liftPot);
		//int rightPot = SensorValue(liftPot2);
		//writeDebugStreamLine("%f %f", GyroGetAngle(), GyroAngleAbsGet());
	}
}

#endif
