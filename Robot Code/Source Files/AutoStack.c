// Stop recursive includes
#ifndef AUTOSTACK_H
#define AUTOSTACK_H

#include "Variables.c"

// Made it a task so it will run concurrently with the autostack function
task releaseCone()
{
	motor[intake] = -100;
	sleep(250);
	motor[intake] = 0;
}


// Vestige
void initConeVals()
{
	conesHeight[0] = LIFT_MIN;
	conesHeight[1] = 1125;
	conesHeight[2] = 1285;
	conesHeight[3] = 1593 + 181;
	conesHeight[4] = 1903;
	conesHeight[5] = 1630;
	conesHeight[6] = conesHeight[5] + 191;
	conesHeight[7] = 2082;
	conesHeight[8] = 2251;
	conesHeight[9] = 0;
	conesHeight[10] = 2220;

	coneDown[0] = LIFT_MIN;
	coneDown[1] = 1032;
	coneDown[2] = 1051;
	coneDown[3] = 1544 + 181;
	coneDown[4] = 1774;
	coneDown[5] = 1440;
	coneDown[6] = coneDown[5] + 252;
	coneDown[7] = 2020;
	coneDown[8] = 2091;
	coneDown[9] = 0;
	coneDown[10] = 2000;
}

void autoConeInitVals()
{
	// Initializing the lift values for autostack
	conesHeight[0] = LIFT_MIN;
	for (int i = 1; i < size; i++)
		conesHeight[i] = LIFT_MIN + (122 * i);

	// Initializing the lift values for autostack release
	// conesDown[0] is the same as conesHeight[0] beacause it is the bottom of the lift
	coneDown[0] = LIFT_MIN;
	for (int i = 1; i < size; i++)
		coneDown[i] = conesHeight[i] - 30*i;
}

void runAutoStackOneCone(bool driver)
{
	barIsUp = true;
	while(SensorValue[barPot] > BAR_UP) {}
	startTask(releaseCone);
	sleep(450);
	barIsUp = false;

}
void runAutoStack(int height, int down, bool driver)
{
	// Moves the lift up to the height
	motor[lLift] = motor[rLift] = 100;
	while(SensorValue[liftPot] < height) {}
	motor[lLift] = motor[rLift] = 0;

	// Moves the bar up
	barIsUp = true;
	while(SensorValue[barPot] > BAR_UP) {}
	//startTask(releaseCone);
	//sleep(250);
	// Moves the lift down to stack
	motor[lLift] = motor[rLift] = -76;
	bool started = false;
 while(SensorValue[liftPot] > down + 30)
	{
		// Runs the intake out as the lift is going down
		if (SensorValue(liftPot) < down+70 && !started)
		{

			startTask(releaseCone);
			started = true;
		}
	}
	if(!started) startTask(releaseCone);

	motor[lLift] = motor[rLift] = 0;

	// Moves lift up to get out of stack
	motor[lLift] = motor[rLift] = 120;
	while(SensorValue[liftPot] <  height) {}
	motor[lLift] = motor[rLift] = 0;

	// Moves the bar to bottom position
	barIsUp = false;
	while(SensorValue[barPot] < BAR_DOWN) {} // Can make the value a little higher to make autostack quicker


	if(!driver)
	{
		// Residual of the moveDownField function

		// Moves the lift to field position
		motor[lLift] = motor[rLift] = -100;
		while(SensorValue[liftPot] > LIFT_MIN + 200) {}
		motor[lLift] = motor[rLift] = -80;
		while(SensorValue[liftPot] > LIFT_MIN+50) {}
		motor[lLift] = motor[rLift] = 0;
	}
	else
	{
		// Residual of the moveDownDriver function

		// Moves lift down to driver load stack
		motor[lLift] = motor[rLift] = -100;
		while(SensorValue[liftPot] > LIFT_DRIVER + 200) {}
		motor[lLift] = motor[rLift] = -65;
		while(SensorValue[liftPot] > LIFT_DRIVER+50) {}
		motor[lLift] = motor[rLift] = 0;
	}
}

void runAutoStackAuton(int height, int down)
{
	// Moves the lift up to the height
	motor[lLift] = motor[rLift] = 100;
	liftUpAuton = true;
	while(SensorValue[liftPot] < height) {}
	motor[lLift] = motor[rLift] = 0;

	// Moves the bar up
	barIsUp = true;
	while(SensorValue[barPot] > BAR_UP) {}
	//startTask(releaseCone);
	//sleep(250);
	// Moves the lift down to stack
	motor[lLift] = motor[rLift] = -76;
 while(SensorValue[liftPot] > down)
	{
		// Runs the intake out as the lift is going down
		if (SensorValue(liftPot) < down+60)
			startTask(releaseCone);

	}
	motor[lLift] = motor[rLift] = 0;

	// Moves lift up to get out of stack
	motor[lLift] = motor[rLift] = 60;
	while(SensorValue[liftPot] <  height) {}
	motor[lLift] = motor[rLift] = 0;
}


task startAutoStack()
{
	if (isFieldControl)
	{
		autoStackIsOn = true;
		if(cones < size)
		{
		//	intakeCone(1);
			if(cones == 0)
				runAutoStackOneCone(false);
			else
				runAutoStack(conesHeight[cones], coneDown[cones], false);
			cones++;
		}
		autoStackIsOn = false;
	}
	else
	{
		autoStackIsOn = true;
		if(cones < size)
		{
			intakeCone(1);
			runAutoStack(conesHeight[cones], coneDown[cones], true);
			cones++;
		}
		autoStackIsOn = false;
	}
}

task autoStackControl()
{
	while (true)
	{
		if (vexRT[Btn8L])
			isFieldControl = true;
		else if (vexRT[Btn8R])
			isFieldControl = false;

		if (!vexRT[Btn8LXmtr2] || !vexRT[Btn8UXmtr2] || !vexRT[Btn8DXmtr2] || !vexRT[Btn8RXmtr2])
		{
			if (vexRT[Btn7LXmtr2])
				cones = 1;
			else if (vexRT[Btn7UXmtr2])
				cones = 2;
			else if (vexRT[Btn7DXmtr2])
				cones = 3;
			else if (vexRT[Btn7RXmtr2])
				cones = 4;
		}
		else if (vexRT[Btn8LXmtr2])
		{
			if (vexRT[Btn7LXmtr2])
				cones = 5;
			else if (vexRT[Btn7UXmtr2])
				cones = 6;
			else if (vexRT[Btn7DXmtr2])
				cones = 7;
			else if (vexRT[Btn7RXmtr2])
				cones = 8;
		}
		else if (vexRT[Btn8RXmtr2])
		{
			if (vexRT[Btn7LXmtr2])
				cones = 9;
			else if (vexRT[Btn7UXmtr2])
				cones = 10;
			else if (vexRT[Btn7DXmtr2])
				cones = 11;
			else if (vexRT[Btn7RXmtr2])
				cones = 12;
		}

		if (vexRT[Btn5UXmtr2])
			cones = 0;

		if (vexRT[Btn6UXmtr2])
		{
			while (vexRT[Btn6UXmtr2]) {}
			cones++;
		}
		else if (vexRT[Btn6DXmtr2])
		{
			while (vexRT[Btn6DXmtr2]) {}
			cones--;
		}

		sleep (50);
	}
}

task autoStack()
{
	startTask(autoStackControl);
	bool tasksStarted = true;
	while(true)
	{
		if (vexRT[Btn5U] && !autoStackIsOn) // Runs AutoStack
		{
			tasksStarted = false;

			//stopTask(stabilizeLift);
      intakeIsActive = false;
      barIsActive = false;
      liftIsActive = false;


			startTask(startAutoStack);
		}
		else if (vexRT[Btn5D] && autoStackIsOn) // Cancels AutoStack
		{
			stopTask(startAutoStack);

			autoStackIsOn = false;
		}
		else if (!tasksStarted && !autoStackIsOn) // Restarts all tasks in the event that they are not running
		{
			tasksStarted = true;

			//startTask(stabilizeLift);
      intakeIsActive = true;
      barIsActive = true;
      liftIsActive = true;

		}

		sleep (100);
	}
}

#endif
