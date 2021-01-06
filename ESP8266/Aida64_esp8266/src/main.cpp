#include <Arduino.h>


char c;

enum eEstado
{
  DESCONECTADO = 0,
  CONECTANDO,
  CONECTADO,
  STANDBY,
  ESCRIBIENDO,
  LEYENDO,
  BLOQUEADO,
  ERR
};
eEstado estado = eEstado::DESCONECTADO;

bool CheckInicioConexion();

char bufferRecv[100];
uint8_t iBufferRcv = 0;
uint8_t auxMaxAntesOK = 0;



void setup() {

  Serial.end();
  Serial.begin(9600);
  Serial.setTimeout(10000);

  while(!Serial) { }

  estado = eEstado::CONECTANDO;

}


void loop() {

    if(Serial.availableForWrite() > 0)
    {
      
      Serial.print("HOLA");
    }

  delay(500);
}


