// Stop recursive includes
#ifndef DEBUG_H
#define DEBUG_H

#include "Vex_Competition_Includes.c"
#include "Variables.c"

// Datalog Function
void display(int P, int I, int D, int error, int mpwr, int targ, int sensor, int other)
{
	//writeDebugStreamLine("Function: P: %d, I: %d, D: %d, Error: %d, MPWR: %d, Target: %d",  P, I, D, error, mpwr, targ);
	datalogDataGroupStart();
	datalogAddValue( DATALOG_SERIES_0, P );
	datalogAddValue( DATALOG_SERIES_1, I );
	datalogAddValue( DATALOG_SERIES_2, D );
	datalogAddValue( DATALOG_SERIES_3,error);
	datalogAddValue( DATALOG_SERIES_4,mpwr);
	datalogAddValue( DATALOG_SERIES_5,targ);
	datalogAddValue( DATALOG_SERIES_6,sensor);
	datalogAddValue( DATALOG_SERIES_7,other);
	datalogDataGroupEnd();
}

#endif
