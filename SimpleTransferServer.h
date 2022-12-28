#ifndef __SIMPLE_TRANSFER_SERVER_H
#define __SIMPLE_TRANSFER_SERVER_H

#include "Platform.h"
#include "SimpleTransferConnection.h"

class SimpleTransferServer: public Platform, public SimpleTransferConnectionCallback
{
    private:
        std::list<std::shared_ptr<SimpleTransferConnection>> mConnectionList;
        PlatformSocketType  mClientSocketHandle;
        PlatformSocketType  mSocketHandle;
        char                *mReceiverBuffer;

        bool                HandleClient();
        virtual void        OnConnectionClose(std::shared_ptr<class SimpleTransferConnection>connection);
        bool                StartServer();
    public:
                            SimpleTransferServer();
        virtual             ~SimpleTransferServer();

        int                 Run(int argc, char **argv);
};

#endif /* __SIMPLE_TRANSFER_SERVER_H */