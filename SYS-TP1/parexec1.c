#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>



int main(int argc, char** argv)
{
  assert(argc>2);
  int pidParent=1;
  int i;

    for(i=2;i<argc;++i)
    {
      if(pidParent!=0)
      {
        pidParent=fork();
      }
      if(pidParent==0)
      {
        execl(argv[1],argv[1],argv[i],NULL);
        break;
      }
    }
    if(pidParent!=0)
    {
    for(i=2;i<argc;++i)
      wait(NULL);
    }
    return 0;
}
