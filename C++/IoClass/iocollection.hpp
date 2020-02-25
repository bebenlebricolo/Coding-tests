#ifndef _IO_COLLECTION_HEADER_
#define _IO_COLLECTION_HEADER_

#include "io.h"
#include "config.h"

namespace peripheral
{

// No instanciation nor inheritance possible
class ioCollection final
{
    ioCollection() = delete;
    virtual ~ioCollection()=0;
    static io collection[(const uint32_t) userIo::user_io_count];
public:
    static inline io& get(const userIo& _target)
    {
        auto index = static_cast<const uint32_t>(_target);
        return collection[index];
    }
};

}


#endif /* _IO_COLLECTION_HEADER_ */
