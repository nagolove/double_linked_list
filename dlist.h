#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Knot {
    struct Knot *next_allocated, *prev_allocated;
    struct Knot *next_free, *prev_free;

    int id;
    bool is_allocated, is_free;
} Knot;

typedef bool(*KnotIterFunc)(Knot *knot, void *data);

typedef struct KnotStorage {
    Knot *knots;
    Knot *knots_free, *knots_allocated;
    int knotsnum, knotsnum_max;
    int last_id;
    int allocated_num, free_num;
} KnotStorage;

void knot_storage_init(KnotStorage *storage, int maxnum);
void knot_storage_free(KnotStorage *storage);

Knot *knot_alloc(KnotStorage *storage);
void knot_free(KnotStorage *storage, Knot *knot);

bool knot_foreach_allocated(KnotStorage *storage, KnotIterFunc func, void *data);
bool knot_foreach_free(KnotStorage *storage, KnotIterFunc func, void *data);
