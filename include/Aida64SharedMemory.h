#ifndef AIDA64SHAREDMEMORY_H
#define AIDA64SHAREDMEMORY_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <exception>
#include <stdlib.h>

#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/interprocess/exceptions.hpp>

namespace boostPt = boost::property_tree;
namespace boostIpc = boost::interprocess;

struct aida64
{
    std::string id;         //<id></id>
    std::string label;      // <label></label>
    std::string value;      // <value><value>
};


class Aida64SharedMemory
{
    public:
        Aida64SharedMemory();
        virtual ~Aida64SharedMemory();



        void MostrarDatosSistema();
        void MostrarDatosTemperatura();
        void MostrarDatosVoltajes();
        void MostrarDatosPower();
        void MostrarDatosFan();
        void MostrarDatosDuty();
        void MostrarDatosCorriente();

    protected:

    private:
        void Init();
        void Cargar(std::istringstream datos);
        void ActualizarDatos();
        void MostrarDatos(std::vector<aida64> datos, const char* titulo);

        void bucleDatos(std::vector<aida64> datos);
        void tituloDatos(const char* titulo);
        void limpiarVectores();

        boostIpc::windows_shared_memory segment;
        boostIpc::mapped_region region;

        char* bytesSM;
        std::string stringBuffer;

        std::vector<aida64> vAida64Sys;
        std::vector<aida64> vAida64Temp;
        std::vector<aida64> vAida64Volt;
        std::vector<aida64> vAida64Pwr;
        std::vector<aida64> vAida64Fan;
        std::vector<aida64> vAida64Duty;
        std::vector<aida64> vAida64Curr;
};

#endif // AIDA64SHAREDMEMORY_H
