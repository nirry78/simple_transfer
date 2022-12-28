#ifndef __PLATFORM_H
#define __PLATFORM_H

#ifdef _WIN32
#include <Winsock2.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <memory>

#ifdef _WIN32
typedef SOCKET PlatformSocketType;
#define PLATFORM_INVALID_SOCKET_HANDLE  INVALID_SOCKET
#define PLATFORM_BOTH_DIRECTIONS        SD_BOTH
#define PlatformCloseSocket(s)          closesocket(s)
typedef int                             socklen_t; 
#else
typedef int PlatformSocketType;
#define PLATFORM_INVALID_SOCKET_HANDLE  (-1)
#define PLATFORM_BOTH_DIRECTIONS        SHUT_RDWR
#define PlatformCloseSocket(s)          close(s)
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
