#include "Aida64SharedMemory.h"

Aida64SharedMemory::Aida64SharedMemory()
{
    try
    {
        this->Init();
    }
    catch(std::exception &e)
    {
        std::cout << "\nFallo:" << e.what() << std::endl;
    }
}

Aida64SharedMemory::~Aida64SharedMemory()
{
        this->limpiarVectores();

}

void Aida64SharedMemory::Init()
{
    this->segment = boostIpc::windows_shared_memory(boostIpc::open_only, "AIDA64_SensorValues", boostIpc::read_only); //Abro memoria compartida
    this->region = boostIpc::mapped_region(this->segment, boostIpc::read_only); //copio memoria compartida a mi memoria

    this->ActualizarDatos();
}



void Aida64SharedMemory::tituloDatos(const char* titulo)
{
    std::cout << "\n" << titulo << std::endl;
    std::cout << "-------------------------------------" << std::endl;
}

void Aida64SharedMemory::limpiarVectores()
{
    vAida64Sys.clear();
    vAida64Temp.clear();
    vAida64Volt.clear();
    vAida64Pwr.clear();
    vAida64Fan.clear();
    vAida64Duty.clear();
    vAida64Curr.clear();
}

void Aida64SharedMemory::Cargar(std::istringstream datos)
{
    boostPt::ptree tree; //Creo arbol para volcar los datos de la memoria
    aida64 lDatos; //Creo estructura de datos para rellenarla y añadirla al vector que sea
    boostPt::read_xml(datos, tree); //Pasar datos memoria al arbol parseando los tags

    this->limpiarVectores(); //inicializo los vectores

    for( const auto& pair : tree)  // recorro el arbol buscando las etiquetas y guardo su valor en el vector correspondiente
    {
        lDatos.id = pair.second.get<std::string>("id");
        lDatos.label = pair.second.get<std::string>("label");
        lDatos.value = pair.second.get<std::string>("value");

        if(pair.first == "sys")
        {
            vAida64Sys.push_back(lDatos); //agrego datos memoria SYS a su vector
        }
        else if(pair.first == "temp")
        {
            vAida64Temp.push_back(lDatos); //agrego datos memoria TEMP a su vector
        }
        else if(pair.first == "volt")
        {
            vAida64Volt.push_back(lDatos); //agrego datos memoria VOLT a su vector
        }
        else if(pair.first == "pwr")
        {
            vAida64Pwr.push_back(lDatos); //agrego datos memoria PWR a su vector
        }
        else if(pair.first == "fan")
        {
            vAida64Fan.push_back(lDatos); //agrego datos memoria PWR a su vector
        }
        else if(pair.first == "duty")
        {
            vAida64Duty.push_back(lDatos); //agrego datos memoria PWR a su vector
        }
        else if(pair.first == "curr")
        {
            vAida64Curr.push_back(lDatos); //agrego datos memoria PWR a su vector
        }
        else
        {

        }

    }
}

void Aida64SharedMemory::ActualizarDatos()
{
    this->bytesSM = static_cast<char*>(region.get_address()); //recojo datos memoria y convierto a cadena caracteres

    //std::cout << bytesSM << std::endl;

    this->stringBuffer = std::string(bytesSM, region.get_size()); //creo un buffer de string

    this->Cargar(std::istringstream(stringBuffer)); //pasar datos de memoria a trabajo
}

void Aida64SharedMemory::bucleDatos(std::vector<aida64> datos)
{
    for (const auto& fDatos : datos)
    {
        std::cout << "ID: " << fDatos.id << ", LABEL: " << fDatos.label << ", VALUE: " << fDatos.value << std::endl;


    }
}

void Aida64SharedMemory::MostrarDatos(std::vector<aida64> datos, const char* titulo)
{
    this->ActualizarDatos();
    this->tituloDatos(titulo);
    this->bucleDatos(datos);
}


void Aida64SharedMemory::MostrarDatosSistema()
{
    this->MostrarDatos(vAida64Sys, "SISTEMA");
}

void Aida64SharedMemory::MostrarDatosTemperatura()
{
    this->MostrarDatos(vAida64Temp, "TEMPERATURAS");
}

void Aida64SharedMemory::MostrarDatosVoltajes()
{
    this->MostrarDatos(vAida64Volt, "VOLTAJES");

}

void Aida64SharedMemory::MostrarDatosPower()
{
    this->MostrarDatos(vAida64Pwr, "POWER");

}

void Aida64SharedMemory::MostrarDatosFan()
{
    this->MostrarDatos(vAida64Fan, "VENTILADORES");

}

void Aida64SharedMemory::MostrarDatosDuty()
{
    this->MostrarDatos(vAida64Duty, "DUTY");

}

void Aida64SharedMemory::MostrarDatosCorriente()
{
    this->MostrarDatos(vAida64Curr, "CORRIENTE");

}



