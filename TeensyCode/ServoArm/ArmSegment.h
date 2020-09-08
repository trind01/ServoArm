#pragma once
#include <Arduino.h>
#include <Servo.h>

enum ArmRole {ARM_BASE, ARM_PIVOT, ARM_WRIST, ARM_CLAW, ARM_LAST};

class ArmSegment
{
public:
	ArmSegment(int smin, int smax, byte pin, int pos, int restingPosition, int extendPosition, ArmRole role);
	~ArmSegment();
	void ReturnToRest();
	void Extend();
  int GetPosition();
  void SetPosition(int pos);
  int GetMin();
  int GetMax();
  int GetRest();
  int GetExtend();
  void Update();
  bool Moving();
  
private:
  const int _min;
	const int _max;
	const byte _pin;
	int _pos;
  int _oldpos;
	const int _restingPosition;
  const int _extendPosition;
	Servo _servo;
	ArmRole _role;
  bool _updating;

  bool WithinBounds(int value);
	void MapServoPos(int value);
};
