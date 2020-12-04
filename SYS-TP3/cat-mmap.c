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
        int idFile=open(doc,O_RDWR);


      struct stat buf;
      fstat(idFile,&buf);
      //printf("%ld",buf.st_size);
      char * crible = (char*) mmap(NULL,buf.st_size,(PROT_READ|PROT_WRITE),MAP_SHARED,idFile,0);
      if (crible == MAP_FAILED)
          printf("error mmap failed");

      write(1,crible,buf.st_size);
      close(idFile);
    }

    return 0;
}
