#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>



int main(int argc, char** argv)
{
  printf("%d\n",getpid());

  int pid=fork();
  if(pid!=0)
  {
    execl("./rebours","rebours","2",NULL);
  }
  else
  {
    execl("./rebours","rebours","4",NULL);
  }

    return 0;
}
