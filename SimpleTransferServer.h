#ifndef __SIMPLE_TRANSFER_SERVER_H
#define __SIMPLE_TRANSFER_SERVER_H

#include "Platform.h"

class SimpleTransferServer: public Platform
{
    private:
        PlatformSocketType  mClientSocketHandle;
        PlatformSocketType  mSocketHandle;
        char                *mReceiverBuffer;

        bool                HandleClient();
        bool                StartServer();
    public:
                            SimpleTransferServer();
        virtual             ~SimpleTransferServer();

        int                 Run(int argc, char **argv);
};

#endif /* __SIMPLE_TRANSFER_SERVER_H */