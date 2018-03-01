#ifndef AUTONCONTROL_H
#define AUTONCONTROL_H

const int size = 10;
struct PControlStruct
{
  int SensorPort;
  int motorPorts[size];
  int pValue[size];
  int target;
  bool highPrecision;

};

void pControlFunction(PControlStruct control)
{
  //int currSensorValue = SensorValue[control.SensorPort];
  bool done = false;
  int rangeHigh = 20;
  int prev = 0;
  while(SensorValue[control.SensorPort] < control.target + control.highPrecision ? control.target : 0 && !done)
  {
    int cumPower = 0;

    for(int i = 0; i<size; i++)
      cumPower += control.pValue[i] * (SensorValue[control.SensorPort];

    for(int i = 0; i<size; i++)
      motor[control.motorPorts[i]] = cumPower;

    if(abs(prev - SensorValue[control.SensorPort]) < rangeHigh && abs(SensorValue[control.SensorPort] - control.target) < rangeHigh)
      done = true;

    prev = SensorValue[control.SensorPort];
  }
}
                                       
void autoTune(int degrees)
{
  bool done = false;
  float stopThres = .7;
  while(!done)
  {
    int i = 0;
    float off = 0;
    while(i<4)
    {
      while(GyroGetAngle() < degrees*stopThres)
      {
        motor[rightB] = motor[rightF] = -80*(GyroGetAngle() - degrees)/(degrees*.95)+10;
        motor[leftB] = motor[leftF] = 80*(GyroGetAngle() - degrees)/(degrees*.95)-10;

      }
          motor[rightB] = motor[rightF] = -10;
          motor[leftB] = motor[leftF] =	-10;  
      off += GyroGetAngle() - degrees;
      pre_auton();
      i++;
    }
    
    if(abs(off/4) < 10)
      done = true;
    else if(off > 0)
      stopThres -= .05;
    else
      stopThres += .05;
  }
}

#endif
