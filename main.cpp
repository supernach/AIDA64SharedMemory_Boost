#include <Aida64SharedMemory.h>

int main()
{
    Aida64SharedMemory Aida64sm;

    //aida64.Mostrar();

    while(1)
    {
        Aida64sm.MostrarDatosSistema();
        Aida64sm.MostrarDatosTemperatura();
        Aida64sm.MostrarDatosVoltajes();
        Aida64sm.MostrarDatosPower();
        Aida64sm.MostrarDatosFan();
        Aida64sm.MostrarDatosDuty();
        Aida64sm.MostrarDatosCorriente();


        for(uint32_t i = 0; i <= 2299999999; i++)
        {

        }
        system("cls");
    }

}
