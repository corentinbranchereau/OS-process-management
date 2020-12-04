#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>


void afficher(char* crible, int n)
{
    int i=0;
    printf("nombre premiers jusqu'à %d: ",n);
    for(i=2;i<n;++i)
    {
      if(crible[i]==1)
        printf("%d ",i);
    }

}

void rayer_multiples(char* crible, int n, int k)
{
    // TODO: rayer (i.e. passer à zéro) tous les multiples de k qui sont plus petits que n
    int i;
    for(i=k+1;i<n;++i)
    {
      if(i%k==0)
      {
        crible[i]=0;

      }
    }
}


int main(int argc, char **argv)
{
    int n=1000;

    if(argc>1)
    {
        n = atoi(argv[1]);
        assert( n > 0 );
    }

    //char buffer[1000]; //q1
    //assert(n <= 1000);


    // char * crible = (char*)&buffer ;  // q1
    char * crible = (char*) mmap(NULL,n*sizeof(char),(PROT_READ|PROT_WRITE),MAP_SHARED|MAP_ANONYMOUS,0,0);  // q2
    if (crible == MAP_FAILED)
        printf("error mmap failed");




    for(int i=0; i<n; i++)
    {
        crible[i] = 1;//par défaut: pas encore barré
    }

    int pidParent=1;
    for(int k=2; k<n; k++)
    {
        if(pidParent!=0) //exécuté par l'enfant
        {
          pidParent=fork();
        }
        if(pidParent==0) //exécuté par le parent
        {
            rayer_multiples(crible, n, k);
            wait(NULL);   //attend que l'enfant ai fini
            exit(0);      // fin du programme avec 0 en code de retour. Seul le dernier enfant va executer afficher()
        }
    }

    //if(pidParent!=0)     // solution si on n'utilise pas exit();
    //{
      afficher(crible, n);
    //}

    return 0;
}
