#ifndef SERIALCONFIG_H
#define SERIALCONFIG_H

#include <boost/asio.hpp>

namespace boostSerialPort = boost::asio;

class SerialConfig
{
    public:
        SerialConfig();
        virtual ~SerialConfig();

        void Puerto(const char* puerto);
        const char* Puerto() const;

        void Baudios(uint16_t baudios);
        uint16_t Baudios() const;

        void BitsCaracter(uint16_t bitsCaracter);
        uint16_t BitsCaracter() const;

        void Paridad(const char paridad);
        boostSerialPort::serial_port::parity::type Paridad() const;

        void BitsParada(uint8_t modo);
        boostSerialPort::serial_port::stop_bits::type BitsParada() const;

        void ControlFlujo(const char modo);
        boostSerialPort::serial_port::flow_control::type ControlFlujo() const;


    protected:

    private:

        struct stParidad
        {
            boostSerialPort::serial_port::parity::type Ninguna = boostSerialPort::serial_port::parity::none;
            boostSerialPort::serial_port::parity::type Par = boostSerialPort::serial_port::parity::even;
            boostSerialPort::serial_port::parity::type Impar = boostSerialPort::serial_port::parity::odd;
        } sParidad;

        struct stBitsParada
        {
            boostSerialPort::serial_port::stop_bits::type Uno = boostSerialPort::serial_port::stop_bits::one;
            boostSerialPort::serial_port::stop_bits::type UnoCinco = boostSerialPort::serial_port::stop_bits::onepointfive;
            boostSerialPort::serial_port::stop_bits::type Dos = boostSerialPort::serial_port::stop_bits::two;
        } sBitsParada;

        struct stControlFlujo
        {
            boostSerialPort::serial_port::flow_control::type Ninguna = boostSerialPort::serial_port::flow_control::none;
            boostSerialPort::serial_port::flow_control::type Hardware = boostSerialPort::serial_port::flow_control::hardware;
            boostSerialPort::serial_port::flow_control::type Software = boostSerialPort::serial_port::flow_control::software;
        } sControlFlujo;

        void Init();

        const char* puerto;
        uint16_t baudios;
        uint16_t bitsCaracter;
        boostSerialPort::serial_port::parity::type paridad;
        boostSerialPort::serial_port::stop_bits::type bitsParada;
        boostSerialPort::serial_port::flow_control::type controlFlujo;

};

#endif // SERIALCONFIG_H
