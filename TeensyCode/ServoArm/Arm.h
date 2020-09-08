#pragma once

#include "ArmSegment.h"

class Arm
{
public:
	Arm(int smin[], int smax[], byte pin[], int pos[], int restingPosition[], int extendPosition[]);
	~Arm();

	void ReturnToRest();
	void Extend();
  int GetPosition(ArmRole role);
  void SetPosition(ArmRole role, int pos);
  int GetMin(ArmRole role);
  int GetMax(ArmRole role);
  int GetRest(ArmRole role);
  int GetExtend(ArmRole role);
  void Update();

  void OpenClaw();
  void CloseClaw();
  void Shake();

private:
	ArmSegment Base;
	ArmSegment Pivot;
	ArmSegment Wrist;
	ArmSegment Claw;
};
