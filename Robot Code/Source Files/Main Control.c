// Stop recursive includes
#ifndef DRIVER_CONTROL_H
#define DRIVER_CONTROL_H

#include "Variables.c"

// Sets the four-bar position

task robotControl()
{
	while (true)
	{
		int lBoundBar = 200;
		int uBoundBar = 10;

		const int UPPER_BAR_PWR = 100;
		const int LOWER_BAR_PWR = 40;
		const int HOLD_BAR_PWR = 0;

		int lBoundMoGo = 200;
		int uBoundMoGo = 10;

		const int UPPER_MOGO_PWR = 100;
		const int LOWER_MOGO_PWR = 40;
		const int HOLD_MOGO_PWR = -10;

		// Four bar
		if (!barIsManual)
		{
			if (barIsUp)
			{
				if (SensorValue(barPot) < BAR_UP - lBound)
					barPwr = UPPER_BAR_PWR;
				else if (SensorValue(barPot) < BAR_UP - uBound)
					barPwr = LOWER_BAR_PWR;
				else
					barPwr = HOLD_BAR_PWR;
			}
			else
			{
				if (SensorValue(barPot) > BAR_DOWN + lBound)
					barPwr = -UPPER_BAR_PWR;
				else if (SensorValue(barPot) > BAR_DOWN + uBound)
					barPwr = -LOWER_BAR_PWR;
				else
					barPwr = -HOLD_BAR_PWR;
			}

			motor[barL] = motor[barR] = barPwr;
		}

		// Mobile Goal
		if (!moGoIsManual)
		{
			if (moGoIsUp)
			{
				if (SensorValue[moGoPot] < MOGO_UP - lBound)
					mGoalPwr = UPPER_MOGO_PWR;
				else if (SensorValue(moGoPot) < MOGO_UP - uBound)
					mGoalPwr = LOWER_MOGO_PWR;
				else
					mGoalPwr = HOLD_MOGO_PWR;
			}
			else
			{
				if (SensorValue(moGoPot) > MOGO_DOWN + lBound)
					mGoalPwr = -UPPER_MOGO_PWR;
				else if (SensorValue(moGoPot) > MOGO_DOWN + uBound)
					mGoalPwr = -LOWER_MOGO_PWR;
				else
					mGoalPwr = -HOLD_MOGO_PWR;
			}

			motor[moGo] = mGoalPwr;
		}

		sleep(50);
	}
}

// Runs intake accordingly
void intakeCone(int pos)
{
	if (pos == 1)
	{
		motor[intake] = 100;
		sleep(500);
		motor[intake] = 30;
	}
	else if (pos == 0)
	{
		motor[intake] = -100;
		sleep(250);
		motor[intake] = 0;
	}
}

// Place mobile goal
void place()
{
	// Check to make sure there aren't conflicting motor power sets with task Controller
	if (!barIsManual)
		stopTask(barSet);

	moGoIsUp = false;
	while (SensorValue(moGoPot) > MOGO_DOWN)
		motor[barL] = motor[barR] = -30;

	intakeCone(0);

	if (!barIsManual)
		startTask(barSet);

	barIsUp = true;
}

#endif
