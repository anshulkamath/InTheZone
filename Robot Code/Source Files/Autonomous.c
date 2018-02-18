// Stop recursive includes
#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#include "Variables.c"
#include "Autonomous Functions.c"

// Naming conventions: "matchAuton_COLOR_PTVALUE"

void matchAuton_RED_RIGHT_Stationary()
{
	forward(600);
	liftTarget = LIFT_STATIONARY;
	startTask(lLiftPID);
	forward(50);
	barIsUp = false;
	startTask(barSet);
	intakeCone(0);
	right(1350);
	forward(300);
  motor[intake] = 100;

  liftTarget = LIFT_MIN + 200;
  while(SensorValue[liftPot] > LIFT_MIN + 200);
  stopTask(lLiftPID);
	runAutoStack(conesHeight[cones], coneDown[cones], false);
	right(1800);
	barIsUp = true;
	forward(300);
	barIsUp = false;

	liftTarget = LIFT_STATIONARY+200;
	startTask(lLiftPID);
	forward(50);
	barIsUp = false;
	sleep(500);
	backward(50);


	/*
	forward
	place on stationary
	turn right
	forward
	pick up cone
	turn 180
	forward
	place on stationary
	back small amount
	right 90 degrees
	forward
	*/
}

void matchAuton_RED_24()
{
  deploy();
  //grabMogo();
	grabMGoal();
	turnTo(0);
  grabCone();
	turnTo(0);
  scoreGoal20(true, ONE_CONE);
}

void matchAuton_BLUE_24()
{
  deploy();
  grabMogo();
	grabMGoal();
	turnTo(0);
  grabCone();
  scoreGoal20(false, ONE_CONE);
}

void matchAuton_RED_22()
{
  deploy();
  grabMGoal();
  scoreGoal20(true, NO_CONES);
}

void matchAuton_BLUE_22()
{
  deploy();
  grabMGoal();
  scoreGoal20(false, NO_CONES);
}

void matchAuton_RED_12()
{
  deploy();
  grabMGoal();
  scoreGoal10(true, NO_CONES);
}

void matchAuton_BLUE_12()
{
  deploy();
  grabMGoal();
  scoreGoal10(false, NO_CONES);
}

void matchAuton_RED_7()
{
  deploy();
  grabMGoal();
  scoreGoal5(false, NO_CONES);
}

void matchAuton_BLUE_7()
{
  deploy();
  grabMGoal();
  scoreGoal5(true, NO_CONES);
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

    switch(autonCount)
    {
      case -1:
        break;
      case 0:
        matchAuton_RED_24();
        break;
      case 1:
        matchAuton_BLUE_22();
        break;
      case 2:
        matchAuton_RED_12();
      case 3:
        matchAuton_BLUE_12();
        break;
      case 4:
        matchAuton_RED_7();
        break;
      case 5:
        matchAuton_BLUE_7();
        break;
    }
}

#endif
