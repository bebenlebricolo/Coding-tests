#ifndef PSEUDO_SERIAL_HEADER
#define PSEUDO_SERIAL_HEADER

#include <exception>
#include <cstdint>
#include <string>
#include <malloc.h>
#include <string>
#include <iostream>

namespace pseudo_serial {

constexpr unsigned int GETLINE_MOCK_LENGTH = 50U;
constexpr unsigned int BAUDRATE_STR_MAX_SIZE = 20U;

    enum class serial_type {
        USB,
        UART,
        SPI,
        I2C
    };

    typedef uint32_t baudrate;
    static const baudrate default_baudrate = 115200;

    class serial_exception : public std::exception
    {
    private:
        serial_type _type;
        baudrate    _baud;
        std::string _msg;

    public:
        serial_exception(std::string const& msg,
                         serial_type stype = serial_type::USB,
                         baudrate baud = default_baudrate
                         ) noexcept :
                                    _type(stype),
                                    _baud(baud),
                                    _msg(msg) {}

        virtual const char* what() const noexcept
        {
            return _msg.c_str();
        }

        serial_type get_type() noexcept {return _type;}
        baudrate get_baudrate() noexcept {return _baud;}
        std::string properties() noexcept {
            std::string out = "Port type : ";
            switch (_type) {
                case serial_type::USB :
                    out += "USB";
                    break;
                case serial_type::UART :
                    out += "UART";
                    break;
                case serial_type::SPI :
                    out += "SPI";
                    break;
                case serial_type::I2C :
                    out += "I2C";
                    break;
                default :
                    out += "UNSUPPORTED";
                    break;
            }
            out += '\n';
            out += "Port speed : " + std::to_string(_baud);
            return out;
        }
        virtual ~serial_exception() {}
    };


    class serial_port {
        baudrate    _baud;
        serial_type _type;
        bool        _is_open;
        bool        _is_ready;

    public:
        explicit serial_port(baudrate baud = default_baudrate,
                             serial_type type = serial_type::USB):
                                                     _baud(baud),
                                                     _type(type),
                                                     _is_open(false),
                                                     _is_ready(false) {}
        void open() {
            _is_open = true;
            _is_ready = true;
        }

        void close() {
            _is_open = false;
            _is_ready = false;
        }

        std::string getline() const {
            std::string out;
            if (_is_open && _is_ready){
                out = "New line from port !";
            }
            else {
                throw serial_exception("Port not ready yet! Cannot get line",
                                        _type,
                                        _baud);
            }
            return out;
        }

        void putchar(char c)
        {
            if (_is_open && _is_ready) {
                std::cout << c << std::endl;
            }
            else
            {
                throw serial_exception("Port not ready yet!",
                        _type,
                        _baud);
            }

        }
        char getchar()
        {
            if (_is_open && _is_ready) {
                return 'a';
            }
            else
            {
                throw serial_exception("Port not ready yet!",
                        _type,
                        _baud);
            }
        }
    };

}


#endif // PSEUDO_SERIAL_HEADER