#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <iostream>

#include <boost/asio.hpp>

namespace boostAsio = boost::asio;

struct Data
{
    char header1;
    char header2;
    //char header3;
};

class SerialComm
{
    public:
        SerialComm();
        virtual ~SerialComm();

        bool Conectar(const char* puerto, uint16_t baudios);
        void Desconectar();
        std::size_t Escribir(std::string datos);
        std::size_t EscribirCaracter(char caracter);
        std::string LeerLinea();
        char LeerCaracter();

        bool EstaConectado();
        void EscanearPuertos(uint16_t baudios);
        uint8_t getEstado();


    protected:

    private:

        boostAsio::io_service io;
        boostAsio::serial_port serial;
        const char* nombrePuertos[10] =
            {
                "/COM1",
                "/COM2",
                "/COM3",
                "/COM4",
                "/COM5",
                "/COM6",
                "/COM7",
                "/COM8",
                "/COM9",
                "./COM10",
            };

        uint8_t estado = 0; // 0=desconectado; 1=conectado; 2=escribiendo; 3=escrito; 4=leyendo; 5=leido;

        Data bufferLectura;

        bool flagAuxLeer = false;



};

#endif // SERIALCOMM_H
