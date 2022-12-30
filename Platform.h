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

#include <stdarg.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <memory>
#include <array>
#include <thread>
#include <string_view>
#include <source_location>

#ifdef _WIN32
typedef SOCKET PlatformSocketType;
#define PLATFORM_INVALID_SOCKET_HANDLE  INVALID_SOCKET
#define PLATFORM_BOTH_DIRECTIONS        SD_BOTH
#define PlatformCloseSocket(s)          closesocket(s)
typedef int                             socklen_t;
typedef SSIZE_T                         ssize_t;
typedef int                             PlatformRecvResult;
#else
typedef int PlatformSocketType;
#define PLATFORM_INVALID_SOCKET_HANDLE  (-1)
#define PLATFORM_BOTH_DIRECTIONS        SHUT_RDWR
#define PlatformCloseSocket(s)          close(s)
typedef ssize_t                         PlatformRecvResult;
#endif

typedef enum {
    LOG_ERROR,
    LOG_INFO,
    LOG_VERBOSE,
} PlatformErrorLevel;

class Platform
{
    private:
        static uint32_t initializeCount;
        static bool     mVerboseOutput;

        static void     Startup();
        static void     Cleanup();
    public:
                        Platform();
        virtual         ~Platform();

        void            Log(PlatformErrorLevel errorLevel, const char *format, ...);
        void            Log(const std::string_view message,
                            const std::source_location location = std::source_location::current());
        void            SetVerbose();

};

#endif
