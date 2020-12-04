#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>





int main(int argc, char** argv)
{
    //printf("Bonjour je suis '%d'\n",argc);
    printf("%d: debut %d\n", getpid(),atoi(argv[1]));
    int i;
    for(i=0;i<atoi(argv[1]);++i)
    {
      printf("%d: %d\n", getpid(),atoi(argv[1])-i);
      sleep(1);
    }
    printf("%d: fin\n", getpid());
    return 0;
}
