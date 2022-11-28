#include "SimpleTransferClient.h"

SimpleTransferClient::SimpleTransferClient()
{

}

SimpleTransferClient::~SimpleTransferClient()
{

}


int SimpleTransferClient::Run(int argc, char **argv)
{
    int result = EXIT_SUCCESS;

    return result;
}

int main(int argc, char **argv)
{
    SimpleTransferClient *simpleTransferClient = new SimpleTransferClient();
    int result = EXIT_FAILURE;

    /* Check the application allocation and start it */
    if (simpleTransferClient)
    {
        result = simpleTransferClient->Run(argc, argv);
        delete simpleTransferClient;
    }

    return result;
}
