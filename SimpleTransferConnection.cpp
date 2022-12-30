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

void SimpleTransferConnection::ProcessRequest(std::string &request)
{
    std::list<std::string> fields;
    std::string operation;
    size_t offset = 0;
    size_t position;

    position = request.find_first_of('\r');
    if (position != std::string::npos)
    {
        operation = request.substr(0, position);
        offset = position + 2;
    }
    else
    {
        return;
    }

    while ((position = request.find_first_of('\r', offset)) != std::string::npos)
    {
        if (position - offset)
        {
            std::string field = request.substr(offset, position - offset);
            fields.push_back(field);
        }
        offset = position + 2;
    }

    std::cout << "Operation: " << operation << std::endl;
    for (auto field : fields)
    {
        std::cout << "Field: " << field << std::endl;
    }
}

void SimpleTransferConnection::ProcessSocket()
{
    Log(LOG_INFO, "Connection thread is running (socketHandle: %d)", mSocketHandle);

    for (;;)
    {
        PlatformRecvResult res = recv(mSocketHandle,
                                      mReceiveBuffer.get() + mReceiveOffset,
                                      mReceiveLength - mReceiveOffset - 1, 0);
        if (res > 0)
        {
            mReceiveOffset += res;
            mReceiveBuffer[mReceiveOffset] = 0;

            for (auto index = 0; index < mReceiveOffset; index++)
            {
                if (mReceiveBuffer[index + 0] == '\r' &&
                    mReceiveBuffer[index + 1] == '\n' &&
                    mReceiveBuffer[index + 2] == '\r' &&
                    mReceiveBuffer[index + 3] == '\n')
                {
                    std::string request(mReceiveBuffer.get(), index + 3);
                    ProcessRequest(request);
                }
            }
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
