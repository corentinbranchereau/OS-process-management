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
        char* doc=argv[i];
        int idFile=open(doc,O_RDONLY);
        char buff[5000];
        int i=0;
        while(read(idFile,buff+i,1)==1)
        {
          write(1,buff+i,1);
          i++;
        }

        close(idFile);
    }

    return 0;
}
