#include "MotorControl.h"








int velocidade = 400;   /// Velocidade em RPM do extrusor, maximo 400.


double rotacoes = 65;    /// Rotações calculadas ( pode ser um numero decimal    EX.: 3.1415 ) - teste dia 25/07/2019








MotorControl extrusor(200, 1);
MotorControl tampa(200, 8);

void setup() {
	extrusor.begin(9, 10, 11);
  tampa.begin(5, 6, 7);

  tampa.setRPM(200);
  tampa.enable(true);
  tampa.setDirection(false);
  
  extrusor.setRPM(velocidade);
  extrusor.enable(true);
  extrusor.setDirection(false);

  extrusor.drive(rotacoes);
  tampa.on();
}

void loop() {  
  extrusor.loop();
  tampa.loop();
  
  if( !extrusor.isMoving() ) {
    extrusor.enable(false);

    tampa.off();
  }

  if( !tampa.isMoving() ) {
    tampa.enable(false);
  }
}
