#include "SerialComm.h"

SerialComm::SerialComm() : io(), serial(io)
{
    this->Init();
}

SerialComm::~SerialComm()
{
     this->Desconectar();
}


bool SerialComm::Conectar(const char* puerto, uint16_t baudios)
{
    uint8_t esperaConexionOK = 0;
    try
    {
        this->puerto = puerto;
        this->baudios = baudios;
        this->serial.open(this->puerto);

        if(this->serial.is_open())
        {
            this->ConfigurarConexion();

            std::cout << "Serialcomm::Conectar() nPuerto= " << puerto << std::endl;

            while(!esperaConexionOK)
            {
                this->Escribir("INIT");

                while(!esperaConexionOK)
                {
                    if( (this->Leer().compare("ACK")) )
                    {
                        this->Escribir("RACK");
                        esperaConexionOK = 1;
                    }
                }
            }

            this->estadoComm = eEstadoComm::CONECTADO;

            esperaConexionOK = 0;

            return true;
        }
        else
        {
            this->estadoComm = eEstadoComm::DESCONECTADO;
            return false;
        }
    }
    catch(boost::system::system_error& ex)
    {
        this->estadoComm = eEstadoComm::ERR;
        std::cout << "Puerto: " << puerto << " no se pudo abrir. Fallo: " << ex.what() << std::endl;
        return false;
    }

}

void SerialComm::Desconectar()
{
    try
    {
        if(this->serial.is_open())
        {
            this->serial.close();
            this->estadoComm = eEstadoComm::DESCONECTADO;
            std::cout << "Puerto cerrado" << std::endl;
        }

    }
    catch(boost::system::system_error& ex)
    {
        this->estadoComm = eEstadoComm::ERR;
        std::cout << "Puerto.close Fallo: " << ex.what() << std::endl;
    }

}

uint16_t SerialComm::Escribir(std::string datos)
{
    uint16_t bytesEscritos = 0;
    try
    {
        bytesEscritos = boostAsio::write(this->serial, boostAsio::buffer(datos.c_str(), datos.size()));
        this->estadoComm = eEstadoComm::BLOQUEADO;

    }
    catch(boost::system::system_error& ex)
    {
        this->estadoComm = eEstadoComm::ERR;
        std::cout << "::Escribir Fallo: " << ex.what() << std::endl;
    }

    return bytesEscritos;
}

std::string SerialComm::Leer(char delim)
{
    uint16_t len;
    boostAsio::streambuf b;
    std::string line;

    if(!this->EstaLibre())
    {
        try
        {
            len = boostAsio::read_until(this->serial, b, delim);
        }
        catch(boost::system::system_error& ex)
        {
            this->estadoComm = eEstadoComm::ERR;
            std::cout << "::Escribir Fallo: " << ex.what() << std::endl;
        }

        std::istream is(&b);
        std::getline(is, line);
        if(line.compare("OK") == 0)
        {
            this->estadoComm = eEstadoComm::STANDBY;
        }

        b.consume(len);
        return line;
    }
    else
    {

        std::cout << "LEERLINEA().EMPIEZA READ()" << std::endl;

        try
        {
            this->estadoComm = eEstadoComm::BLOQUEADO;

            len = boostAsio::read_until(this->serial, b, '\n');

        }
        catch(boost::system::system_error& ex)
        {
            this->estadoComm = eEstadoComm::ERR;
            std::cout << "::Escribir Fallo: " << ex.what() << std::endl;
        }

        std::istream is(&b);
        std::getline(is, line);

        std::cout << line << std::endl;

        this->estadoComm = eEstadoComm::STANDBY;

        std::cout << "LEERLINEA().TERMINA READ()" << std::endl;

        b.consume(len);
        return line;
    }
}

char SerialComm::LeerCaracter()
{
    char c;

    std::cout << "LEERCARACTER().EMPIEZA READ()" << std::endl;

    this->estadoComm = eEstadoComm::BLOQUEADO;

    uint16_t len = boostAsio::read(this->serial, boostAsio::buffer(&c, 1));

    this->estadoComm = eEstadoComm::STANDBY;

    std::cout << len << std::endl;
    std::cout << c << std::endl;

    std::cout << "LEERCARACTER().TERMINA READ()" << std::endl;

    return c;
}

bool SerialComm::EstaLibre()
{
    if( (this->estadoComm == eEstadoComm::CONECTADO) || (this->estadoComm == eEstadoComm::STANDBY) ) return true;
    else return false;
}



//////////////// PRIVATE

void SerialComm::Init()
{
    this->estadoComm = eEstadoComm::DESCONECTADO;
}

void SerialComm::EscanearPuertos()
{
    uint16_t nPuertos = sizeof(this->nombrePuertos);

    for(uint8_t i = 0; i < nPuertos; i++)
    {
            this->Conectar(this->nombrePuertos[i], this->baudios);
            this->Desconectar();
    }
}


void SerialComm::ConfigurarConexion()
{
    this->serial.set_option(boostAsio::serial_port_base::baud_rate(this->baudios));
    this->serial.set_option(boostAsio::serial_port_base::parity(this->paridad));
    this->serial.set_option(boostAsio::serial_port_base::character_size(boostAsio::serial_port::character_size(this->tamCaracter)));
    this->serial.set_option(boostAsio::serial_port_base::stop_bits(this->bitsParada));
    this->serial.set_option(boostAsio::serial_port_base::flow_control(this->controlFlujo));

}
