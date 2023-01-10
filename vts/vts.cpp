#include "vts.h"

#ifdef VOPEN_VLOG
vts::vlog* vts::vlog::obj = nullptr;
vts::vlog::vlog()
{
    vec.push_back("\033[31m[Error");
    vec.push_back("\033[33m[Warning");
    vec.push_back("\033[32m[Debug");
    vec.push_back("[Info");
}
#endif //OPEN_VLOG
