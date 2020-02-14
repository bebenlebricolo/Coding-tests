#include <iostream>
#include <string>
#include <memory>

using namespace std;

struct IOError
{
public:
    enum class FileError
    {
        NoError,
        WriteError,
        ReadError
    };

    static inline string to_string(IOError::FileError t)
    {
        switch(t)
        {
            case FileError::NoError:
                return "NoError";
            case FileError::WriteError:
                return "WriteError";
            case FileError::ReadError:
                return "ReadError";
            default:
                return "Unknown";
        }
    }
};

class toto
{
public:

    toto()=delete;
    explicit toto(const char* filename) : _filename(filename), _err(IOError::FileError::NoError), _isopen(false) {}
    virtual ~toto() {close();}

    virtual bool open()
    {
        _err = IOError::FileError::ReadError;
        _isopen = false;
        return false;
    }
    virtual IOError::FileError close()
    {
        _err = IOError::FileError::NoError ;
        _isopen = false ;
        return _err;
    }
    inline string filename() const {return _filename;}
    inline IOError::FileError error() const {return _err;}

protected:
    bool _isopen;
    string _filename;
    IOError::FileError _err;
};

class tata final : protected toto
{
public:
    tata()=delete;
    tata(const char* f) : toto(f){}
    ~tata()=default;
    bool open() override {_err = IOError::FileError::NoError; return true;}
    string gimme_my_filename();
private:
    string _name;
};

void get_error(toto * obj )
{
    cout << IOError::to_string(obj->error()) << endl;
}

int main(int argc, char ** argv)
{
    tata * ta = new tata("totoesaubistro");
    ta->open();
    //toto* tatoko = dynamic_cast<toto*>(ta);   // fails because base class is unreachable
    //tatoko->error();
    //toto* tatook = reinterpret_cast<toto*>(ta);
    get_error(ta);  // Won't do neither because tata is a **protected** inheritance type of base class toto, base class could not be sliced from original object (thus no polymorphism is possible)

    return 0;
}
