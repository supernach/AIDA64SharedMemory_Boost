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
            this->serial.set_option(boostAsio::serial_port_base::parity(boostAsio::serial_port::parity::even));
            this->serial.set_option(boostAsio::serial_port_base::character_size(boostAsio::serial_port::character_size(8)));
            this->serial.set_option(boostAsio::serial_port_base::stop_bits(boostAsio::serial_port::stop_bits::one));
            this->serial.set_option(boostAsio::serial_port_base::flow_control(boostAsio::serial_port::flow_control::none));

            std::cout << "Puerto: " << puerto << " ha sido abierto" << std::endl;

            this->estado = 1;

            return true;
        }
        else
        {
            this->estado = 0;
            return false;
        }
    }
    catch(boost::system::system_error& ex)
    {
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
            this->estado = 0;
            std::cout << "Puerto cerrado" << std::endl;
        }

    }
    catch(boost::system::system_error& ex)
    {
        std::cout << "Puerto.close Fallo: " << ex.what() << std::endl;
    }

}

std::size_t SerialComm::Escribir(std::string datos)
{
    std::size_t bytesEscritos = 0;
    try
    {
        this->estado = 2;
        bytesEscritos = boostAsio::write(this->serial, boostAsio::buffer(datos.c_str(), datos.size()));
        this->estado = 3;

    }
    catch(boost::system::system_error& ex)
    {
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
        this->estado = 2;
        bytesEscritos = boostAsio::write(this->serial, boostAsio::buffer(&c, 1));
        this->estado = 3;

    }
    catch(boost::system::system_error& ex)
    {
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
    std::string cadena;
    char obuf[2];
    size_t len;
    boostAsio::streambuf b;

    std::cout << "LEERLINEA().EMPIEZA READ()" << std::endl;

    this->estado = 4;
    try
    {
        //len = boostAsio::read(this->serial, boostAsio::buffer(obuf, sizeof(obuf)));

        len = boostAsio::read(this->serial, b, boostAsio::transfer_exactly(2));
        //std::cout << b.prepare() << std::endl;
        /*std::cout << obuf[0] << std::endl;
        std::cout << obuf[1] << std::endl;*/
    }
    catch(boost::system::system_error& ex)
    {
        std::cout << "::Escribir Fallo: " << ex.what() << std::endl;
    }

    this->estado = 5;

    std::istream is(&b);
    std::string line;
    std::getline(is, line);

    std::cout << line << std::endl;

    /*Data d = {};
    memcpy( &d, obuf, sizeof(d) );

    std::cout << sizeof(d) << std::endl;
    std::cout << len << std::endl;
    std::cout << d.header1 << std::endl;
    std::cout << d.header2 << std::endl;*/
    //std::cout << d.header3 << std::endl;

    std::cout << "LEERLINEA().TERMINA READ()" << std::endl;

    return line;
}

char SerialComm::LeerCaracter()
{
    char c;

    std::cout << "LEERCARACTER().EMPIEZA READ()" << std::endl;

    this->estado = 4;

    size_t len = boostAsio::read(this->serial, boostAsio::buffer(&c, 1));

    this->estado = 5;

    std::cout << len << std::endl;
    std::cout << c << std::endl;

    std::cout << "LEERCARACTER().TERMINA READ()" << std::endl;

    return c;
}

uint8_t SerialComm::getEstado()
{
    return this->estado;
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
