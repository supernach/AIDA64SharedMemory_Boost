#ifndef SERIALHARD_H
#define SERIALHARD_H

#include <iostream>

#include <boost/asio.hpp>
#include <SerialConfig.h>

namespace boostAsio = boost::asio;

class SerialHard
{
    public:
        SerialHard();
        virtual ~SerialHard();

        bool Conectado();
        const char* Leer(uint16_t nBytes = 1);
        void Escribir(const char* datos);


    protected:

    private:

        void Init();
        void Conectar();
        bool ConfirmarConexion();
        void Desconectar();
        void ConfigurarConexion();
        void EsperarConexion();


        boostAsio::io_service io;
        boostAsio::serial_port serial;
        SerialConfig sConfig;

};

#endif // SERIALHARD_H
