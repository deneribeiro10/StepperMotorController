#ifndef MotorControl_h
#define MotorControl_h

  #include "Arduino.h"

  class MotorControl {
    public: 
      MotorControl(int stepsPerRev, int microsteps);
      void begin(int pul, int ena, int dir);
      void drive(double rev);
      void driveDeg(double deg);
      void driveTime(double ms);
      void enable(bool en);
      bool isMoving();
      void loop();
      void off();
      void on();
      void setDirection(bool dir);
      void setRPM(double rpm);

    private:
      bool step();

      bool direction;
      unsigned long driveSteps;
      bool driving;
      bool drivingDeg;
      bool drivingTime;
      bool ena;
      int microsteps;
      int pinPul;
      int pinEna;
      int pinDir;
      bool pulse;
      int spr;
      unsigned long stepPeriod;
      bool stepping;
      unsigned long steps;
      unsigned long time;
      unsigned long timerDriver;
      bool turnedOn;
  };

#endif
