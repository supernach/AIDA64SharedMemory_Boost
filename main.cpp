#include <Aida64SharedMemory.h>
#include <SerialComm.h>

int main()
{
    SerialComm commEsp8266;

    //Aida64SharedMemory Aida64sm;

    //aida64.Mostrar();

    //commEsp8266.EscanearPuertos(9600);

    while(!commEsp8266.Conectar("/COM3", 9600))
    {

    }

    /*if(commEsp8266.Conectar("/COM3", 9600))
    {
        std::cout << "Conectado" << std::endl;
    }*/

    while(1)
    {
        /*std::cout << "MAIN(). INICIO ESCRIBIR" << std::endl;
        std::cout << "Longitud en bytes: " << commEsp8266.EscribirCaracter('A') << std::endl;
        std::cout << "MAIN(). FIN ESCRIBIR" << std::endl;*/
         //char cadena = "AA";

      /*  std::cout << "MAIN(). INICIO ESCRIBIR" << std::endl;
        std::cout << "Longitud en bytes: " << commEsp8266.Escribir("AA") << std::endl;
        std::cout << "MAIN(). FIN ESCRIBIR" << std::endl;*/

        std::cout << "MAIN(). INICIO LEEER" << std::endl;
        commEsp8266.LeerLinea();
        std::cout << "MAIN(). FIN LEEER" << std::endl;

        for(uint32_t i = 0; i <= 100000; i++)
        {

        }

       /* Aida64sm.MostrarDatosSistema();
        Aida64sm.MostrarDatosTemperatura();
        Aida64sm.MostrarDatosVoltajes();
        Aida64sm.MostrarDatosPower();
        Aida64sm.MostrarDatosFan();
        Aida64sm.MostrarDatosDuty();
        Aida64sm.MostrarDatosCorriente();*/

        /*if(commEsp8266.EstaConectado())
        {
            std::cout << "Conectado" << std::endl;
        }
        else
        {
            std::cout << "Desconectado" << std::endl;
        }*/



        /*if((commEsp8266.getEstado() == 1) || (commEsp8266.getEstado() == 5))
        {
            uint16_t bytesEscritos = 0;

            std::cout << "ESCRIBO EN EL PUERTO SERIE" << std::endl;

            bytesEscritos = commEsp8266.Escribir("Hello world\n");

            std::cout << "BYTES ESCRITOS: " << bytesEscritos << std::endl;

            std::cout << "ESPERO A RECIBIR EL ESPEJO" << std::endl;
        }
        else if(commEsp8266.getEstado() == 3)
        {
            char* datosLeidos;
            datosLeidos = commEsp8266.LeerLinea();

            std::cout << &datosLeidos << std::endl;

            //std::cout << commEsp8266.LeerLinea() << std::endl;

            std::cout << "LINEA LEIDA" << std::endl;
        }

        for(uint32_t i = 0; i <= 2299999999; i++)
        {

        }*/
        //system("cls");
    }

}
