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
        file.open(std::string{"c:\\temp\\iqmeasure\\capture.bin"}, std::ios_base::binary);
        for(;;)
        {
            int res = recv(mClientSocketHandle, mReceiverBuffer, 65536, 0);
            if (res > 0)
            {
                file.write(mReceiverBuffer, res);
            }
            else
            {
                break;
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

void SimpleTransferServer::OnConnectionClose(std::shared_ptr<class SimpleTransferConnection>connection)
{
    mConnectionList.remove(connection);
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
        .sin_family = AF_INET,
        .sin_port = htons(4959),
        .sin_addr = {
            .s_addr = htonl(INADDR_ANY)
        }
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

    for (auto index = 1; index < argc; index++)
    {
        if ((argv[index][0] == '/' || argv[index][0] == '-') && argv[index][1] != 0)
        {
            const char option = argv[index][1];

            switch(option)
            {
                case 'v':
                {
                    SetVerbose();
                    break;
                }
            }
        }
    }

    Log(LOG_INFO, "Running server...");
    if (!StartServer())
    {
        return EXIT_FAILURE;
    }

    for(;;)
    {
        sockaddr_in clientAddress;
        socklen_t clientAddressLen = sizeof(clientAddress);

        mClientSocketHandle = accept(mSocketHandle, (sockaddr *)&clientAddress, &clientAddressLen);
        if (mClientSocketHandle != PLATFORM_INVALID_SOCKET_HANDLE)
        {
            try
            {
                std::shared_ptr<SimpleTransferConnection> simpleConnection =
                    std::make_shared<SimpleTransferConnection>(mClientSocketHandle, this);

                Log(LOG_INFO, "Incoming connection");

                mConnectionList.push_back(simpleConnection);
            }
            catch(const std::bad_alloc&)
            {
                shutdown(mClientSocketHandle, PLATFORM_BOTH_DIRECTIONS);
                PlatformCloseSocket(mClientSocketHandle);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else
        {
            perror("accept");
            return false;
        }
    }

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
