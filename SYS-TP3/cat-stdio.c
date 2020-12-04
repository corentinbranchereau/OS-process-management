#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    for(int i=1; i<argc ; i++)
    {

        printf("%s\n",argv[i]);
        char * doc=argv[i];
        FILE * f=fopen(doc,"r+");
        while(feof(f)==0)
        {
          putchar(fgetc(f));
        }
        fclose(f);
    }

    return 0;
}
