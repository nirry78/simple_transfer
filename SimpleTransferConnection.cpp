#include "SimpleTransferConnection.h"

SimpleTransferConnection::SimpleTransferConnection(PlatformSocketType socketHandle):
    mSocketHandle(socketHandle)
{
    std::cout << "SimpleTransferConnection::Init" << std::endl;
}

SimpleTransferConnection::~SimpleTransferConnection()
{
    std::cout << "SimpleTransferConnection::Close" << std::endl;

    PlatformCloseSocket(mSocketHandle);
    mSocketHandle = PLATFORM_INVALID_SOCKET_HANDLE;
}
