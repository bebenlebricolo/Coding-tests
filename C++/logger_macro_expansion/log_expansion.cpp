#include <iostream>
#include <string>
#include <cstring>

using namespace std;

struct TestException : public exception 
{
    private:
    string message;
    
    public:
    TestException() throw() :message("Unknown cause"){}
    TestException(string msg) throw() : message(msg) {}
    virtual const char* what() {return message.c_str();} 
    virtual ~TestException() throw() {}
};

// implemented as a singleton
class logger
{
    public:
    enum LoggerLevels {debug=0,info,warning,error,critical,init};
    static logger* get_logger();
    static void purge_logger();
    void log_data(string message, logger::LoggerLevels level, int line, string file, string function, string className);
    void log_raw_exception(TestException &e, int line, string file, string function);

    private:
    static logger* m_instance;
    logger(){};
};
logger* logger::m_instance = nullptr;

#define log_raw(msg,level,line,file,function,class) log->log_data(msg,level,line,file,function,class);
#define log_init(msg,class) log_raw(msg,  logger::LoggerLevels::init ,__LINE__,__FILE__,__func__,class)
#define log_debug(msg,class) log_raw(msg,  logger::LoggerLevels::debug ,__LINE__,__FILE__,__func__,class)
#define log_info(msg,class) log_raw(msg,  logger::LoggerLevels::info ,__LINE__,__FILE__,__func__,class)
#define log_warning(msg,class) log_raw(msg,  logger::LoggerLevels::warning ,__LINE__,__FILE__,__func__,class)
#define log_error(msg,class) log_raw(msg,  logger::LoggerLevels::error ,__LINE__,__FILE__,__func__,class)
#define log_critical(msg,class) log_raw(msg,  logger::LoggerLevels::critical ,__LINE__,__FILE__,__func__,class)
#define log_exception(exception) log->log_raw_exception(exception,__LINE__,__FILE__,__func__);

void throw_exception(string msg)
{
    throw TestException(msg);
}

int main()
{
    logger *log = logger::get_logger();
    log_init("Starting main function","main");
    log_debug("Starting main function","main");
    log_info("Starting main function","main");
    log_warning("Starting main function","main");
    log_error("Starting main function","main");
    log_critical("Starting main function","main");
    try {
        throw_exception("Ho! Ho! Finallyyyy");
    } catch (TestException &e) {
        char error_message[256];
        snprintf(error_message,256,"Caught exception : %s",e.what());
        log_error(string(error_message),"main");
        //log_exception(e);
    } catch (...)
    {
        cerr << "Damn it! " << endl;
    }

    return 0;
}


// Log data and rewrite message string according to targeted log level
void logger::log_data(string message, logger::LoggerLevels level, int line, string file, string function, string className)
{
    string level_str;
    switch(level)
    {
        case logger::LoggerLevels::info :
            level_str = "[INFO] : ";
            break;
        case logger::LoggerLevels::debug:
            level_str = "[DEBUG] : ";
            break;
        case logger::LoggerLevels::warning :
            level_str = "[WARNING] : ";
            break;
        case logger::LoggerLevels::error :
            level_str = "[ERROR] : ";
            break;
        case logger::LoggerLevels::critical :
            level_str = "[CRITICAL] : ";
            break;
        case logger::LoggerLevels::init :
            level_str = "[INIT] : ";
            break;
        default :
            break;
    }
    cout << "[ " << file  << ":" << to_string(line) << " ; " 
         << className << "::" << function << " ] # "
         << level_str << message <<  endl;
}

logger* logger::get_logger()
{
    if(m_instance == nullptr)
    {
        m_instance = new logger;
    }
    return m_instance;
}

void logger::purge_logger()
{
    if(m_instance != nullptr)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

void logger::log_raw_exception(TestException &e, int line, string file, string function)
{
    cout << "[ " << file  << ":" << to_string(line) << " ; " 
         << "::" << function << " ] # "
         << e.what() <<  endl;
}
