#ifndef _BAG_H
#define _BAG_H
#include <pthread.h>
#include <semaphore.h>

// bounded bag with blocking add and take operations

typedef struct {
    int     size;  // maximum number of elements (== length of 'elem' array)
    void ** elem;  // array of pointer to elements (each pointer has type 'void*' )
    int     count; // number of elements currently in the buffer
    sem_t places_libres;
    sem_t places_pleines;
    sem_t semCount;
    int is_closed; // boolean. cf last exercice
} bag_t ;

// Create a new bag with room for 'size' elements
bag_t * bb_create(int size);

// Insert an element in the bag.
// - if bag is full, block until there is room
void bb_add(bag_t *b, void * element);

// Retrieve an element from the bag
// - if bag is non-empty: remove one element and return it
// - if bag is empty and open, block until something is added
// - if bag is empty and closed return NULL
void* bb_take(bag_t *b);

// Close the bag. When a bag is closed:
// - closing it again is an error
// - calling bb_add is an error
// - bb_take doesn't block anymore on an empty bag, but returns NULL instead
// - all threads previously blocked in bb_take are unblocked (up to N of them)
void bb_close(bag_t *bag, int N);

#endif
