// Stop recursive includes
#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#include "Variables.c"
#include "Autonomous Functions.c"

// Naming conventions: "matchAuton_COLOR_PTVALUE"

void matchAuton_RED_24()
{
  deploy();
  grabMogo();
	grabMGoal();
  grabCone();
  scoreGoal20(true, ONE_CONE);
}

void matchAuton_BLUE_24()
{
  deploy();
  grabMogo();
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
  scoreGoal5(false, NO_CONES);
}

void matchAuton_BLUE_7()
{
  deploy();
  grabMGoal();
  scoreGoal5(true, NO_CONES);
}

task autonomous()
{
    clearDebugStream();
    datalogClear();
    stopTask(runLCD);
    clearLCDLine(0);
    clearLCDLine(1);

    // 0 - 20 Pt Right Red
    // 1 - 20 Pt Left Blue
    // 2 - 10 Pt Red
    // 3 - 10 Pt Blue
    // 4 - 5 Pt Red
    // 5 - 5 Pt Blue

    switch(autonCount)
    {
      case -1:
        break;
      case 0:
        matchAuton_RED_22();
        break;
      case 1:
        matchAuton_BLUE_22();
        break;
      case 2:
        matchAuton_RED_12();
      case 3:
        matchAuton_BLUE_12();
        break;
      case 4:
        matchAuton_RED_7();
        break;
      case 5:
        matchAuton_BLUE_7();
        break;
    }
}

#endif
