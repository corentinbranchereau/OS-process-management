#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>



int main(int argc, char** argv)
{
  assert(argc>3);
  int pidParent=1;
  int N=atoi(argv[2]);
  int i;
  int nbProcess=1;

    for(i=3;i<argc;++i)
    {
      //rentre seulement dans l'unique parent
      if(pidParent!=0)
      {
        if(nbProcess<=N) //si dépasse le nbproceess max N, on attend la fin d'un process
        {
            pidParent=fork();
            nbProcess++;
        }
        else
        {
            wait(NULL);
            pidParent=fork();
        }
      }

      //si on est un pid fils, on lance la commande
      if(pidParent==0)
      {
        execl(argv[1],argv[1],argv[i],NULL);
        break;
      }
    }// fin du for


    if(pidParent!=0) //On attend dans le parent la fin de tous les programmes fork
    {
    for(i=2;i<argc;++i)
      wait(NULL);
    }
    return 0;
}
