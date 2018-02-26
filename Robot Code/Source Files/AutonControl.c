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
