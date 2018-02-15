// Stop recursive includes
#ifndef USER_CONTROL_TASKS_H
#define USER_CONTROL_TASKS_H

#include "Variables.c"

task barSet()
{
	while (true)
	{
		int lBound = 200;
		int uBound = 10;

		const int UPPER_PWR = 100;
		const int LOWER_PWR = 40;
		const int HOLD_PWR = 5;

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

task moGoSet()
{
	while (true)
	{
		int lBound = 200;
		int uBound = 10;

		const int UPPER_PWR = 100;
		const int LOWER_PWR = 40;
		const int HOLD_PWR = 0;

		// Bang-bang the mobile goal
		if (moGoIsUp)
		{
			if (SensorValue[moGoPot] < MOGO_UP - lBound)
				barPwr = UPPER_PWR;
			else if (SensorValue(moGoPot) < MOGO_UP - uBound)
				barPwr = LOWER_PWR;
			else
				barPwr = HOLD_PWR;
		}
		else
		{
			if (SensorValue(moGoPot) > MOGO_DOWN + lBound)
				barPwr = -UPPER_PWR;
			else if (SensorValue(moGoPot) > MOGO_DOWN + uBound)
				barPwr = -LOWER_PWR;
			else
				barPwr = -HOLD_PWR;
		}

		// Commented out because replaced in controller task
		motor[moGo] = barPwr;

		sleep(50);
	}
}

#endif
