#include "Arm.h"

Arm::Arm(int smin[], int smax[], byte pin[], int pos[], int restingPosition[], int extendPosition[]):
Base( smin[ARM_BASE], smax[ARM_BASE], pin[ARM_BASE], pos[ARM_BASE], restingPosition[ARM_BASE], extendPosition[ARM_BASE], ARM_BASE), 
Pivot( smin[ARM_PIVOT], smax[ARM_PIVOT], pin[ARM_PIVOT], pos[ARM_PIVOT], restingPosition[ARM_PIVOT], extendPosition[ARM_PIVOT], ARM_PIVOT), 
Wrist( smin[ARM_WRIST], smax[ARM_WRIST], pin[ARM_WRIST], pos[ARM_WRIST], restingPosition[ARM_WRIST], extendPosition[ARM_WRIST], ARM_WRIST), 
Claw( smin[ARM_CLAW], smax[ARM_CLAW], pin[ARM_CLAW], pos[ARM_CLAW], restingPosition[ARM_CLAW], extendPosition[ARM_CLAW], ARM_CLAW)
{
}

Arm::~Arm()
{

}

void Arm::ReturnToRest()
{
	Claw.ReturnToRest();
	Wrist.ReturnToRest();
	Pivot.ReturnToRest();
	Base.ReturnToRest();
}

void Arm::Extend()
{
  Pivot.Extend();
  while(Pivot.Moving()){Update();delay(10);}
	Claw.Extend();
  while(Claw.Moving()){Update();delay(10);}
  Wrist.Extend();
  while(Wrist.Moving()){Update();delay(10);}
	Base.Extend();
  while(Base.Moving()){Update();delay(10);}
}

int Arm::GetPosition(ArmRole role)
{
  switch(role)
  {
    case ARM_BASE:
      return Base.GetPosition();
      break;
    case ARM_PIVOT:
      return Pivot.GetPosition();
      break;
    case ARM_WRIST:
      return Wrist.GetPosition();
      break;
    case ARM_CLAW:
      return Claw.GetPosition();
      break;
    default:
      return 0;
  }
}

void Arm::SetPosition(ArmRole role, int pos)
{
  switch(role)
  {
    case ARM_BASE:
      Base.SetPosition(pos);
      break;
    case ARM_PIVOT:
      Pivot.SetPosition(pos);
      break;
    case ARM_WRIST:
      Wrist.SetPosition(pos);
      break;
    case ARM_CLAW:
      Claw.SetPosition(pos);
      break;
    default:
      break;
  }
}

int Arm::GetMin(ArmRole role)
{
  switch(role)
  {
    case ARM_BASE:
      return Base.GetMin();
      break;
    case ARM_PIVOT:
      return Pivot.GetMin();
      break;
    case ARM_WRIST:
      return Wrist.GetMin();
      break;
    case ARM_CLAW:
      return Claw.GetMin();
      break;
    default:
      return 0;
      break;
  }
}

int Arm::GetMax(ArmRole role)
{
  switch(role)
  {
    case ARM_BASE:
      return Base.GetMax();
      break;
    case ARM_PIVOT:
      return Pivot.GetMax();
      break;
    case ARM_WRIST:
      return Wrist.GetMax();
      break;
    case ARM_CLAW:
      return Claw.GetMax();
      break;
    default:
      return -1;
      break;
  }  
}

int Arm::GetRest(ArmRole role)
{
  switch(role)
  {
    case ARM_BASE:
      return Base.GetRest();
      break;
    case ARM_PIVOT:
      return Pivot.GetRest();
      break;
    case ARM_WRIST:
      return Wrist.GetRest();
      break;
    case ARM_CLAW:
      return Claw.GetRest();
      break;
    default:
      return -1;
      break;
  }   
}

int Arm::GetExtend(ArmRole role)
{
  switch(role)
  {
    case ARM_BASE:
      return Base.GetExtend();
      break;
    case ARM_PIVOT:
      return Pivot.GetExtend();
      break;
    case ARM_WRIST:
      return Wrist.GetExtend();
      break;
    case ARM_CLAW:
      return Claw.GetExtend();
      break;
    default:
      return -1;
      break;
  }     
}

void Arm::Update()
{
  Base.Update();
  Pivot.Update();
  Wrist.Update();
  Claw.Update();
}

void Arm::OpenClaw()
{
  Claw.SetPosition(Claw.GetMin());
}

void Arm::CloseClaw()
{
  Claw.SetPosition(Claw.GetMax());
}

void Arm::Shake()
{
  OpenClaw();
  while(Claw.Moving()){Update();}
  delay(100);
  Wrist.SetPosition(Wrist.GetMax());
  while(Wrist.Moving()){Update();delay(10);}
  Wrist.SetPosition(Wrist.GetMin());
  while(Wrist.Moving()){Update();delay(10);}
  Wrist.ReturnToRest();
  while(Wrist.Moving()){Update();delay(10);}
}
