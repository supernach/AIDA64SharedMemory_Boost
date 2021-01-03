#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <iostream>

#include <boost/asio.hpp>

namespace boostAsio = boost::asio;

class SerialComm
{
    public:
        SerialComm();
        virtual ~SerialComm();

        bool Conectar(const char* puerto, uint16_t baudios);
        void Desconectar();
        uint16_t Escribir(std::string datos);
        std::string Leer(char delim = '\n');
        char LeerCaracter();


        bool EstaLibre();


    protected:

    private:

        void Init();
        void EscanearPuertos();
        void ConfigurarConexion();


        enum class eEstadoComm
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

        eEstadoComm estadoComm = eEstadoComm::DESCONECTADO;

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

        bool flagAuxLeer = false;

        const char* puerto = "/COM3";
        uint16_t baudios = 9600;
        boostAsio::serial_port::parity::type paridad = boostAsio::serial_port::parity::none;
        uint16_t tamCaracter = 8;
        boostAsio::serial_port::stop_bits::type bitsParada = boostAsio::serial_port::stop_bits::one;
        boostAsio::serial_port::flow_control::type controlFlujo = boostAsio::serial_port::flow_control::none;




};

#endif // SERIALCOMM_H
