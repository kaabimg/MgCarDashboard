#ifndef MGGLOBAL_H
#define MGGLOBAL_H

#include "mgio.h"

#define MG_PRIVATE(Type)\
    Type##Private * d_ptr;\
    friend class Type##Private;


#endif // MGGLOBAL_H
