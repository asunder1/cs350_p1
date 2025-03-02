#include "types.h"
#include "stat.h"
#include "user.h"

/* ATTENTION: to ensure correct compilation of the base code, 
   stub functions for the system call user space wrapper functions are provided. 
   REMEMBER to disable the stub functions (by commenting the following macro) to 
   allow your implementation to work properly. */

// #define STUB_FUNCS
// #ifdef STUB_FUNCS
// void mkdirn(char * count, char* d2) {} // Commented by Alex E. to support mkdirn
// #endif


/* IMPORTANT INSTRUCTION: the code below should not be changed. 
    Failure to follow this instruction will lead to zero point 
	for this part */

int 
main(int argc, char * argv[])
{    
    if(argc != 3){
        printf(1, "Please provide the number of direcdtories to create and the name of the directory to create");
        printf(1, "for example: mkdirn 5 mydir");
        printf(1, "will create 5 directories named mydir1, mydir2, mydir3, mydir4, mydir5");
        exit();
    }

    int count = atoi(argv[1]);
	mkdirn(argv[1], argv[2]);
    exit(); //return 0;
}
