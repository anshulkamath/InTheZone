#ifndef AUTONOMOUS_FUNCTIONS_H
#define AUTONOMOUS_FUNCTIONS_H

#include "Variables.c"

// Autonomous functions
void deploy()
{
	// Pre-condition: N/A
	// Post-condition: Robot is deployed

	// Steps:
  // 1 - Runs intake in
  // 2 - Runs lift up
	// 3 - Runs mobile goal intake out

	// 1
  motor[intake] = INTAKE_HOLD + 10;

	// 2
	liftTarget = LIFT_MID;
	startTask(lLiftPID);
	startTask(barSet);

	// 3
	sleep(150);
	moGoIsUp = true;
	startTask(mGoalAuton);
	while(moGoIsUp);

  //barIsUp = true;
}

void grabMGoal()
{
	// Pre-condition: Robot is deployed
	// Post-condition: Mobile goal is in robot with one cone on it

	// Steps:
  // 1 - Drives forward to just before the mobile goal
	// 2 - Brings four bar down to be directly over mobile goal
  // 3 - Runs forward slowly to secure mobile goal until the limit switch has been hit
	// 4 - Releases cone onto mobile goal
	// 5 - Run mGoalAuton task to bring mobile goal in

  // 1
	barIsUp = false;
  forward(1260);
//	liftTarget = LIFT_MID;
	// 2


	// 3
	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 40; // Power to prevent jerk from PID
	sleep(350);
	motor[leftB] = motor[leftF] = motor[rightB] = motor[rightF] = 0;

	// 4
	while(SensorValue[barPot] > BAR_DOWN) {} // This shouldn't ever run; +100 for small margin of error
	liftTarget = LIFT_MIN;
	intakeCone(0);

	// 5
	liftTarget = LIFT_MID;
	while(SensorValue[liftPot] < LIFT_MID - 300);
	startTask(mGoalAuton);
	//liftTarget = LIFT_MID;
	while(!moGoIsUp); // Waits for mGoal to go up
}


task stackCone1()
{
	// Pre-Condition: Cone is already in the intake
	// Post-Condition: Cone is placed onto the mobile goal

	// Steps:
	// 1 - Intake Runs at INTAKE_HOLD power + extra (because robot will be moving)
	// 2 - Autostack function runs
	// 3 - Lift moves out of the way in order for the robot to be able to score the goal.

	// 1
	motor[intake] = 100;

  // 2
	forwardNonPID(75, 40);

	cones = 1;
	runAutoStackAuton(conesHeight[cones], coneDown[cones])
	cones++;

  // 3
	liftTarget = LIFT_MIN + 200;
	startTask(lLiftPID);
	barIsUp = true;
}

void grabCone()
{
	// Pre-condition: Mobile goal is already in the MoGo intake and there is a cone on it
	// Post-condition: There is a cone in the intake and the task stackCone is running

	// Steps:
  // 1 - Stops task liftPID and AutoStack takes over for the lift
	// 2 - Drives forward to align with cone
  // 3 - Runs intake
	// 4 - Runs the drive forward to be on top of the cone
  // 5 - Moves the lift down to intake the cone
  // 6 - Starts cone stack task

  // 1
  stopTask(lLiftPID);

	// 2
	forwardNonPID(25, 40);

  // 3
  motor[intake] = 100;

	// 4
  forwardNonPID(100, 50);

  // 5
	motor[lLift] = motor[rLift] = -100;
	while(SensorValue[liftPot] > LIFT_MIN) {}
	motor[lLift] = motor[rLift] = 0 ;

  // 6
	startTask(stackCone1);
	sleep(1000);
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

  //turnTo(0); // 1
	backward(distBack - 200); // 2
  if(isRed) right(450); else left (450); // 3
	backward(730); // 4
	if(isRed) right(900); else left (900); // 5
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
  //startTask(mGoalAuton);
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
