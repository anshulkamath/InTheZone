// Stop recursive includes
#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#include "Variables.c"
#include "AutonControl.c"
//#include "GyroPid.c"

// Naming conventions: "matchAuton_COLOR_PTVALUE"
// NUM_CONE DOES NOT COUNT THE PRELOAD

task deploy()
{
	startTask(intakeCone);
	sleep(200); // wait for cone to get into intake

}

// 22_Left
void auton1()
{
	writeDebugStreamLine("%d", SensorValue[gyroscope]);
	clearTimer(T3);
	startTask(barSet);
	startTask(liftSet);

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

	motor[lLift] = motor[rLift] = 75;
	while(SensorValue[liftPot] < LIFT_MIN + 400);
	motor[lLift] = motor[rLift] = 10;
	startTask(moveMoGoDown);

  forward(1300);
  barIsUp = false;
  while(SensorValue(barPot) < BAR_DOWN - 500);
motor[intake] = -50;
	wait10Msec(50);
	motor[intake] = 0;

  barIsUp = true;
  while(SensorValue(barPot) > BAR_UP + 100);

	liftTarget = LIFT_MIN + 300;

	startTask(moGoUp);
	wait10Msec(50);


	writeDebugStream("%d", SensorValue[gyroscope]);
	if(abs(SensorValue[gyroscope]) > 30)
		turnTo(0);
	writeDebugStream("%d", SensorValue[gyroscope]);

	// Could replace with startTask(releaseCone)


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

	liftTarget = LIFT_MIN + 350;

	turnTo(-450, false);
	backward(600);
	turnTo(-1350, false);

	forwardNonPID(200, 75);
	moGoIsUp = true;
	startTask(moveMoGoDown);
	forwardNonPID(400, 75);
	//while(moGoIsUp);
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

void cones3()
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
	motor[lLift] = motor[rLift] = -75;
	while(SensorValue[liftPot] > LIFT_MIN + 200);
	motor[lLift] = motor[rLift] = 10;
	forwardNonPID(125, 45);
	barIsUp = false;
	//turnTo(0);
	wait1Msec(100);
	motor[intake] = 100;
	runAutoStack(conesHeight[0], coneDown[0], coneDown[0], false);
	turnTo(0);
	motor[intake] = 100;
	motor[lLift] = motor[rLift] = -75;
	while(SensorValue[liftPot] > LIFT_MIN);
	motor[lLift] = motor[rLift] = 0;
	turnTo(0);
	barIsUp = true;
	backward(950);

	driveL(60);
	driveR(-60);
	while(SensorValue[gyroscope] > -900);
	driveL(0);
	driveR(0);
	motor[lLift] = motor[rLift] = 75;
	clearTimer(T1);
	while(SensorValue[liftPot] < LIFT_MIN + 400 && time1[T1] < 1000);
	motor[lLift] = motor[rLift] = 0;

	moGoIsUp = true;
	startTask(moveMoGoDown);
	while(moGoIsUp);

	backward(550);
	//writeDebugStream("%d", time1[T3]);
	motor[moGo] = -100;
	while(SensorValue[moGoPot] < MOGO_UP)
	{
		motor[moGo] = -100;
	}
	motor[moGo] = 0;

	writeDebugStream("Time: %d\n", time1[T3]);


}

void stationary(bool loader, bool isLeft)
{
	clearTimer(T3);
	startTask(barSet);
	startTask(intakeCone);
	startTask(moveMoGoDown);
	startTask(liftSet);
	liftDone = false;
	liftTarget = 2100;
	while(!liftDone);

	forwardNonPID(540, 60);
	barIsUp = false;
	sleep(500);

	motor[lLift] = motor[rLift] = -50;
	startTask(releaseCone);
	sleep(200);
	stopTask(releaseCone);
	motor[lLift] = motor[rLift] = 0;
	barIsUp = true;
	while (SensorValue(barPot) < BAR_DOWN - 1250) {}


	if(!loader)
	{
		backward(535);
	//liftTarget = LIFT_MIN;
		turnTo(0, true);
	}
	else
	{
		backward(440);
	//liftTarget = LIFT_MIN+500;
		turnTo(35, true);
	}

	// Initiate swing turn
	// driveR(25);
	// while(SensorValue[gyroscope] < 0);
	// driveR(0);

	writeDebugStream("Gyro: %d\n", SensorValue[gyroscope]);

	motor[moGo] = 100;
	bool doney = false;
	while(SensorValue[moGoPot] > MOGO_DOWN)
	{
		motor[moGo] = 100;
	}
	motor[moGo] = 0;

	//liftDone = false;
	//liftTarget = LIFT_MIN + 1000;
	//while(!liftDone);

	forward(1300);
	if(!loader)
		forwardNonPID(20, 45);
	else
		forwardNonPID(70, 45);
	motor[moGo] = -100;

	startTask(moGoUp);
/*	turnTo(-10);
	//turnTo(0);
	motor[lLift] = motor[rLift] = -75;
	while(SensorValue[liftPot] > LIFT_MIN + 100);
	motor[lLift] = motor[rLift] = 0;
	barIsUp = false;
	while (SensorValue(barPot) < BAR_DOWN - 1000) {}

	forwardNonPID(300, 45);


	//turnTo(0);
	motor[intake] = 100;
	motor[lLift] = motor[rLift] = -75;

	clearTimer(T1);
	while(SensorValue[liftPot] > LIFT_MIN + 50 && time1[T1] < 1000);
	motor[lLift] = motor[rLift] = 0;

	//turnTo(-15);

	runAutoStack(conesHeight[0], coneDown[0], coneDown[0], false, false);*/
	turnTo(0);
	/*barIsUp = false;
	liftTarget = LIFT_MIN;
	liftDone = false;
	motor[intake] = 100;
	while(!liftDone);*/
	barIsUp = true;
	backward(950);
	if(isLeft)
	{
		driveL(-60);
		driveR(60);
		while(SensorValue[gyroscope]  < 900);
	}else
	{
		driveL(60);
		driveR(-60);
		while(SensorValue[gyroscope] >- 900);

	}
	driveL(0);
	driveR(0);
	motor[lLift] = motor[rLift] = 75;
	clearTimer(T1);
	while(SensorValue[liftPot] < LIFT_MIN + 400 && time1[T1] < 1000);
	motor[lLift] = motor[rLift] = 0;

	moGoIsUp = true;
	startTask(moveMoGoDown);
	while(moGoIsUp);

	backward(350);
	//writeDebugStream("%d", time1[T3]);
	motor[moGo] = -100;
	while(SensorValue[moGoPot] < MOGO_UP)
	{
		motor[moGo] = -100;
	}
	motor[moGo] = 0;

	writeDebugStream("Time: %d\n", time1[T3]);
}

void stationary1(bool loader)
{
	clearTimer(T3);
	startTask(barSet);
	startTask(intakeCone);
	startTask(moveMoGoDown);
	startTask(liftSet);
	liftDone = false;
	liftTarget = 2000;
	while(!liftDone);

	forwardNonPID(490, 60);
	barIsUp = false;
	sleep(500);

	motor[lLift] = motor[rLift] = -50;
	startTask(releaseCone);
	sleep(200);
	stopTask(releaseCone);
	motor[lLift] = motor[rLift] = 0;
	barIsUp = true;
	while (SensorValue(barPot) < BAR_DOWN - 1250) {}


	if(!loader)
	{
		backward(540);
	//liftTarget = LIFT_MIN;
		turnTo(5, true);
	}
	else
	{
		backward(440);
	//liftTarget = LIFT_MIN+500;
		turnTo(35, true);
	}

	// Initiate swing turn
	// driveR(25);
	// while(SensorValue[gyroscope] < 0);
	// driveR(0);

	writeDebugStream("Gyro: %d\n", SensorValue[gyroscope]);

	motor[moGo] = 100;
	bool doney = false;
	while(SensorValue[moGoPot] > MOGO_DOWN)
	{
		motor[moGo] = 100;
	}
	motor[moGo] = 0;

	//liftDone = false;
	//liftTarget = LIFT_MIN + 1000;
	//while(!liftDone);

	forward(1250);
	if(!loader)
		forwardNonPID(70, 45);
	else
		forwardNonPID(70, 45);
	motor[moGo] = -100;
	moGoIsUp = false;
	startTask(moGoUp);
	while(SensorValue[moGoPot] < MOGO_UP - 800);
	//forwardNonPID(200, 45);
	//turnTo(-10);
	//turnTo(0);
	turnTo(0, false);

	/*while(SensorValue[moGoPot] < 2047);
	motor[lLift] = motor[rLift] = -75;
	barIsUp= false;

	clearTimer(T1);
	stopTask(liftSet);
	motor[lLift] = motor[rLift] = -75;
	while(SensorValue[liftPot] > LIFT_MIN+50 && time1[T1] < 250);
	motor[lLift] = motor[rLift] = 0;
	clearTimer(T1);
	while (SensorValue(barPot) < BAR_DOWN - 1500 && time1[T1] < 250) {}
	//forwardNonPID(100, 45);
	motor[intake] = 100;
	wait1Msec(100);

	startTask(startAutoStack);*/

	/*barIsUp = false;
	liftTarget = LIFT_MIN;
	liftDone = false;
	motor[intake] = 100;
	while(!liftDone);*/
	barIsUp = true;
	backward(1000);

	driveL(-120);
	driveR(120);
	moGoIsUp = true;
	startTask(moveMoGoDown);
	while(SensorValue[gyroscope] < 700)
	{
	}
	driveL(0);
	driveR(0);
	motor[lLift] = motor[rLift] = 75;
	clearTimer(T1);
	while(SensorValue[liftPot] < LIFT_MIN + 400 && time1[T1] < 1000);
	motor[lLift] = motor[rLift] = 0;


	while(moGoIsUp);
	backward(350);
	//writeDebugStream("%d", time1[T3]);

	writeDebugStream("Time: %d\n", time1[T3]);
}


void auton2(bool isLeft)
{
	writeDebugStreamLine("%d", SensorValue[gyroscope]);
	clearTimer(T3);
	startTask(barSet);
	startTask(liftSet);

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

	motor[lLift] = motor[rLift] = 75;
	while(SensorValue[liftPot] < LIFT_MIN + 400);
	motor[lLift] = motor[rLift] = 10;
	startTask(moveMoGoDown);

  forward(1400);
  barIsUp = false;
  while(SensorValue(barPot) < BAR_DOWN - 500);
motor[intake] = -50;
	wait10Msec(50);
	motor[intake] = 0;

  barIsUp = true;
  while(SensorValue(barPot) > BAR_UP + 100);

	liftTarget = LIFT_MIN + 300;

	startTask(moGoUp);
	wait10Msec(50);


	writeDebugStream("%d", SensorValue[gyroscope]);
//	if(abs(SensorValue[gyroscope]) > 30)
	//	turnTo(0);
	writeDebugStream("%d", SensorValue[gyroscope]);

	// Could replace with startTask(releaseCone)


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

	liftTarget = LIFT_MIN + 350;

	if(!isLeft)
	{
		turnTo(-450, false);
		backward(600);
		turnTo(-1350, false);
	}else
	{
		turnTo(450, false);
		backward(600);
		turnTo(1350, false);
	}

	forwardNonPID(200, 75);
	moGoIsUp = true;
	startTask(moveMoGoDown);
	while(SensorValue[moGoPot] > 2500);
	forwardNonPID(650, 75);
//	wait1Msec(250);
	//while(moGoIsUp);

	stopTask(moveMoGoDown);

	startTask(moGoUp);

	backward(700);
	writeDebugStreamLine("%d", time1[T3]);
}

//
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
//	turnPD(-900 + 200, false);
	//turnTo(0, true);
	//turnTo(-900, true);
	//auton1();
	//autonCount = 1;
	//cones3()
	//stationary(true, true);
	stationary1(false);
	//turnTo(900);
	/*wait1Msec(5000);
	if(autonCount == 0)
		auton2(true);
	else
		auton2(false);*/
	//stationary(false, true);
/*	if(autonCount == 0)
		stationary1(false);
	else if(autonCount == 1)
		stationary(true);
	else if(autonCount == 2)
	{
		auton1();
	}else
	{
		auton2();
	}*/
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
