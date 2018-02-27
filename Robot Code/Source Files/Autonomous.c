// Stop recursive includes
#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#include "Variables.c"

// Naming conventions: "matchAuton_COLOR_PTVALUE"
// NUM_CONE DOES NOT COUNT THE PRELOAD

void matchAuton_RED_RIGHT_Stationary()
{
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
}

void matchAuton_RED_24()
{
  deploy();
	grabMGoal();
  grabCone();
  scoreGoal20(true, ONE_CONE);
}

void matchAuton_BLUE_24()
{
  deploy();
	grabMGoal();
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
  grabCone();
 // while(!autoStackEnd);
 //grabCone();
	autonIs24 = false;

  scoreGoal5(true, ONE_CONE+300);
}

void matchAuton_BLUE_7()
{
	deploy();
	grabMGoal();
  grabCone();
 // while(!autoStackEnd);
 //grabCone();
	autonIs24 = false;

  scoreGoal5(false, ONE_CONE+300);
}

#endif
