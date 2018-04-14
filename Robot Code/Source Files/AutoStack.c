// Stop recursive includes
#ifndef AUTOSTACK_H
#define AUTOSTACK_H

#include "Variables.c"
#include "AutonControl.c"

// Made it a task so it will run concurrently with the autostack function
task releaseCone()
{
	motor[intake] = -100;
	sleep(250);
	motor[intake] = -25;
}


void runAutoStack(int height, int down, int prevConeBottom, bool driver)
{
	// Moves the lift up to the height
	motor[lLift] = motor[rLift] = 100;
	while(SensorValue[liftPot] < prevConeBottom) {}
	//motor[lLift] = motor[rLift] = 0;
	barIsUp = true;
	// Moves the bar up


//	motor[lLift] = motor[rLift] = 100;
	while(SensorValue[liftPot] < height) {}
	motor[lLift] = motor[rLift] = 0;

	while(SensorValue[barPot] > BAR_UP+100) {}


	//startTask(releaseCone);
	//sleep(250);
	// Moves the lift down to stack
	motor[lLift] = motor[rLift] = -100;
	bool started = false;
 while(SensorValue[liftPot] > down + 30)
	{
		// Runs the intake out as the lift is going down
	}
	startTask(releaseCone);

	motor[lLift] = motor[rLift] = 0;
	//while(true);
//	while(true);
	sleep(100);
	// Moves lift up to get out of stack
	motor[lLift] = motor[rLift] = 100;
	while(SensorValue[liftPot] <  height) {}
	motor[lLift] = motor[rLift] = 0;

	// Moves the bar to bottom position
	barIsUp = false;
	while(SensorValue[barPot] < BAR_DOWN - 2000) {} // Can make the value a little higher to make autostack quicker


	if(!driver)
	{
		// Residual of the moveDownField function

		// Moves the lift to field position
		motor[lLift] = motor[rLift] = -100;
		while(SensorValue[liftPot] > 1590 + 600) {}
		motor[lLift] = motor[rLift] = -40;
		while(SensorValue[liftPot] > 1590+100) {}
		motor[lLift] = motor[rLift] = 0;
	}
	else
	{
		// Residual of the moveDownDriver function

		// Moves lift down to driver load stack
		motor[lLift] = motor[rLift] = -100;
		while(SensorValue[liftPot] > LIFT_DRIVER + 50) {}
		motor[lLift] = motor[rLift] = 0;
		//while(SensorValue[liftPot] > LIFT_DRIVER+50) {}
		//motor[lLift] = motor[rLift] = 0;
	}
}


// Vestige
void initConeVals()
{
	conesHeight[0] = 1400;
	conesHeight[1] = 1460;
	conesHeight[2] = 1580;
	conesHeight[3] = 1700;
	conesHeight[4] = 1790;
	conesHeight[5] = 1900;
	conesHeight[6] = 2060;
	conesHeight[7] = 2130;
	conesHeight[8] = 2270;
	conesHeight[9] = 2370;
	conesHeight[10] = 2550;
	conesHeight[11] = 2700;
	conesHeight[12] = LIFT_MAX;

	coneDown[0] = 1300;
	coneDown[1] = 1340;
	coneDown[2] = 1370;
	coneDown[3] = 1500;
	coneDown[4] = 1640;
	coneDown[5] = 1765;
	coneDown[6] = 1815;
	coneDown[7] = 1960;
	coneDown[8] = 1990;
	coneDown[9] = 2155;
	coneDown[10] = 2180;
	coneDown[11] = 2390;
	coneDown[12] = 2550;
}


task startAutoStack()
{
	if(cones < 0) cones = 0;
	if (isFieldControl)
	{
		autoStackIsOn = true;
		if(cones < size)
		{
		//	intakeCone(1);
			{
				intakeIsActive = false;
				if(cones < 3)
					runAutoStack(conesHeight[cones], coneDown[cones], coneDown[cones], false);
				else
					runAutoStack(conesHeight[cones], coneDown[cones], coneDown[cones-3], false);
				cones++;
				intakeIsActive = true;
			}
		}
		autoStackIsOn = false;
	}
	else
	{
		autoStackIsOn = true;
		if(cones < size)
		{
			intakeCone(1);
		//	runAutoStack(conesHeight[cones], coneDown[cones], true);
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
intakeIsActive = true;
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
