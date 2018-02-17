// Stop recursive includes
#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#include "Vex_Competition_Includes.c"
//#include "Motors and Sensors.c"
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
	forward(1450);
	//forwardNonPID(350, 50);
	sleep(500);
	isMogoUp = false;
	startTask(MGoalUp);
	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 40;
	sleep(200);
	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 0;
	sleep(600);

	while(!isMogoUp);
//	forwardNonPID(100);
	stopTask(lLiftPID);
	startTask(barSet);
	barIsUp = false;
	while(SensorValue[barPot] > BAR_DOWN) {}
	motor[lLift] = motor[rLift] = -100;
	while(SensorValue[liftPot] > LIFT_MIN + 200) {}
	motor[lLift] = motor[rLift] = -60;
	while(SensorValue[liftPot] > LIFT_MIN) {}
	motor[lLift] = motor[rLift] = 0;
	sleep(200);
	motor[intake] = 70;
	forwardNonPID(120);
	motor[intake] = 30;
	cones = 1;
	if(cones < size)
	{
		//	intakeCone(1);
		runAutoStack(conesHeight[cones], coneDown[cones], false);
		cones++;
	}
	liftTarget = LIFT_MIN + 200;
	startTask(lLiftPID);
	barIsUp = true;
	writeDebugStreamLine("%d",GyroGetAngle());
	turnTo(0);
	writeDebugStreamLine("%d",GyroGetAngle());
	backward(1600);
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
	intakeCone(1);
	grabMogo();

	right(450);
	backward(775);
	right(1000);
	//startTask(delayMGoalThrow);
	//startTask(moGoSet);
	motor[leftB] = motor[rightB] = motor[leftF] = motor[rightF] = 100;

	forwardNonPID(450);
//	longDelay = true;
//	startTask(delayMGoalThrow);
	motor[moGo] = 90;
	while(SensorValue[moGoPot] > 1720 + 200);
	motor[moGo] = 0;
	forwardNonPID(300);
	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = -127;
	sleep(200);
	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 0;
//	deployMGoal(1);
	backward(100);
	startTask(MGoalUp);
	sleep(800);
	backward(500);
}

void matchAutonLeftBlue()
{
	intakeCone(1);
	grabMogo();

	left(450);
	backward(400);
	left(900);
	//startTask(delayMGoalThrow);
	moGoIsUp = true;
	startTask(moGoSet);
	motor[leftB] = motor[rightB] = motor[leftF] = motor[rightF] = 100;

	forwardNonPID(100);
	moGoIsUp = false;
	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 100;
	sleep(800);
	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = -50;
	sleep(200);
	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 0;
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
		stopTask(runLCD);
		clearLCDLine(0);
		clearLCDLine(1);

    // 0 - 20 Pt Right Red
    // 1 - 20 Pt Left Blue
    // 2 - 10 Pt Red
    // 3 - 10 Pt Blue
    // 4 - 5 Pt Red
    // 5 - 5 Pt Blue
    /*grabMogoOtherSide();
    sleep(350);
		right(900);*/

		//forward(500);
		//backward(500);
		//left(900);
		//sleep(500);
		//right(900);
		//while(true);



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
