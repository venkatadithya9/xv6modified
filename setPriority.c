#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

int main(int argc, char *argv[])
{
    if(argc<=2)
    {
        printf(1,"Wrong input format\n");
        exit();
    }
    else
    {
        if(set_priority(atoi(argv[1]), atoi(argv[2])) < 0)
        {
            printf(1,"Wrong input, check pid and priority values\n");
        }
    }
    exit();
}