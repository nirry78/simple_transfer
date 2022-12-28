#include "Platform.h"

uint32_t Platform::initializeCount = 0;
bool Platform::mVerboseOutput = false;

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

void Platform::SetVerbose()
{
    mVerboseOutput = true;
}

void Platform::Log(PlatformErrorLevel errorLevel, const char *format, ...)
{
    va_list va;

    if (errorLevel < LOG_VERBOSE || mVerboseOutput)
    {
        char buffer[512];

        va_start(va, format);
        int pos = vsnprintf(buffer, 512, format, va);
        va_end(va);

        if (pos > 0)
        {
            buffer[pos] = 0;
            std::cout << buffer << std::endl;
        }
    }
}

int PlatformStartup()
{

    return EXIT_SUCCESS;
}

void PlatformCleanup()
{
}
