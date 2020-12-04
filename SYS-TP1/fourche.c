#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char** argv)
{
    int pidParent=getpid();
    printf("%d: Hello World \n", pidParent);
    int* a=malloc(sizeof(int));
	*a=3;
    int pid=fork();
    int* b=malloc(sizeof(int));
	*b=4;
    if(pid!=0)
    {
	*b=6;
      printf("%d: %p je %p suis le Parent %d \n", getpid(),a,b,*b);
    }
    else
    {
      printf("%d: %p je %p suis l'enfant %d \n", getpid(),a,b, *b);
    }
	wait(NULL);
	sleep(2);
    return 0;
}
