#include "SimpleTransferConnection.h"

SimpleTransferConnection::SimpleTransferConnection(PlatformSocketType socketHandle, 
                                                   SimpleTransferConnectionCallback *callback):
    mSocketHandle(socketHandle), 
    mCallback(callback), 
    mReceiveOffset(0), 
    mReceiveLength(65536)
{
    std::cout << "SimpleTransferConnection::Init (socketHandle: " << socketHandle << ")" << std::endl;

    mReceiveBuffer = std::make_unique<char[]>(mReceiveLength);

    mThread = std::make_unique<std::thread>([](SimpleTransferConnection *obj) {
        obj->ProcessSocket();   
    }, this);
}

SimpleTransferConnection::~SimpleTransferConnection()
{
    std::cout << "SimpleTransferConnection::Close" << std::endl;

    if (mSocketHandle != PLATFORM_INVALID_SOCKET_HANDLE)
    {
        PlatformCloseSocket(mSocketHandle);
        mSocketHandle = PLATFORM_INVALID_SOCKET_HANDLE;
    }

    mThread->join();
}

void SimpleTransferConnection::ProcessSocket()
{
    Log(LOG_INFO, "Connection thread is running (socketHandle: %d)", mSocketHandle);
    for (;;)
    {
        ssize_t res = recv(mSocketHandle, 
                           mReceiveBuffer.get() + mReceiveOffset, 
                           mReceiveLength - mReceiveOffset - 1, 0);
        if (res > 0)
        {
            mReceiveOffset += res;
            mReceiveBuffer[mReceiveOffset] = 0;

            for (auto index = 0; index < mReceiveOffset; index++)
            {

            }

            Log(LOG_VERBOSE, "Received %zd bytes", res);

            std::cout << mReceiveBuffer.get() << std::endl;
        }
        else
        {
            perror("recv");
            break;
        }
    }

    shutdown(mSocketHandle, PLATFORM_BOTH_DIRECTIONS);

    Log(LOG_INFO, "Connection thread is stopped");

    if (mCallback)
    {
        mCallback->OnConnectionClose(std::shared_ptr<SimpleTransferConnection>(this));
    }
}
