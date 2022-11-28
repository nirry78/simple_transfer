#ifndef __PLATFORM_H
#define __PLATFORM_H

#ifdef _WIN32
#include <Winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#endif

#include <iostream>
#include <fstream>
#include <string>

#ifdef _WIN32
typedef SOCKET PlatformSocketType;
#define PLATFORM_INVALID_SOCKET_HANDLE INVALID_SOCKET
#else
typedef int PlatformSocketType;
#define PLATFORM_INVALID_SOCKET_HANDLE (-1)
#endif

class Platform
{
    private:
        static uint32_t initializeCount;

        static void     Startup();
        static void     Cleanup();
    public:
                        Platform();
        virtual         ~Platform();

};

#endif
