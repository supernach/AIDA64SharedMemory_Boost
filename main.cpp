#include <Aida64SharedMemory.h>
#include <SerialComm.h>

int main()
{
    SerialComm commEsp8266;

    //Aida64SharedMemory Aida64sm;

    //aida64.Mostrar();

    while(!commEsp8266.Conectar("/COM3", 9600))
    {

    }


    while(1)
    {

        //UNA VEZ CONECTADOS MANDO DATOS AL ESP, ME QUEDO BLOQUEADO ESPERANDO LA RESPUESTA OK DEL ESP
        //Y ENTONCES DESBLOQUEO

        if(commEsp8266.EstaLibre())
        {
            std::cout << "commEsp8266::Escribir() nBytes= " << commEsp8266.Escribir("ESTA ES UNA FRASE con ESPACIOS") << std::endl;
        }
        else
        {
            std::cout << "commEsp8266::LeerLinea() Data= " << commEsp8266.Leer() << std::endl;
        }

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
