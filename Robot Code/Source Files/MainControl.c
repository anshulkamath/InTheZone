// Stop recursive includes
#ifndef DRIVER_CONTROL_H
#define DRIVER_CONTROL_H

#include "Variables.c"

task controller()
{
	while (true)
	{
		// Added toggles for all aspects of the robot so that they could be shut off one at a time
		// since they are no longer tasks (you can no longer "stopTask()")

		// Drive
		if (driveIsActive)
		{
			lDrivePwr = vexRT[Ch3];
			rDrivePwr = vexRT[Ch2];

			// Introduces deadzone
			if (abs(lDrivePwr) < 5)
				lDrivePwr = 0;
			else if (abs(rDrivePwr) < 5)
				rDrivePwr = 0;

			motor[leftB] = motor[leftF] = lDrivePwr;
			motor[rightB] = motor[rightF] = rDrivePwr;
		}

		// Mobile Goal
		if (moGoIsManual)
		{
			if (moGoIsActive)
			{
				if (vexRT[Btn7U])
				{
						mGoalPwr = 100;
						moGoIsUp = false;
				}
				else if (vexRT[Btn7D])
				{
					if (SensorValue(moGoPot) < MOGO_UP - 300)
						mGoalPwr = -100;
					else if (SensorValue(moGoPot) < MOGO_UP)
						mGoalPwr = -40;
					else
						mGoalPwr = 0;

					moGoIsUp = true;
				}
				else if (moGoIsUp)
				{
				/*	if (SensorValue(moGoPot) < MOGO_UP - 200)
						mGoalPwr = -30;
					else if (SensorValue(moGoPot) > MOGO_UP + 200)
						mGoalPwr = 30;
					else
						mGoalPwr = 0;*/
						mGoalPwr = 0;
				}
				else
					mGoalPwr = 0;

				// Setting mobile goal motor power
				motor[moGo] = mGoalPwr;
			}
		}
		else
		{
			if (moGoIsActive)
			{
				if (vexRT[Btn7U])
					moGoIsUp = true;
				else if (vexRT[Btn7D] && cones < 9)
					moGoIsUp = false;
				else if (vexRT[Btn7D] && cones >= 9)
					place();
			}
		}

		// Lift
		if (liftIsActive)
		{
			if(vexRT[Btn6U])
				lLiftPwr = rLiftPwr = 100;
			else if(vexRT[Btn6D])
				lLiftPwr = rLiftPwr = -100;
			else
			{
				if(SensorValue(liftPot) > LIFT_MIN + 100)
					lLiftPwr = rLiftPwr = -2;
				else
					lLiftPwr = rLiftPwr = -10;
			}

			motor[lLift] = lLiftPwr;
			motor[rLift] = rLiftPwr;
		}

		// Four bar
		if (barIsManual)
		{
			if (barIsActive)
			{
				if (vexRT[Btn8U])
					barPwr = 100;
				else if (vexRT[Btn8D])
					barPwr = -100;
				else
					barPwr = 0;

				motor[barR] = motor[barL] = barPwr;
			}
		}
		else
		{
			if (barIsActive)
			{
				if (vexRT[Btn8U])
					barIsUp = true;
				else if (vexRT[Btn8D])
					barIsUp = false;
			}
		}

		// Intake
		if (intakeIsActive)
		{
			if (vexRT[Btn7L])
			{
				intakePwr = -100;
				intakeIsHolding = false;
			}
			else if (vexRT[Btn7R])
			{
				intakePwr = 100;
				intakeIsHolding = true;
			}
			else if (intakeIsHolding)
				intakePwr = INTAKE_HOLD;
			else if (!intakeIsHolding)
				intakePwr = -5    ;

			motor[intake] = intakePwr;
		}

		if(vexRT[Btn8L])
		{
			moGoIsManual = !moGoIsManual;
			while(vexRT[btn8L]);
		}
		if(vexRT[Btn8R])
		{
			//cones--;
			barIsManual = !barIsManual;
			while(vexRT[btn8R]);
		}
	}
}

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
				if (SensorValue(barPot) < BAR_UP )
					barPwr = UPPER_BAR_PWR;
				else if (SensorValue(barPot) < BAR_UP)
					barPwr = LOWER_BAR_PWR;
				else
					barPwr = HOLD_BAR_PWR;
			}
			else
			{
				if (SensorValue(barPot) > BAR_DOWN)
					barPwr = -UPPER_BAR_PWR;
				else if (SensorValue(barPot) > BAR_DOWN )
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
				if (SensorValue[moGoPot] < MOGO_UP )
					mGoalPwr = UPPER_MOGO_PWR;
				else if (SensorValue(moGoPot) < MOGO_UP)
					mGoalPwr = LOWER_MOGO_PWR;
				else
					mGoalPwr = HOLD_MOGO_PWR;
			}
			else
			{
				if (SensorValue(moGoPot) > MOGO_DOWN )
					mGoalPwr = -UPPER_MOGO_PWR;
				else if (SensorValue(moGoPot) > MOGO_DOWN )
					mGoalPwr = -LOWER_MOGO_PWR;
				else
					mGoalPwr = 0;
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

#endif
