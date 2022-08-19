#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct Knot {
    struct Knot *next_allocated, *prev_allocated;
    struct Knot *next_free, *prev_free;

    int id;
} Knot;

typedef void(*KnotIterFunc)(Knot *knot);

typedef struct KnotStorage {
    Knot *knots;
    Knot *knots_free, *knots_allocated;
    int knotsnum, knotsnum_max;
} KnotStorage;

void knot_storage_init(KnotStorage *storage, int maxnum);
void knot_storage_free(KnotStorage *storage);

Knot *knot_alloc(KnotStorage *storage);
void knot_free(KnotStorage *storage, Knot *knot);

void knot_foreach(KnotStorage *storage, KnotIterFunc func);
