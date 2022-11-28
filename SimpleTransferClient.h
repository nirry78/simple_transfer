#ifndef __SIMPLE_TRANSFER_CLIENT_H
#define __SIMPLE_TRANSFER_CLIENT_H

#include "Platform.h"

class SimpleTransferClient: public Platform
{
    private:

    public:
                        SimpleTransferClient();
        virtual         ~SimpleTransferClient();

        int             Run(int argc, char **argv);
};

#endif /* __SIMPLE_TRANSFER_CLIENT_H */
