#include <iostream>
#include <thread>
#include <mutex>
#include <cstring>

using namespace std;

static volatile mutex mtx;

#define S_SIZE 20
#define S_MSG_SIZE 256

enum ECode {
    NO_ERROR=0 ,
    NULL_PTR ,
    STACK_FULL ,
    STACK_EMPTY,
    UNKNOWN
};

static struct stack
{
public:
    ECode push(char* msg , size_t sz);
    ECode pop(char*);
    char* get_element(uint8_t i);
    uint8_t get_element_count() {return element_count;}
    void flush();
    void quick_flush();

protected:
    uint8_t element_count;
    char s [S_SIZE][S_MSG_SIZE];
} error_stack ;

void thread_function(int id,int loops)
{
    static thread_local uint16_t retries = 0;
    for(int i = 0; i< loops;i++)
    {
        // We try to lock the mutex.
        // If operation does not succeed (returns false), it means another thread has already locked cout.
        if( mtx.try_lock() == false)
        {
            retries++;
            char msg[S_MSG_SIZE];
            snprintf(msg, S_MSG_SIZE , "Thread %d cannot access to cout ! push message in error stack [%d]. Retries count = %d",
                     id,
                     (error_stack.get_element_count() + 1),
                     retries
                     );
            error_stack.push(msg,S_MSG_SIZE);
        }
        else
        {
            char msg[S_MSG_SIZE];
            cout << "I'm thread " << to_string(id) << endl ;
            if(error_stack.pop(msg)==NO_ERROR)
            {
                cout << msg << endl;
            }
            mtx.unlock();
            {
                this_thread::sleep_for(chrono::milliseconds(50));
            }
        }
    }
}


int main()
{
    thread first(thread_function,1,20);
    thread second(thread_function,2,30);

    first.join();
    second.join();

    cout << "Finished jobs" << endl;
    return 0;
}

// Flushes all data
void stack::flush()
{
    for(uint8_t i = 0 ; i < S_SIZE ; i++ )
    {
        memset(s[i],0,S_MSG_SIZE);
    }
}

// Partial flush (only until current index)
void stack::quick_flush()
{
    for(uint8_t i = 0 ; i < element_count ; i++)
    {
        memset(s[i],0,S_MSG_SIZE);
    }
}

ECode stack::push(char* msg, size_t sz)
{
    if(msg == NULL )
    {
        return NULL_PTR;
    }
    if( element_count + 1 == S_SIZE )
    {
        return STACK_FULL;
    }
    strncpy(s[element_count],msg,sz);
    element_count++;
    return NO_ERROR;
}

ECode stack::pop(char* out)
{
    if(out == NULL ) return NULL_PTR;
    if(element_count == 0) return STACK_EMPTY;
    element_count--;
    strncpy(out,s[element_count],S_MSG_SIZE);
    memset(s[element_count],0,S_MSG_SIZE);
    return NO_ERROR;
}

char* stack::get_element(uint8_t in)
{
    if(element_count + 1 >= in)
    {
        return s[in];
    }
    else
    {
        return NULL;
    }
}