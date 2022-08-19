#include "dlist.h"

#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void knot_storage_init(KnotStorage *storage, int maxnum) {
    assert(storage);
    assert(maxnum > 3);

    memset(storage, 0, sizeof(*storage));

    storage->last_id = 0;
    storage->knots = calloc(maxnum, sizeof(storage->knots[0]));
    storage->knotsnum_max = maxnum;
    storage->knotsnum = 0;
    storage->free_num = maxnum;

    for(int i = 0; i < maxnum - 1; ++i) {
        storage->knots[i].next_free = &storage->knots[i + 1];
    }
    for(int i = 1; i < maxnum; ++i) {
        storage->knots[i].prev_free = &storage->knots[i - 1];
    }

    storage->knots[0].prev_free = NULL;
    storage->knots[maxnum - 1].next_free = NULL;

    storage->knots_free = &storage->knots[0];
    /*printf("storage->knots_free %p\n", storage->knots_free);*/
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

    storage->free_num--;
    storage->allocated_num++;

    /*printf("storage->knots_free %p\n", storage->knots_free);*/

    assert(storage->knots_free);
    Knot *new = storage->knots_free;

    /*printf("storage->knots_free %p\n", storage->knots_free);*/
    /*printf("storage->knots_free->next_free %p\n", */
            /*storage->knots_free->next_free*/
    /*);*/

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

    new->is_free = false;
    new->is_allocated = true;

    new->next_free = NULL;
    new->prev_free = NULL;

    new->id = storage->last_id++;

    return new;
}

void knot_free(KnotStorage *storage, Knot *knot) {
    assert(storage);
    assert(knot);

    /*knot->id = -1;*/
    storage->free_num++;
    storage->allocated_num--;

    printf(
            "allocated_num %d free_num %d\n",
            storage->allocated_num,
            storage->free_num
    );

    /*printf("knot                        %p\n", knot);*/
    /*printf("storage->knots_allocated    %p\n", storage->knots_allocated);*/

    if (knot != storage->knots_allocated) {
        Knot *prev = knot->prev_allocated;
        Knot *next = knot->next_allocated;

        if (next) {
            next->prev_allocated = prev;
        }
        if (prev) {
            prev->next_allocated = next;
        }

    } else {
        /*printf("rare case\n");*/
        if (storage->knots_allocated->next_allocated) {
            storage->knots_allocated = storage->knots_allocated->next_allocated;
            storage->knots_allocated->prev_allocated = NULL;
        } else {
            storage->knots_allocated = NULL;
        }
    }

    knot->next_allocated = NULL;
    knot->prev_allocated = NULL;
    knot->is_free = true;
    knot->is_allocated = false;

    Knot *new = knot;
    if (!storage->knots_free) {
        storage->knots_free = new;
        new->next_free = NULL;
        new->prev_free = NULL;
    } else {
        new->prev_free = NULL;
        storage->knots_free->prev_free = new;
        new->next_free = storage->knots_free;
        storage->knots_free = new;
    }

}

bool knot_foreach_allocated(
    KnotStorage *storage,
    KnotIterFunc func,
    void *data
) {
    assert(storage);
    assert(func);

    Knot *cur = storage->knots_allocated;
    while (cur) {
        if (func(cur, data)) {
            return true;
        }
        cur = cur->next_allocated;
    }

    return false;
}

bool knot_foreach_free(
    KnotStorage *storage,
    KnotIterFunc func,
    void *data
) {
    assert(storage);
    assert(func);

    Knot *cur = storage->knots_free;
    while (cur) {
        if (func(cur, data)) {
            return true;
        }
        cur = cur->next_free;
    }

    return false;
}

