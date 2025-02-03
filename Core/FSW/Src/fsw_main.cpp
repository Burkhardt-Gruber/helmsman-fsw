#include "fsw_main.h"
#include "worker.h"

/**
 * Create the list of workers for the FSW
 */
static void create_workers();

extern "C" int fsw_main()
{
    create_workers();
    return 0;
}

void create_workers()
{
    
}


