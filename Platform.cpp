#include "Platform.h"

uint32_t Platform::initializeCount = 0;

Platform::Platform()
{
    if (initializeCount++ == 0)
    {
        Startup();
    }
}

Platform::~Platform()
{
    if (--initializeCount == 0)
    {
        Cleanup();
    }
}

void Platform::Startup()
{
#ifdef _WIN32
    WSADATA wsadata;
    WSAStartup(0x0202, &wsadata);
#endif
}

void Platform::Cleanup()
{
#ifdef _WIN32
    WSACleanup();
#endif
}


int PlatformStartup()
{

    return EXIT_SUCCESS;
}

void PlatformCleanup()
{
}
