#include "ArmSegment.h"

ArmSegment::ArmSegment(int smin, int smax, byte pin, int pos, 
int restingPosition, int extendPosition, ArmRole role): 
_min(smin), _max(smax), _pin(pin), _pos(pos), _oldpos(pos), 
_restingPosition(restingPosition), _extendPosition(extendPosition), _role(role),
_updating(false)
{
	_servo.attach(_pin);
	_servo.write(_pos);
}

ArmSegment::~ArmSegment()
{

}

void ArmSegment::ReturnToRest()
{
	SetPosition(_restingPosition);
}

void ArmSegment::Extend()
{
	SetPosition(_extendPosition);
}

int ArmSegment::GetPosition()
{
  return _pos;
}

void ArmSegment::SetPosition(int pos)
{
  _oldpos = _pos;
  if(!WithinBounds(pos))
  {
    MapServoPos(pos);
  } else {
    _pos = pos;
  }
  _updating = true;
}

int ArmSegment::GetMin()
{
  return _min;
}

int ArmSegment::GetMax()
{
  return _max;
}

int ArmSegment::GetRest()
{
  return _restingPosition;
}

int ArmSegment::GetExtend()
{
  return _extendPosition;
}

void ArmSegment::Update()
{
  if(_oldpos != _pos){
    if(_oldpos < _pos)
    {
      _oldpos++;
    } else
    {
      _oldpos--;
    }
    _servo.write(_oldpos);
  } else
  {
    _updating = false;
  }
}

bool ArmSegment::Moving()
{
  return _updating;
}

/////////////Private//////////////////////////
bool ArmSegment::WithinBounds(int value)
{
  return (_min <= value) && (value <= _max);
}

void ArmSegment::MapServoPos(int value)
{
	_pos = map(value, 0, 1023, _min, _max);
}
