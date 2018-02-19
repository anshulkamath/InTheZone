#ifndef AUTONOMOUS_FUNCTIONS_H
#define AUTONOMOUS_FUNCTIONS_H

#include "Variables.c"

// Autonomous functions
void deploy()
{
  // 1 - Runs intake in
  // 2 - Runs lift up
	// 3 - Runs mobile goal intake out

	// 1
	intakeCone(1);
  motor[intake] = INTAKE_HOLD;

	// 2
	liftTarget = LIFT_MIN + 200;
	startTask(lLiftPID);
	sleep(400);
	startTask(barSet);

	// 3
	startTask(mGoalAuton);

  barIsUp = true;
  sleep(200);
}

void grabMGoal()
{
  // 1 - Drives forward to just before the mobile goal
  // 2 - Runs forward slowly to secure mobile goal until the limit switch has been hit
	// 3 - Run mGoalAuton task to bring mobile goal in

  // 1
  forward(1260);
	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 10; // Power to prevent jerk from PID
	sleep(500);

	// 2
  motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 40;
	while(SensorValue[moGoLim] == 0) {}

	// 3
	startTask(mGoalAuton);
	while(!moGoIsUp); // Waits for mGoal to go up
}

void grabCone()
{
  // 1 - Stops task liftPID and AutoStack takes over for the lift
	// 2 - Drives forward to align with cone
  // 3 - Moves the bar down
  // 4 - Moves the lift down
  // 5 - Runs the intake while running forward to grab the cone
  // 6 - Runs the autostack function
  // 7 - Turns on lift PID and gets the lift and bar out of the way of the mGoal
  // 8 - Readjusts

  // 1
  stopTask(lLiftPID);

	// 2
	forwardNonPID(25, 40);

  // 3
  barIsUp = false;
  motor[intake] = 100;
  while(SensorValue[barPot] > 1915) {}

  // 4
	motor[lLift] = motor[rLift] = -100;
	while(SensorValue[liftPot] > LIFT_MIN + 200) {}
	motor[lLift] = motor[rLift] = 0 ;

  sleep(200);

  // 5
  sleep(400);
  motor[intake] = 30;

  // 6
  if(cones < size)
	{
		runAutoStack(conesHeight[cones], coneDown[cones], false);
		cones++;
	}

  // 7
	liftTarget = LIFT_MIN + 200;
	startTask(lLiftPID);
	barIsUp = true;
}

void scoreGoal20(bool isRed, int distBack)
{
  // 1 - Turns to 0 value on Gyro
  // 2 - Go back to starting position
  // 3 - Turns right
  // 4 - Goes backwards to be in line with 20pt zone
  // 5 - Turns right to face 20pt zone
  // 6 - Goes over the bump
  // 7 - Prepares mobile goal for throw into zone
  // 8 - Throws mobile goal into the zone
  // 9 - Moves backwards, brings in mobile goal, and moves out of the zone

  turnTo(0); // 1
	backward(distBack); // 2
  if(isRed) right(450); else left (450); // 3
	backward(790); // 4
	if(isRed) right(1000); else left (1000); // 5
  forwardNonPID(450); // 6

  // 7
  motor[moGo] = 100;
	while(SensorValue[moGoPot] > MOGO_THROW + 200);
	motor[moGo] = 0;

  // 8
  forwardNonPID(300);
  motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = -100;
  sleep(200);
  motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 0;

  // 9
  backward(100);
  startTask(mGoalAuton);
  sleep(800);
  backward(500);
}

void scoreGoal10(bool isRed, int distBack)
{
  // 1 - Turns to 0 value on Gyro
  // 2 - Go back to starting position
  // 3 - Turns right
  // 4 - Goes backwards to distance robot from field fence
  // 5 - Turns right to face 10pt zone
  // 6 - Goes over the bump
  // 7 - Places mobile goal into the zone
  // 8 - Moves backwards, brings in mobile goal, and moves out of the zone

  turnTo(0); // 1
	backward(distBack); // 2
  if(isRed) right(450); else left (450); // 3
	backward(100); // 4
	if(isRed) right(1000); else left (1000); // 5
  forward(300); // 6
  startTask(mGoalAuton); // 7

  sleep(800);

  // 8
  backward(500);
  startTask(mGoalAuton);
}

void scoreGoal5(bool isRed, int distBack)
{
  // 1 - Turns to 0 value on Gyro
  // 2 - Go back to starting position
  // 3 - Turns 180
  // 4 - Goes backwards to distance robot from field fence
  // 5 - Runs mGoal lift down
  // 6 - Releases mGoal

  turnTo(0); // 1
	backward(distBack); // 2
  if(isRed) right(1800); else left (1800); // 3
  forward(300); // 4
  startTask(mGoalAuton); // 5
  sleep(800);
  backward(300); // 6
}


#endif
