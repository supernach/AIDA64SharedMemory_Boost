#include "SerialConfig.h"

SerialConfig::SerialConfig()
{
    this->Init();
}

SerialConfig::~SerialConfig()
{
    //dtor
}



////// public

void SerialConfig::Puerto(const char* puerto)
{
    this->puerto = puerto;
}
const char* SerialConfig::Puerto() const
{
    return this->puerto;
}

void SerialConfig::Baudios(uint16_t baudios)
{
    this->baudios = baudios;
}
uint16_t SerialConfig::Baudios() const
{
    return this->baudios;
}

void SerialConfig::BitsCaracter(uint16_t bitsCaracter)
{
    this->bitsCaracter = bitsCaracter;
}
uint16_t SerialConfig::BitsCaracter() const
{
    return this->bitsCaracter;
}

void SerialConfig::Paridad(const char paridad)
{
    if(paridad == 'N') this->paridad = sParidad.Ninguna;
    else if(paridad == 'I') this->paridad = sParidad.Impar;
    else if(paridad == 'P') this->paridad = sParidad.Par;
    else
    {
        this->paridad = sParidad.Ninguna;
    }
}
boostSerialPort::serial_port::parity::type SerialConfig::Paridad() const
{
    return this->paridad;
}

void SerialConfig::BitsParada(uint8_t modo)
{
    if(modo == 1) this->bitsParada = sBitsParada.Uno;
    else if(modo == 15) this->bitsParada = sBitsParada.UnoCinco;
    else if(modo == 2) this->bitsParada = sBitsParada.Dos;
    else
    {
        this->bitsParada = sBitsParada.Uno;
    }
}
boostSerialPort::serial_port::stop_bits::type SerialConfig::BitsParada() const
{
    return this->bitsParada;
}

void SerialConfig::ControlFlujo(const char modo)
{
    if(modo == 'N') this->controlFlujo = sControlFlujo.Ninguna;
    else if(modo == 'H') this->controlFlujo = sControlFlujo.Hardware;
    else if(modo == 'S') this->controlFlujo = sControlFlujo.Software;
    else
    {
        this->controlFlujo = sControlFlujo.Ninguna;
    }
}
boostSerialPort::serial_port::flow_control::type SerialConfig::ControlFlujo() const
{
    return this->controlFlujo;
}





///// private

void SerialConfig::Init()
{
    this->Puerto("/COM3");
    this->Baudios(9600);
    this->BitsCaracter(8);
    this->Paridad('N'); // N = ninguna; I = impar; P = par
    this->BitsParada(1); // 1 = 1 bit; 2 = 2 bit; 15 = 1.5 bit
    this->ControlFlujo('N'); // N = ninguno; H = hardware; S = software
}
