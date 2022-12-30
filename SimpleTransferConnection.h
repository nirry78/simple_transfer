#ifndef __SIMPLE_TRANSFER_CONNECTION_H
#define __SIMPLE_TRANSFER_CONNECTION_H

#include "Platform.h"

class SimpleTransferConnectionCallback
{
    public:
        virtual void OnConnectionClose(std::shared_ptr<class SimpleTransferConnection>connection) = 0;
};

class SimpleTransferConnection: public Platform
{
    private:
        PlatformSocketType                  mSocketHandle;
        SimpleTransferConnectionCallback   *mCallback;
        std::unique_ptr<std::thread>        mThread;
        std::unique_ptr<char[]>             mReceiveBuffer;
        PlatformRecvResult                  mReceiveOffset;
        PlatformRecvResult                  mReceiveLength;

        void    ProcessRequest(std::string &request);
        void    ProcessSocket();
    public:
                SimpleTransferConnection(PlatformSocketType socketHandle,
                                         SimpleTransferConnectionCallback *callback = NULL);
        virtual ~SimpleTransferConnection();
};

#endif /* __SIMPLE_TRANSFER_CONNECTION_H */