#include <iostream>
#include <string>
#include <exception>
#include <cstring>

struct IoErrors
{
    enum IoErrorType
    {
        Unknown         = 0x00,
        FileNotFound    = 0x01,
        NotAllowed      = 0x02
    };
    static inline std::string to_string(IoErrorType t)
    {
        switch(t)
        {
            case FileNotFound:
                return std::string("FileNotFound");
                break;
            case NotAllowed:
                return std::string("NotAllowed");
                break;
            default:
                return std::string("Unkown");
                break;
        }
    }
};

class toto : public std::exception
{
public:
    toto() = delete;
    explicit toto(std::string& m) : msg(m){};
    explicit toto(const char* m) : msg(m){};
    virtual const char* what() const noexcept override {return msg.c_str();}

protected:
    std::string msg;
    std::string fullmsg;
};

class tata_system : public toto
{
public:


    tata_system() = delete;
    explicit tata_system(const char* _msg, const char* _filename, IoErrors::IoErrorType _ertype) : toto(_msg), filename(_filename), error_type(_ertype) {
        fullmsg = "Failed with msg : \t" + msg + "\nFilename :\t\t" + filename + "\nError type : \t\t" + IoErrors::to_string(error_type);
    }
    explicit tata_system(std::string& _msg, std::string& _filename, IoErrors::IoErrorType _ertype) : tata_system(_msg.c_str(),_filename.c_str(),_ertype) {}

    virtual const char* what() const noexcept override
    {
        return fullmsg.c_str();
    }

private:
    std::string filename;
    IoErrors::IoErrorType error_type;
};


void raise_ioerror() {
    using namespace std;
    cout << "Accessing a wrong file ... " << endl;
    throw tata_system("Cannot open file", "1235468.tototata", IoErrors::FileNotFound);
}


struct titi
{
    enum {
        Hello,
        Baba,
        Cool
    } yolo;
};


int main (int argc, char** argv)
{
    try
    {
        raise_ioerror();
    }
    catch (const tata_system& e)
    {
        std::cerr << e.what() << std::endl; // prints the whole message block
    }

    volatile titi t;
    t.yolo=t.Baba;

    return 0;
}