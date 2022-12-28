#ifndef __SIMPLE_TRANSFER_CONNECTION_H
#define __SIMPLE_TRANSFER_CONNECTION_H

#include "Platform.h"

class SimpleTransferConnection
{
    private:
        PlatformSocketType      mSocketHandle;
    public:
                SimpleTransferConnection(PlatformSocketType socketHandle);
        virtual ~SimpleTransferConnection();
};

#endif /* __SIMPLE_TRANSFER_CONNECTION_H */