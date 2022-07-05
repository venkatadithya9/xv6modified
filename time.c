#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf(1, "No process given to examine\n");
        exit();
    }
    else
    {    
        int wtm,rtm;
        int chk = fork();
        if(chk < 0) printf(2, "Fork error");
        else if (chk == 0)
        {
            exec(argv[1], &argv[1]);
            printf(1, "%s could not be executed\n", argv[1]);
            exit();
        }
        else 
        {
            waitx(&wtm, &rtm);
            printf(1, "\nWait time = %d\nRun time = %d\n", wtm,rtm);
        }
    }

    exit();
}