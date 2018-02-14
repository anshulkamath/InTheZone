// Stop recursive includes
#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#include "Vex_Competition_Includes.c"
#include "Motors and Sensors.c"
#include "Variables.c"
#include "LCD Code.c"
#include "Autonomous Control.c"
#include "GyroLib.c"

void skillsauton1()
{
	liftTarget = LIFT_MIN + 600;
	startTask(lLiftPID);
	deployMGoal(1);

	forward(1120);

	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 100;
	sleep(200);
	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 0;

	deployMGoal(0);
	right(1800);
	forward(1000);
	right(900);
	sleep(500);
	forward(430);
	sleep(500);
	left(900);
	sleep(500);

	motor[moGo] = 100;
	sleep(400);
	motor[moGo] = 0;

	timeforward(200,500);
	sleep(800);
	int angle = GyroGetAngle();
	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 100;
	sleep(1000);
	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 0;

	timebackward(700,2000);
	deployMGoal(0);

	turnTo(angle);

	right(900);
	timebackward(1100,2000);
	motor[rightB] = motor[rightF] = -50;
	sleep(2000);
	motor[rightB] = motor[rightF] = 0;
	sleep(500);
	pre_auton();
	forward(1200);
	right(450);
	deployMGoal(1);
	forward(1000);

	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 100;
	sleep(200);
	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 0;

	deployMGoal(0);

	forward(700);

	left(900);
	sleep(500);
	forward(450);
	sleep(500);
	right(900);
	sleep(500);

	motor[barL] = 100;
	sleep(400);
	motor[barL] = 0;

	timeforward(200,500);
	sleep(800);
	angle = GyroGetAngle();
	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 100;
	sleep(1000);
	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 0;

	timebackward(700,2000);
	deployMGoal(0);

}

void grabMogo()
{
	motor[intake] = 20;
	liftTarget = LIFT_MIN + 200;
	startTask(lLiftPID);
	//startTask(barSet);
	startTask(MGoalDown);
	//barIsUp = true;
	sleep(500);
	forward(1350);

	startTask(MGoalUp);
	intakeCone(0);

	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 100;
	sleep(200);
	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 0;
	sleep(600);

	writeDebugStreamLine("%d",GyroGetAngle());
	turnTo(0);
	writeDebugStreamLine("%d",GyroGetAngle());
	backward(1750);
	writeDebugStreamLine("%d",GyroGetAngle());
}

void grabMogoOtherSide()
{
	motor[intake] = 20;
	liftTarget = LIFT_MIN + 200;
	startTask(lLiftPID);
	//startTask(barSet);
	startTask(MGoalDown);
	//barIsUp = true;
	sleep(500);
	forward(1350);

	startTask(MGoalUp);
	intakeCone(0);
	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 100;
	sleep(400);
	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 0;
	sleep(1000);

	writeDebugStreamLine("%d",GyroGetAngle());
	turnTo(0);
	writeDebugStreamLine("%d",GyroGetAngle());
	backward(1750);
	writeDebugStreamLine("%d",GyroGetAngle());
}

void matchAutonRightRed()
{
	grabMogo();

	right(450);
	backward(750);
	right(900);
	startTask(delayMGoalThrow);
	timeforward(650,1200);
	deployMGoal(1);
	backward(100);
	startTask(MGoalUp);
	sleep(800);
	backward(500);
}

void matchAutonLeftBlue()
{
	grabMogo();

	left(450);
	backward(750);
	left(900);
	startTask(delayMGoalThrow);
	timeforward(650,1200);
	deployMGoal(1);
	backward(100);
	startTask(MGoalUp);
	sleep(800);
	backward(500);

}

void matchAuton10PtBlue()
{
	grabMogoOtherSide();

	left(1350);
	forward(300);
	left(900);
	timeforward(200,600);
	deployMGoal(1);
	backward(800);
}

void matchAuton10PtRed()
{
	grabMogoOtherSide();

	right(1350);
	forward(300);
	right(900);
	timeforward(200,600);
	deployMGoal(1);
	backward(800);
}

void matchAuton5PtBlue()
{
	grabMogoOtherSide();

	forward(200);
	left(2000);
	deployMGoal(1);
	backward(500);
}

void matchauton5PtRed()
{
	grabMogoOtherSide();

	forward(200);
	right(2000);
	deployMGoal(1);
	backward(500);
}

task autonomous()
{
    clearDebugStream();
    datalogClear();

    // 0 - 20 Pt Right Red
    // 1 - 20 Pt Left Blue
    // 2 - 10 Pt Red
    // 3 - 10 Pt Blue
    // 4 - 5 Pt Red
    // 5 - 5 Pt Blue
		startTask(delayMGoalThrow);
		forward(2020);
		startTask(MGoalUp);
		sleep(500);
		backward(1500);
		right(900);
    switch(autonCount)
    {
      case -1:
        break;
      case 0:
        matchAutonRightRed();
        break;
      case 1:
        matchAutonLeftBlue();
        break;
      case 2:
        matchAuton10PtRed();
      case 3:
        matchAuton10PtBlue();
        break;
      case 4:
        matchauton5PtRed();
        break;
      case 5:
        matchAuton5PtBlue();
        break;
    }
}

#endif
