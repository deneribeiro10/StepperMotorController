#include "Arduino.h"
#include "MotorControl.h"

MotorControl::MotorControl(int stepsPerRev = 200, int microsteps = 1) {
  
  this->microsteps = microsteps;
  this->spr = stepsPerRev;

}

void MotorControl::begin(int pul = 8, int ena = 9, int dir = 10) {
  
  pinPul = pul;
  pinEna = ena;
  pinDir = dir;

  pinMode(pinPul, OUTPUT);
  pinMode(pinEna, OUTPUT);
  pinMode(pinDir, OUTPUT);

  pulse = false;
  driving = false;
  drivingDeg = false;
  drivingTime = false;
  turnedOn = false;

}

void MotorControl::drive(double rev) {

  if(driving || drivingDeg || drivingTime || turnedOn) return;

  driving = true;
  steps = 0;
  driveSteps = (unsigned long) (spr * microsteps * rev);

}

void MotorControl::driveDeg(double deg) {

  if(driving || drivingDeg || drivingTime || turnedOn) return;

  drivingDeg = true;
  steps = 0;
  driveSteps = (unsigned long) (spr * microsteps * deg / 360);

}

void MotorControl::driveTime(double time) {

  if(driving || drivingDeg || drivingTime || turnedOn) return;
  
  drivingTime = true;

}

void MotorControl::enable(bool en = true) {
  
  this->ena = !en;

}

bool MotorControl::isMoving() {
  return driving || drivingDeg || drivingTime || turnedOn || stepping;
}

void MotorControl::loop() {

  digitalWrite(pinDir, direction);
  digitalWrite(pinEna, ena);
  digitalWrite(pinPul, pulse);

  if(turnedOn) {
    step();
    return;
  }

  if(driving || drivingDeg) {
    if(steps < driveSteps) {
      steps += step() ? 1 : 0;
    } else {
      driving = false;
      drivingDeg = false;
    }
  }

}

void MotorControl::off() {

  if(driving || drivingDeg || drivingTime) return;
 
  turnedOn = false;
  stepping = false;
  pulse = false;

}

void MotorControl::on() {
  
  turnedOn = true;

}

void MotorControl::setAcceleration(double revPerMin2) {

  acceleration = revPerMin2;

}

void MotorControl::setDirection(bool dir) {
  
  direction = dir;

}

void MotorControl::setRPM(double rpm) {
  
  stepPeriod = (unsigned long) (60000000 / (rpm * spr * microsteps));

}

bool MotorControl::step() {
  
  unsigned long currentTime = micros();

  if(currentTime < time) {
    time = 0;
  }

  if(!stepping) {
    time = currentTime;
    stepping = true;
    return false;
  }

  if(currentTime - time < stepPeriod/2) {
    pulse = true;
    return false;
  }

  if(currentTime - time < stepPeriod) {
    pulse = false;
    return false;
  }
  
  stepping = false;
  
  return true;
}
