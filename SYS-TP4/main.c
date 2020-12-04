#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "mem.h"



void exo1a()
{
  mem_init();
  mem_alloc (42);
  mem_alloc (42);
  mem_alloc (42);
  mem_alloc (42);
  mem_alloc (42);
  mem_alloc (42);
  //mem_release(a);
  char * p7=mem_alloc (42);
  if(p7==NULL)
  {
    printf("Echec allocation 7eme bloc\n");
  }else
  {
    printf("Succes désalocation\n");
  }
  mem_show_heap();
}



void exo1b()
{
  mem_init();
  char* a=mem_alloc (200);
    mem_release(a);
    char * p2=mem_alloc (300);

  if(p2==NULL)
  {
    printf("Echec allocation 2eme bloc\n");
  }
  else
  {
    printf("Succes désalocation\n");
  }
  mem_show_heap();
}






int main()
{
    //exo1a();
    // initialize the allocator
    mem_init();
    mem_show_heap();

    char *p = mem_alloc( 60 );
      char *p1=mem_alloc( 60 );
      char *p2=mem_alloc( 60 );
      char *p3=mem_alloc( 60 );
     //mem_alloc( 8 );
    assert( p != NULL ); // check whether the allocation was successful
    //printf("allocated 42 bytes at %p\n", p);
    mem_show_heap();
    mem_release(p3);
    mem_show_heap();
    mem_release(p2);
    mem_show_heap();
    mem_release(p1);
    mem_show_heap();
    mem_release(p);
    mem_show_heap();
    return 0;
}



// Réponse aux questions
// Après la partie 3, on ne peux plus désallouer le bloc de 200 et réallouer 300
//car on a compartimenté la mémoire
