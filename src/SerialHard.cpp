#include "SerialHard.h"

SerialHard::SerialHard() : io(), serial(io)
{
    this->Init();
}

SerialHard::~SerialHard()
{
    this->Desconectar();
}


///// public

bool SerialHard::Conectado()
{
    return this->ConfirmarConexion();
}

const char* SerialHard::Leer(uint16_t nBytes)
{
    uint16_t bytesLeidos = 0;
    const char* line;

    bytesLeidos = boostAsio::read(this->serial, boostAsio::buffer(&line, nBytes), boostAsio::transfer_exactly(nBytes));

    if(bytesLeidos > 0) return line;
    else return "NODATA";
}

void SerialHard::Escribir(const char* datos)
{
    boostAsio::write(this->serial, boostAsio::buffer(datos, strlen(datos)));
}

///// PRIVATE


void SerialHard::Init()
{
    this->sConfig = SerialConfig();
    this->Conectar();

    this->EsperarConexion();

    this->ConfigurarConexion();
}


void SerialHard::Conectar()
{
    this->serial.open(this->sConfig.Puerto());
}

bool SerialHard::ConfirmarConexion()
{
    if(this->serial.is_open()) return true;
    else return false;
}

void SerialHard::Desconectar()
{
    if( this->ConfirmarConexion() ) this->serial.close();
    else
    {

    }
}

void SerialHard::ConfigurarConexion()
{
    this->serial.set_option(boostAsio::serial_port_base::baud_rate(this->sConfig.Baudios()));
    this->serial.set_option(boostAsio::serial_port_base::character_size(boostAsio::serial_port::character_size(this->sConfig.BitsCaracter())));
    this->serial.set_option(boostAsio::serial_port_base::parity(this->sConfig.Paridad()));
    this->serial.set_option(boostAsio::serial_port_base::stop_bits(this->sConfig.BitsParada()));
    this->serial.set_option(boostAsio::serial_port_base::flow_control(this->sConfig.ControlFlujo()));
}

void SerialHard::EsperarConexion()
{
    while(!this->ConfirmarConexion())
    {

    }
}
