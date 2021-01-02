#include "SerialComm.h"

SerialComm::SerialComm() : io(), serial(io)
{

}

SerialComm::~SerialComm()
{
     this->Desconectar();
}


bool SerialComm::Conectar(const char* puerto, uint16_t baudios)
{
    try
    {
        this->serial.open(puerto);

        if(this->serial.is_open())
        {
            this->serial.set_option(boostAsio::serial_port_base::baud_rate(baudios));
            this->serial.set_option(boostAsio::serial_port_base::parity(boostAsio::serial_port::parity::none));
            this->serial.set_option(boostAsio::serial_port_base::character_size(boostAsio::serial_port::character_size(8)));
            this->serial.set_option(boostAsio::serial_port_base::stop_bits(boostAsio::serial_port::stop_bits::one));
            this->serial.set_option(boostAsio::serial_port_base::flow_control(boostAsio::serial_port::flow_control::none));

            std::cout << "Serialcomm::Conectar() nPuerto= " << puerto << std::endl;

            this->estadoComm = eEstadoComm::CONECTADO;

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

std::size_t SerialComm::Escribir(std::string datos)
{
    std::size_t bytesEscritos = 0;
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

    if(bytesEscritos < 0)
    {
        bytesEscritos = 0;
    }
    return bytesEscritos;
}

std::size_t SerialComm::EscribirCaracter(char caracter)
{
    std::size_t bytesEscritos = 0;
    char c = caracter;
    try
    {
        bytesEscritos = boostAsio::write(this->serial, boostAsio::buffer(&c, 1));
        this->estadoComm = eEstadoComm::BLOQUEADO;
    }
    catch(boost::system::system_error& ex)
    {
        this->estadoComm = eEstadoComm::ERR;
        std::cout << "::Escribir Fallo: " << ex.what() << std::endl;
    }

    if(bytesEscritos < 0)
    {
        bytesEscritos = 0;
    }
    return bytesEscritos;
}

std::string SerialComm::LeerLinea()
{
    size_t len;
    boostAsio::streambuf b;
    std::string line;

    if(!this->EstaLibre())
    {
        try
        {
            len = boostAsio::read_until(this->serial, b, '\n');
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

    size_t len = boostAsio::read(this->serial, boostAsio::buffer(&c, 1));

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

bool SerialComm::EstaConectado()
{
    if(this->serial.is_open())
    {
        return true;
    }
    else
    {
        return false;
    }
}





void SerialComm::EscanearPuertos(uint16_t baudios)
{
    uint16_t nPuertos = sizeof(this->nombrePuertos);

    for(uint8_t i = 0; i < nPuertos; i++)
    {
            this->Conectar(this->nombrePuertos[i], baudios);
            this->Desconectar();
    }
}
