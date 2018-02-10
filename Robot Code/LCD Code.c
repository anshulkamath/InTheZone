const int NUM_AUTONS = 2;
const int NUM_MENUS = 4;
bool gyroIsCalibrating = false;
string mainBattery, backupBattery;

// LCD Counters
int autonCount = 0;
int lcdCount = 0;

const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;

// LCD Control Functions
void waitForPress()
{
  while(nLCDButtons == 0){}
  wait1Msec(5);
}

void waitForRelease()
{
  while(nLCDButtons != 0){}
  wait1Msec(5);
}

// LCD Functions
void autonSelector()
{
  clearLCDLine(0);
  clearLCDLine(1);

  while (bIfiRobotDisabled && nLCDButtons != centerButton)
  {
    // 0 - 20 Pt Right Red
    // 1 - 20 Pt Left Blue
    // 2 - 10 Pt Red
    // 3 - 10 Pt Blue
    // 4 - 5 Pt Red
    // 5 - 5 Pt Blue

    switch (autonCount)
    {
      // 20 Point Right Red
      case 0:
        displayLCDCenteredString(0, "20 Pt Right Red");
        displayLCDCenteredString(1, "<-        Enter       ->");
        waitForPress();
        if (nLCDButtons == rightButton)
        {
          waitForRelease();
          autonCount++;
        }
        else if (nLCDButtons == leftButton)
        {
          waitForRelease();
          autonCount = NUM_AUTONS - 1;
        }
        break;

      // 20 Point Left Blue
      case 1:
        displayLCDCenteredString(0, "20 Pt Left Blue");
        displayLCDCenteredString(1, "<-        Enter       ->");
        waitForPress();
        if (nLCDButtons == rightButton)
        {
          waitForRelease();
          autonCount++;
        }
        else if (nLCDButtons == leftButton)
        {
          waitForRelease();
          autonCount--;
        }
        break;

      // 10 Point Red
      case 2:
        displayLCDCenteredString(0, "10 Pt Red");
        displayLCDCenteredString(1, "<-        Enter       ->");
        waitForPress();
        if (nLCDButtons == rightButton)
        {
          waitForRelease();
          autonCount++;
        }
        else if (nLCDButtons == leftButton)
        {
          waitForRelease();
          autonCount--;
        }
        break;

      // 10 Point Blue
      case 3:
        displayLCDCenteredString(0, "10 Pt Blue");
        displayLCDCenteredString(1, "<-        Enter       ->");
        waitForPress();
        if (nLCDButtons == rightButton)
        {
          waitForRelease();
          autonCount++;
        }
        else if (nLCDButtons == leftButton)
        {
          waitForRelease();
          autonCount--;
        }
        break;

      // 5 Pt Red
      case 4:
        displayLCDCenteredString(0, "5 Pt Red");
        displayLCDCenteredString(1, "<-        Enter       ->");
        waitForPress();
        if (nLCDButtons == rightButton)
        {
          waitForRelease();
          autonCount++;
        }
        else if (nLCDButtons == leftButton)
        {
          waitForRelease();
          autonCount--;
        }
        break;

      // 5 Pt Blue
      case 5:
        displayLCDCenteredString(0, "5 Pt Blue");
        displayLCDCenteredString(1, "<-        Enter       ->");
        waitForPress();
        if (nLCDButtons == rightButton)
        {
          waitForRelease();
          autonCount = 0;
        }
        else if (nLCDButtons == leftButton)
        {
          waitForRelease();
          autonCount--;
        }
        break;;
    }
  }
}

void displayBattery()
{
  clearLCDLine(0);
  clearLCDLine(1);

  while (nLCDButtons != centerButton)
  {
    //Display the Primary Robot battery voltage
    displayLCDString(0, 0, "Primary: ");
    sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
    displayNextLCDString(mainBattery);

    //Display the Backup battery voltage
    displayLCDString(1, 0, "Backup: ");
    sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');    //Build the value to be displayed
    displayNextLCDString(backupBattery);
  }
}

task runLCD()
{
  bLCDBacklight = true;
  clearLCDLine(0);
  clearLCDLine(1);

  while (true)
  {
    while (gyroIsCalibrating)
    {
      displayLCDCenteredString(0, "DO NOT TOUCH");
      displayLCDCenteredString(1, "Gyro is calibrating...");
    }
    while (bIfiRobotDisabled && nLCDButtons != centerButton)
    {
      switch (lcdCount)
      {
        // Run auton switcher
        case 0:
          displayLCDCenteredString(0, "Select Autons");
          displayLCDCenteredString(1, "<-        Enter       ->");
          waitForPress();
          if (nLCDButtons == rightButton)
          {
            waitForRelease();
            lcdCount++;
          }
          else if (nLCDButtons == leftButton)
          {
            waitForRelease();
            lcdCount = NUM_MENUS - 1;
          }
          break;

        // Toggle Bar Manual
        case 1:
          if (barIsManual)
            displayLCDCenteredString(0, "Set Bar Auto");
          else
            displayLCDCenteredString(0, "Set Bar Manual");
          displayLCDCenteredString(1, "<-        Enter       ->");
          waitForPress();
          if (nLCDButtons == rightButton)
          {
            waitForRelease();
            lcdCount++;
          }
          else if (nLCDButtons == leftButton)
          {
            waitForRelease();
            lcdCount--;
          }
          break;

        // Toggle Mobile Goal Manual
        case 2:
          if (barIsManual)
            displayLCDCenteredString(0, "Set MoGo to Auto");
          else
            displayLCDCenteredString(0, "Set MoGo to Manu");
          displayLCDCenteredString(1, "<-        Enter       ->");
          waitForPress();
          if (nLCDButtons == rightButton)
          {
            waitForRelease();
            lcdCount++;
          }
          else if (nLCDButtons == leftButton)
          {
            waitForRelease();
            lcdCount--;
          }
          break;

        // Display Battery Voltage
        case 3:
          displayLCDCenteredString(0, "Show Battery Voltage");
          displayLCDCenteredString(1, "*Press enter to exit*");
          waitForPress();
          if (nLCDButtons == rightButton)
          {
            waitForRelease();
            lcdCount = 0;
          }
          else if (nLCDButtons == leftButton)
          {
            waitForRelease();
            lcdCount--;
          }
          break;
        }

      switch (lcdCount)
      {
        case 0:
          autonSelector();
          break;
        case 1:
          barIsManual = !barIsManual;
          break;
        case 2:
          moGoIsManual = !moGoIsManual;
          break;
        case 3:
          displayBattery();
          break;
      }
    }

    if (!bIfiRobotDisabled)
    {
      clearLCDLine(0);
      clearLCDLine(1);

      //Display the Primary Robot battery voltage
      displayLCDString(0, 0, "Primary: ");
      sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
      displayNextLCDString(mainBattery);

      //Display the Backup battery voltage
      displayLCDString(1, 0, "Backup: ");
      sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');    //Build the value to be displayed
      displayNextLCDString(backupBattery);
    }
  }
}

// Pre-Auton
void pre_auton()
{
    bStopTasksBetweenModes = true;
    startTask(runLCD);

    // Initializes the cones arrays
    initConeVals();

    // Calibrates Gyroscope
    gyroIsCalibrating = true;
    SensorType[in4] = sensorNone;
    wait1Msec(1000);
    SensorType[in4] = sensorGyro;
    wait1Msec(2000);
    SensorFullCount[in4] = 3600 * 100;
    SensorScale[in4] = 130;
    gyroIsCalibrating = false;
}

task autonomous()
{
    clearDebugStream();
    datalogClear();

    // 0 - 20 Pt Right Red
    // 1 - 20 Pt Left Blue
    // 2 - 10 Pt Red
    // 3 - 10 Pt Blue
    // 4 - 5 Pt Red
    // 5 - 5 Pt Blue

    switch(autonCount)
    {
      case 0:
        matchAutonRightRed();
        break;
      case 1:
        matchAutonLeftBlue();
        break;
      case 2:
        matchAuton10PtRed();
      case 3:
        matchAuton10PtBlue();
        break;
      case 4:
        matchauton5PtRed();
        break;
      case 5:
        matchAuton5PtBlue();
        break;
    }
}

task usercontrol()
{
  
}
