#include "Arm.h"
#include <i2c_driver_wire.h>

#define SLAVE_ADDRESS 0x7

//Set up Arm
int sMin[ARM_LAST] = {112, 0, 30, 0};
int sMax[ARM_LAST] = {150, 170, 150, 50};
byte pin[ARM_LAST] = {0,1,2,3};
int pos[ARM_LAST] = {150,151,90,0};
int restingPosition[ARM_LAST] = {150,170,90,0};
int extendedPosition[ARM_LAST] = {112,80,90,50};
Arm arm(sMin,sMax,pin,pos,restingPosition,extendedPosition);

//Helper Functions
void processCommand(int howMany);

/////////////////////////////
/////////////SETUP///////////
/////////////////////////////
void setup() {
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(processCommand); // register event
  arm.ReturnToRest();
}

/////////////////////////////
/////////////LOOP////////////
/////////////////////////////
void loop() {
  arm.Update();
  delay(10);
}

/////////////////////////////
///////////HELPERS///////////
/////////////////////////////
void processCommand(int howMany)
{
  char c;
  c = Wire.read();
  Serial.print(c);

  int newPos;
  switch(c)
  {
    case 'r':
      arm.ReturnToRest();
      break;
    case 'e':
      arm.Extend();
      break;
    case 's':
      arm.Shake();
      break;
    case 'b':
//      newPos = Serial.parseInt();
//      arm.SetPosition(ARM_BASE,newPos);
      break;
    case 'p':
    {
      char comm = Wire.read();
      Serial.print(comm);
      if(comm == 'u')
      {
        arm.SetPosition(ARM_PIVOT,0);
      } else
      {
        arm.SetPosition(ARM_PIVOT,arm.GetRest(ARM_PIVOT));
      }
      break;
    }
//      newPos = Serial.parseInt();
//      arm.SetPosition(ARM_PIVOT,newPos);
      break;
    case 'w':
//      newPos = Serial.parseInt();
//      arm.SetPosition(ARM_WRIST,newPos);
      break;
    case 'c':
    {
      char seg = Wire.read();
      Serial.print(seg);
      if(seg == 'o'){arm.OpenClaw();}
      else if(seg == 'c'){arm.CloseClaw();}
      break;
    }
    case 'm':
    {
      char seg = Wire.read();
      int val = 0;
      char digit[1];
      while(Wire.available())
      {
        digit[0] = Wire.read();
        val = (val*10) + atoi(digit);
      }
      newPos = val;
      Serial.print(seg);
      Serial.print(newPos);
      switch(seg)
      {
        case 'b':
          arm.SetPosition(ARM_BASE,newPos);
          break;
        case 'p':
          arm.SetPosition(ARM_PIVOT,newPos);
          break;
        case 'w':
          arm.SetPosition(ARM_WRIST,newPos);
          break;
        case 'c':
          arm.SetPosition(ARM_CLAW,newPos);
          break;
      }
    }
  }
  Serial.println("");
}
