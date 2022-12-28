#include "Platform.h"
#include "SimpleTransferConnection.h"

int main(int argc, char **argv)
{
    std::shared_ptr<SimpleTransferConnection> connection = std::make_shared<SimpleTransferConnection>(0);
    std::list<std::shared_ptr<SimpleTransferConnection>> connectionList;
    connectionList.push_back(connection);
    for (auto connection : connectionList)
    {
        std::cout << "Connection found" << std::endl;
    }
    

    return EXIT_SUCCESS;
}
