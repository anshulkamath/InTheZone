// Stop recursive includes
#ifndef DRIVER_CONTROL_H
#define DRIVER_CONTROL_H

#include "Variables.c"

// Sets the four-bar position
task barSet()
{
	while (true)
	{
		int lBound = 200;
		int uBound = 10;

		const int UPPER_PWR = 100;
		const int LOWER_PWR = 40;
		const int HOLD_PWR = 0;

		// Bang-bang the bar
		if (barIsUp)
		{
			if (SensorValue(barPot) < BAR_UP - lBound)
				barPwr = UPPER_PWR;
			else if (SensorValue(barPot) < BAR_UP - uBound)
				barPwr = LOWER_PWR;
			else
				barPwr = HOLD_PWR;
		}
		else
		{
			if (SensorValue(barPot) > BAR_DOWN + lBound)
				barPwr = -UPPER_PWR;
			else if (SensorValue(barPot) > BAR_DOWN + uBound)
				barPwr = -LOWER_PWR;
			else
				barPwr = -HOLD_PWR;
		}

		// Commented out because replaced in controller task
		motor[barL] = motor[barR] = barPwr;

		sleep(50);
	}
}

// Sets the mobile goal position
task moGoSet()
{
	while (true)
	{
		int lBound = 200;
		int uBound = 10;

		const int UPPER_PWR = 100;
		const int LOWER_PWR = 40;
		const int HOLD_PWR = -10;

		// Bang-bang the mobile goal
		if (moGoIsUp)
		{
			if (SensorValue[moGoPot] < MOGO_UP - lBound)
				mGoalPwr = UPPER_PWR;
			else if (SensorValue(moGoPot) < MOGO_UP - uBound)
				mGoalPwr = LOWER_PWR;
			else
				mGoalPwr = HOLD_PWR;
		}
		else
		{
			if (SensorValue(moGoPot) > MOGO_DOWN + lBound)
				mGoalPwr = -UPPER_PWR;
			else if (SensorValue(moGoPot) > MOGO_DOWN + uBound)
				mGoalPwr = -LOWER_PWR;
			else
				mGoalPwr = -HOLD_PWR;
		}

		// Commented out because replaced in controller task
		motor[moGo] = mGoalPwr;

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
