#ifndef PSEUDO_VECTOR_HEADER
#define PSEUDO_VECTOR_HEADER

#include <iostream>
#include <vector>
#include <malloc.h>
#include <string>

namespace pseudo_vector_test
{

    template<class T>
    struct generic_list {
        generic_list();
        ~generic_list();

        void push(T const& elt);
        T const& pop();

        size_t size();
        void clear();

        void print();
        T& operator[](unsigned int index);
    private:
        size_t element_count;
        T* list;
    };

    template<class T>
    inline generic_list<T>::generic_list() :
                                element_count(0),
                                list(nullptr)
                                {}

    template<class T>
    inline generic_list<T>::~generic_list(){
        clear();
    }

    template<class T>
    inline void generic_list<T>::clear()
    {
        if(nullptr != list && 0 != element_count) {
            element_count = 0 ;
            free(list);
            list = nullptr;
        }
    }

    template<class T>
    inline void generic_list<T>::print()
    {
        if(nullptr != list && 0 != element_count) {
            for (unsigned int i = 0 ; i < element_count ; i++)
            {
                std::cout << *(list + i) << "\n";
            }
        }
    }

    template<class T>
    inline void generic_list<T>::push(T const& elt)
    {
        if (nullptr == list) {
            list = (T*) malloc(sizeof(T));
            if (nullptr == list){
                throw ("Cannot allocate memory for new generic_list ! ");
            }
            else
            {
                *list = elt;
                element_count++;
            }
        }
        else {
            T* realloc_ptr = nullptr;
            realloc_ptr = static_cast<T*>(realloc(list, sizeof(T) * (element_count + 1)));
            if(nullptr == realloc_ptr) {
                free(list);
                throw ("Cannot reallocate memory for generic_list : no more memory available! ");
            }
            else
            {
                list = realloc_ptr;
                list[element_count] = elt;
                element_count++;
            }

        }
    }

    template<class T>
    inline T const& generic_list<T>::pop()
    {
        if (0 != element_count && nullptr != list) {
            element_count--;
            return list[element_count];
        }
        throw "List is empty ! \n";
    }

    template<class T>
    inline T& generic_list<T>::operator[](unsigned int index)
    {
        if ((element_count - 1) >= index && list != nullptr)
        {
            return list[index];
        }

        throw "Cannot access expected list index : requested cell is not allocated! \n";
    }

    template<class T>
    inline size_t generic_list<T>::size()
    {
        return element_count;
    }
}
#endif