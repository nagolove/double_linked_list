#include "dlist.h"

#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void knot_storage_init(KnotStorage *storage, int maxnum) {
    assert(storage);
    assert(maxnum > 3);

    storage->knots = calloc(maxnum, sizeof(storage->knots[0]));
    storage->knotsnum_max = maxnum;
    storage->knotsnum = 0;

    /*Knot *current = &storage->knots[0];*/
    /*current->prev_free = NULL;*/
    /*current->next_free = NULL;*/

    for(int i = 0; i < maxnum - 1; ++i) {
        storage->knots[i].next_free = &storage->knots[i + 1];

        /*current->next_free = &st->tanks[i];*/
        /*current->prev_free = prev_free;*/
        /*prev_free = current;*/
        /*current = current->next;*/
        /*printf("i %d\n", i);*/

    }

    for(int i = 1; i < maxnum; ++i) {
        storage->knots[i].prev_free = &storage->knots[i - 1];
    }

    storage->knots[0].prev_free = NULL;
    storage->knots[maxnum - 1].next_free = NULL;

    storage->knots_free = &storage->knots[0];
    storage->knots_allocated = NULL;
}

void knot_storage_free(KnotStorage *storage) {
    assert(storage);
    free(storage->knots);
    memset(storage, 0, sizeof(*storage));
}

Knot *knot_alloc(KnotStorage *storage) {
    assert(storage);
    if (storage->knotsnum == storage->knotsnum_max) {
        return NULL;
    }
    assert(storage->knots_free);
    Knot *new = storage->knots_free;
    new->next_free = NULL;
    new->prev_free = NULL;
    storage->knots_free = storage->knots_free->next_free;

    if (storage->knots_free)
        storage->knots_free->prev_free = NULL;

    if (!storage->knots_allocated) {
        storage->knots_allocated = new;
        new->next_allocated = NULL;
        new->prev_allocated = NULL;
    } else {
        new->prev_allocated = NULL;
        storage->knots_allocated->prev_allocated = new;
        new->next_allocated = storage->knots_allocated;
        storage->knots_allocated = new;
    }

    return new;
}

void knot_free(KnotStorage *storage, Knot *knot) {
}

void knot_foreach(KnotStorage *storage, KnotIterFunc func) {
}

