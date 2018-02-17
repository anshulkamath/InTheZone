// Stop recursive includes
#ifndef LCD_CODE_H
#define LCD_CODE_H

#include "Vex_Competition_Includes.c"
#include "Variables.c"

// LCD Control Functions
void waitForPress()
{
  while(nLCDButtons == 0){sleep(100);}
  wait1Msec(5);
}

void waitForRelease()
{
  while(nLCDButtons != 0){sleep(100);}
  wait1Msec(5);
}

// LCD Functions
void redRightSelector()
{
	int tempCount = 0;
	int tempNum = -1;
	while(tempNum == -1)
	{
		switch (tempCount)
		{
	      case 0:
	        displayLCDCenteredString(0, "20 Pt Right Red");
	        displayLCDCenteredString(1, "<- Enter ->");
	        waitForPress();
	        if (nLCDButtons == rightButton)
	        {
	          waitForRelease();
	          tempCount++;
	        }
	        else if (nLCDButtons == leftButton)
	        {
	          waitForRelease();
	          //tempCount = 1;
	        }
	        tempNum = 0;
	        break;
	      case 1:
	        displayLCDCenteredString(0, "10 Pt Red");
	        displayLCDCenteredString(1, "<- Enter ->");
	        waitForPress();
	        if (nLCDButtons == rightButton)
	        {
	          waitForRelease();
	          tempCount++;
	        }
	        else if (nLCDButtons == leftButton)
	        {
	          waitForRelease();
	          tempCount--;
	        }
	        tempNum = 2;
	        break;
	      case 2:
	        displayLCDCenteredString(0, "5 Pt Red");
	        displayLCDCenteredString(1, "<- Enter ->");
	        waitForPress();
	        if (nLCDButtons == rightButton)
	        {
	          waitForRelease();
	          //tempCount++;
	        }
	        else if (nLCDButtons == leftButton)
	        {
	          waitForRelease();
	          tempCount--;
	        }
	        tempNum = 4;
	        break;
		}
	}
	autonCount = tempCount;
}

void redLeftSelector()
{
	int tempCount = 0;
	int tempNum = 0;
	while(tempNum == 0)
	{
		switch (tempCount)
		{
	      case 0:
	        displayLCDCenteredString(0, "10 Pt Red");
	        displayLCDCenteredString(1, "<- Enter ->");
	        waitForPress();
	        if (nLCDButtons == rightButton)
	        {
	          waitForRelease();
	          tempCount++;
	        }
	        else if (nLCDButtons == leftButton)
	        {
	          waitForRelease();
	         // tempCount--;
	        }
	        tempNum = 2;
	        break;
	      case 1:
	        displayLCDCenteredString(0, "5 Pt Red");
	        displayLCDCenteredString(1, "<- Enter ->");
	        waitForPress();
	        if (nLCDButtons == rightButton)
	        {
	          waitForRelease();
	         // tempCount++;
	        }
	        else if (nLCDButtons == leftButton)
	        {
	          waitForRelease();
	          tempCount--;
	        }
	        tempNum = 4;
	        break;
		}
	}
	autonCount = tempNum;
}

void blueRightSelector()
{
	int tempCount = 0;
	int tempNum = 0;
	while(tempNum == 0)
	{
		switch (tempCount)
		{
	      case 0:
	        displayLCDCenteredString(0, "10 Pt Blue");
	        displayLCDCenteredString(1, "<- Enter ->");
	        waitForPress();
	        if (nLCDButtons == rightButton)
	        {
	          waitForRelease();
	          tempCount++;
	        }
	        else if (nLCDButtons == leftButton)
	        {
	          waitForRelease();
	         // tempCount--;
	        }
	        tempNum = 3;
	        break;
	      case 1:
	        displayLCDCenteredString(0, "5 Pt Blue");
	        displayLCDCenteredString(1, "<- Enter ->");
	        waitForPress();
	        if (nLCDButtons == rightButton)
	        {
	          waitForRelease();
	          //tempCount++;
	        }
	        else if (nLCDButtons == leftButton)
	        {
	          waitForRelease();
	          tempCount--;
	        }
	        tempNum = 5;
	        break;
		}
		autonCount = tempNum;
	}
}

void blueLeftSelector()
{
		int tempCount = 0;
		int tempNum = 0;
	while(tempNum == 0)
	{

		switch (tempCount)
		{
	      case 0:
	        displayLCDCenteredString(0, "20 Pt Left Blue");
	        displayLCDCenteredString(1, "<- Enter ->");
	        waitForPress();
	        if (nLCDButtons == rightButton)
	        {
	          waitForRelease();
	          tempCount++;
	        }
	        else if (nLCDButtons == leftButton)
	        {
	          waitForRelease();

	        }
	        tempNum = 1;
	        break;
       case 1:
	        displayLCDCenteredString(0, "10 Pt Blue");
	        displayLCDCenteredString(1, "<- Enter ->");
	        waitForPress();
	        if (nLCDButtons == rightButton)
	        {
	          waitForRelease();
	          tempCount++;
	        }
	        else if (nLCDButtons == leftButton)
	        {
	          waitForRelease();
	          tempCount--;
	        }
	        tempNum = 3;
	        break;
	      case 2:
	        displayLCDCenteredString(0, "5 Pt Blue");
	        displayLCDCenteredString(1, "<- Enter ->");
	        waitForPress();
	        if (nLCDButtons == rightButton)
	        {
	          waitForRelease();
	          //tempCount++;
	        }
	        else if (nLCDButtons == leftButton)
	        {
	          waitForRelease();
	          tempCount--;
	        }
	        tempNum = 5;
	        break;
		}
	}
	autonCount = tempNum;
}
void autonSelector()
{
  clearLCDLine(0);
  clearLCDLine(1);
 waitForRelease();
  displayLCDCenteredString(0, "Select Color");
  displayLCDCenteredString(1, "Red   Blue");
  while (color == -1 || side == -1)
  {
  	if(color != -1)
  	{
  		displayLCDCenteredString(0, "Select Side");
  		displayLCDCenteredString(1, "Left   Right");
  	}
    waitForPress();
		if(color == -1)
		{
      if (nLCDButtons == rightButton)
      {
        waitForRelease();
        color = 1;
      }
      else if (nLCDButtons == leftButton)
      {
        waitForRelease();
      	color = 0;
    	}
    }else if(side == -1)
    {
      if (nLCDButtons == rightButton)
      {
        waitForRelease();
        side = 1;
        // Color check
        if(color == 0)
        {
        	redRightSelector();
        }else
        {
        	blueRightSelector();
        }
      }
      else if (nLCDButtons == leftButton)
      {
        waitForRelease();
      	side = 0;
      	if(color == 0)
      	{
      		redLeftSelector();
      		break;
      	}else
      	{
      		blueLeftSelector();
      		break;
      	}
    	}
    }
  	waitForRelease();
  	wait10Msec(50);
    // 0 - 20 Pt Right Red
    // 1 - 20 Pt Left Blue
    // 2 - 10 Pt Red
    // 3 - 10 Pt Blue
    // 4 - 5 Pt Red
    // 5 - 5 Pt Blue
    /*switch (autonCount)
    {
      // 20 Point Right Red


      // 20 Point Left Blue

      // 10 Point Red


      // 10 Point Blue


      // 5 Pt Red


      // 5 Pt Blue
      case 5:
        displayLCDCenteredString(0, "5 Pt Blue");
        displayLCDCenteredString(1, "<- Enter ->");
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
    }*/
    sleep(100);
  }
  displayLCDCenteredString(0, "Auton Selected");
  clearLCDLine(1);
  lcdCount = 1;
  side = -1;
  color = -1;
  waitForRelease();
  wait10Msec(150);

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
    sleep(100);
  }
  lcdCount = 0;
  waitForRelease();
  wait10Msec(50);
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
      displayLCDCenteredString(1, "Gyro calibrating");
    }
    while ( true )
    {
      switch (lcdCount)
      {
        // Run auton switcher
        case 0:
          displayLCDCenteredString(0, "Select Autons");
          displayLCDCenteredString(1, "<- Enter ->");
          waitForPress();
          if (nLCDButtons == rightButton)
          {
            waitForRelease();
            lcdCount++;
          }
          else if (nLCDButtons == leftButton)
          {
            waitForRelease();
             sleep(500);

            lcdCount = NUM_MENUS - 1;
          }else if(nLCDButtons == centerButton)
          {
          	centerPressed = true;
          }
          writeDebugStreamLine("Here");
          break;

        // Toggle Bar Manual
        case 1:
          if (barIsManual)
            displayLCDCenteredString(0, "Set Bar Auto");
          else
            displayLCDCenteredString(0, "Set Bar Manual");
          displayLCDCenteredString(1, "<- Enter ->");
          waitForPress();
          if (nLCDButtons == rightButton)
          {
            waitForRelease();
            lcdCount++;
          }
          else if (nLCDButtons == leftButton)
          {
            waitForRelease();
            sleep(500);
            lcdCount--;
          }
          else if(nLCDButtons == centerButton)
          {
            waitForRelease();
          	centerPressed = true;
          }
          break;

        // Toggle Mobile Goal Manual
        case 2:
          if(moGoIsManual)
            displayLCDCenteredString(0, "Set MoGo to Auto");
          else
            displayLCDCenteredString(0, "Set MoGo to Manu");
          displayLCDCenteredString(1, "<- Enter ->");
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
          else if(nLCDButtons == centerButton)
          {
            waitForRelease();
          	centerPressed = true;
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
          else if(nLCDButtons == centerButton)
          {
            waitForRelease();
          	centerPressed = true;
          }

          break;
      }

      if(centerPressed)
			{
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

	    if(centerPressed == 1 && lcdCount == 0) autonSelector();
	    if(lcdCount == 3) displayBattery();

      centerPressed = false;
    }

    if (false)
    {
      //clearLCDLine(0);
      //clearLCDLine(1);

      //Display the Primary Robot battery voltage
      displayLCDString(0, 0, "Primary: ");
      sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
      displayNextLCDString(mainBattery);

      //Display the Backup battery voltage
      displayLCDString(1, 0, "Backup: ");
      sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');    //Build the value to be displayed
      displayNextLCDString(backupBattery);
    }
    sleep(100);
  }
}

#endif
