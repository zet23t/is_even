#if __INCLUDE_LEVEL__ < 1024
#if __INCLUDE_LEVEL__ % 2 == 0
case __INCLUDE_LEVEL__: return 1;
#else
case __INCLUDE_LEVEL__: return 0;
#endif
#include "is_even.h"
#endif