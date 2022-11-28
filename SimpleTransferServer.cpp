#include "SimpleTransferServer.h"

SimpleTransferServer::SimpleTransferServer()
{
    mReceiverBuffer = new char[65536];
}

SimpleTransferServer::~SimpleTransferServer()
{
    if (mReceiverBuffer)
    {
        delete mReceiverBuffer;
        mReceiverBuffer = NULL;
    }
}

bool SimpleTransferServer::HandleClient()
{
    bool result = true;
    std::ofstream file;

    try
    {
        file.open(std::string{"c:\\temp\\channel_sounding.bin"});
        for(;;)
        {
            int res = recv(mClientSocketHandle, mReceiverBuffer, 65536, 0);
            if (res > 0)
            {
                file.write(mReceiverBuffer, res);
            }
        }
        file.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return result;
}

bool SimpleTransferServer::StartServer()
{
    mSocketHandle = socket(AF_INET, SOCK_STREAM, 0);
    if (mSocketHandle == PLATFORM_INVALID_SOCKET_HANDLE)
    {
        perror("socket");
        return false;
    }

#ifdef _WIN32
    sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_port = htons(4959),
        .sin_addr = {
            .S_un = {
                .S_addr = htonl(INADDR_ANY)
            }
        }
    };
#else
    sockaddr_in address = {
        .sa_family = AF_INET,
    };
#endif

    const int enable = 1;
    if (setsockopt(mSocketHandle, SOL_SOCKET, SO_REUSEADDR, (const char*)&enable, sizeof(int)) < 0)
    {
        perror("setsockopt(SO_REUSEADDR) failed");
        return false;
    }

    if (bind(mSocketHandle, (const sockaddr*)&address, sizeof(address)))
    {
        perror("bind");
        return false;
    }

    if (listen(mSocketHandle, 10))
    {
        perror("bind");
        return false;
    }

    return true;
}

int SimpleTransferServer::Run(int argc, char **argv)
{
    int result = EXIT_SUCCESS;

    if (!StartServer())
    {
        return EXIT_FAILURE;
    }

    for(;;)
    {
        sockaddr_in clientAddress;
        int clientAddressLen = sizeof(clientAddress);

        mClientSocketHandle = accept(mSocketHandle, (sockaddr *)&clientAddress, &clientAddressLen);
        if (mClientSocketHandle != PLATFORM_INVALID_SOCKET_HANDLE)
        {
            std::cout << "Client connected" << std::endl;
            HandleClient();
            std::cout << "Client disconnected" << std::endl;
            shutdown(mClientSocketHandle, SD_BOTH);
            closesocket(mClientSocketHandle);
        }
        else
        {
            perror("accept");
            return false;
        }
    }

    std::cout << "Server initialized" << std::endl;

    return result;
}

int main(int argc, char **argv)
{
    SimpleTransferServer *sts = new SimpleTransferServer();
    int result = EXIT_FAILURE;

    /* Check the application allocation and start it */
    if (sts)
    {
        result = sts->Run(argc, argv);
        delete sts;
    }

    return result;
}
