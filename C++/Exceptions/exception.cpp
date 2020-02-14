#include <exception>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <ostream>

class customException : public std::exception
{
public:
    enum class stack_state {
        FULL,
        EMPTY
    };
    customException()=delete;
    customException(const char* m, unsigned int p, const char* s, stack_state state);
    virtual const char* what() const noexcept override {
        std::string out;
        out += _msg;
        out += "\n";
        out += "Process pid = " + std::to_string(_pid) + "\n";
        out += "Socket name = " + _socket_name + "\n";
        {
            std::string statestr = ((_state == stack_state::FULL) ? "FULL" : "EMPTY");
            out += "Stack state = " + statestr + "\n";
        }
        return out.c_str();
    };
private:
    std::string _msg;
    unsigned int _pid;
    std::string _socket_name;
    stack_state _state;
};

customException::customException(const char* m,
                                 unsigned int p,
                                 const char* s,
                                 customException::stack_state state) :
                                    _msg(m),
                                    _pid(p),
                                    _socket_name(s),
                                    _state(state) {}

template <typename T>
struct simpleFIFO
{
    simpleFIFO();
    ~simpleFIFO();
    void push(const T& elt)  throw();
    T pop() throw();
    void clear();
    size_t size();
    void content(std::ostream& outstream = std::cout) const;

private:
    static const unsigned int MAX_STACK_SIZE = 10;
    unsigned int _elt_count;
    T _buf[MAX_STACK_SIZE];
};

template <typename T>
simpleFIFO<T>::simpleFIFO() : _elt_count(0){}

template <typename T>
simpleFIFO<T>::~simpleFIFO(){
    clear();
}

template<typename T>
void simpleFIFO<T>::push(const T& elt)  throw()
{
    if(_elt_count < MAX_STACK_SIZE) {
        _buf[_elt_count] = elt;
        _elt_count++;
    }
    else
    {
        throw customException("Not enough room in simpleFIFO !",
                              1234,
                              "UNIX SOCKET:14569",
                              customException::stack_state::FULL);
    }
}

template<typename T>
T simpleFIFO<T>::pop()  throw()
{
    T out;
    if(_elt_count > 0) {
        out = _buf[_elt_count];
        _elt_count--;
    }
    else
    {
        throw customException("Stack is empty, cannot pop data from it !",
                              1234,
                              "UNIX SOCKET:14569",
                              customException::stack_state::FULL);
    }
    return out;
}

template<typename T>
void simpleFIFO<T>::content(std::ostream& outstream) const
{
   for (auto &i : _buf)
   {
       outstream << i << std::endl;
   }
}

template<typename T>
void simpleFIFO<T>::clear()
{
    if(_elt_count > 0) {
        for (auto &i : _buf) {
            i = 0;
        }
        _elt_count = 0;
    }
    // Do not throw an exception if we try to clean this fifo several times consecutively
}

template<>
void simpleFIFO<std::string>::clear()
{
    if(_elt_count > 0) {
        for (auto &i : _buf) {
            i.clear();
        }
        _elt_count = 0;
    }
    // Do not throw an exception if we try to clean this fifo several times consecutively
}


int main (int argc, char ** argv)
{
    simpleFIFO<std::string> stack_trace;
    try {
        stack_trace.push("main()");
        stack_trace.push("init_SPI()");
        stack_trace.push("init_SPI_peripheral()");
        stack_trace.push("toggle_pin()");
        stack_trace.content(std::cout);
        stack_trace.clear();
        stack_trace.push("main()");
        std::string function = stack_trace.pop();
        std::cout << "Read function " << function << " from stack_trace " << std::endl;
        function = stack_trace.pop();   // should throw an exception
        stack_trace.clear();
    }
    catch (const customException& e)
    {
        e.what();
    }
    return 0;
}