
#include "pseudo_serial.hpp"

int main(const int argc, const char * const * const argv)
{
    for (int i = 0 ; i < argc ; i++) {
        std::cout << argv[i] << " " ;
    }
    std::cout << "\n";
    pseudo_serial::serial_type communication_type = pseudo_serial::serial_type::USB;
    pseudo_serial::baudrate baud                  = 115200;
    pseudo_serial::serial_port usb_port(baud,communication_type);
    try {
        usb_port.open();
        std::cout << "Got new line : " << usb_port.getline() << std::endl;
        usb_port.putchar('Q');
        usb_port.close();
        std::string response = usb_port.getline();
        // Shall not get there !
        char letter = usb_port.getchar();
    }
    catch (pseudo_serial::serial_exception& e) {
        std::cerr << "Exception thrown : " << e.what() << std::endl;
        std::cerr << "Port type" << e.properties() << std::endl;
    }


    return 0;
}