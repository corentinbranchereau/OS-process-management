#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#include "bag.h"

bag_t * bb_create(int size)
{
    assert(size > 0);

    bag_t *bag=malloc(sizeof(bag_t));
    assert(bag != NULL);

    bag->elem = malloc( size * sizeof(void*));
    assert(bag->elem != NULL);

    bag->size  = size;
    bag->count = 0;
    bag->is_closed = 0;

    sem_init(& bag->places_pleines, 0, 0);
    sem_init(& bag->semCount, 0, 1);
    sem_init(& bag->places_libres, 0, size);

    return bag;
}

void bb_add(bag_t * bag, void * element)
{
    assert(bag != NULL);                 // sanity check
    if(bag-> is_closed == 0)   // adding to a closed bag is an error
	{
      //while( bag->count >= bag->size ) { } // CAUTION: this synchronization is bogus
      sem_wait(& bag->places_libres);
      sem_wait(&bag->semCount);
      assert( bag->count < bag->size ); // sanity check
      bag->elem[bag->count] = element;
      bag->count += 1;
      sem_post(&bag->semCount);
      sem_post(&bag->places_pleines);
  }
}

void * bb_take(bag_t *bag)
{
    assert(bag != NULL); // sanity check

    //while( bag->count <= 0 ) { } // CAUTION: this synchronization is bogus


    if(bag->is_closed==0)
    {
      sem_wait(&bag->places_pleines);
      sem_wait(&bag->semCount);
      if( (bag->is_closed == 1) && (bag->count == 0) )
		{
			sem_post(& bag->semCount);
			return NULL;
		}
      assert( bag->count > 0); // sanity check
      bag->count -= 1;
      void *r = bag->elem[bag->count];
      sem_post(&bag->semCount);
      sem_post(&bag->places_libres);
      usleep(10);// artificial delay to increase the occurence of race conditions
      return r;
    }else
    {
      return NULL;
    }

}

void bb_close(bag_t *bag, int N)
{
    int i;
    bag->is_closed=1;
    for(i=0;i<N;i++)
    {
        sem_post(&bag->places_pleines);
    }
}
