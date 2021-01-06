#include <Aida64SharedMemory.h>
#include <SerialHard.h>

int main()
{
    SerialHard commEsp8266;

    //Aida64SharedMemory Aida64sm;

    //aida64.Mostrar();


    while(1)
    {

        //UNA VEZ CONECTADOS MANDO DATOS AL ESP, ME QUEDO BLOQUEADO ESPERANDO LA RESPUESTA OK DEL ESP
        //Y ENTONCES DESBLOQUEO

        std::cout << commEsp8266.Leer(4) << std::endl;
      /*  for(uint32_t i = 0; i <= 100000; i++)
        {

        }*/

       /* Aida64sm.MostrarDatosSistema();
        Aida64sm.MostrarDatosTemperatura();
        Aida64sm.MostrarDatosVoltajes();
        Aida64sm.MostrarDatosPower();
        Aida64sm.MostrarDatosFan();
        Aida64sm.MostrarDatosDuty();
        Aida64sm.MostrarDatosCorriente();*/

    }

}
