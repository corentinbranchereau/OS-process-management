#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct {
    int sexe; // 1=Garcon, 2=Fille
    char prenom[25];
    int annee; // 1900..2018
    int nombre; // d'enfants nés cette année avec ce prénom
} tuple;

int main(int argc, char **argv)
{
    int idFile=open("prenoms.dat",O_RDWR);
    struct stat buf;
    fstat(idFile,&buf);
    tuple* crible = (tuple*) mmap(NULL,buf.st_size,(PROT_READ|PROT_WRITE),MAP_SHARED,idFile,0);
    if (crible == MAP_FAILED)
        printf("error mmap failed");

    int sizeTuple= sizeof(tuple);
    //write(1,crible[0],sizeTuple);
    int nombre=0;
    //int max=0;

    for(int i=0;i<buf.st_size/sizeTuple;++i)
    {
      if(crible[i].sexe!=0) //&& strlen(crible[i].prenom)>max
      {
        for(int j=0;j<25;++j)
        {
          crible[i].prenom[j]+=32;
        }
          printf("tuple: %d, %s, %d, %d \n",crible[i].sexe,crible[i].prenom,crible[i].annee,crible[i].nombre);
          //max=strlen(crible[i].prenom);

          nombre++;
      }

    }
      printf("%d",nombre);
    close(idFile);



    return 0;
}
