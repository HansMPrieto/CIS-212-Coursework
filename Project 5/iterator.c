#include "iterator.h"
#include <stdlib.h>
#include "jsheap.h"

typedef struct it_data {
    long next;
    long size;
    void **elements;
} ItData;

static int it_hasNext(const Iterator *it) {
    ItData *itd = (ItData *)(it->self);

    return (itd->next < itd->size) ? 1 : 0;
}

static int it_next(const Iterator *it, void **element) {
    ItData *itd = (ItData *)(it->self);
    int status = 0;

    if (itd->next < itd->size) {
        *element = itd->elements[itd->next++];
        status = 1;
    }
    return status;
}

static void it_destroy(const Iterator *it) {
    ItData *itd = (ItData *)(it->self);

    jsFree(itd->elements);
    jsFree(itd);
    jsFree((void *)it);
}

static Iterator template = {NULL, it_hasNext, it_next, it_destroy};

const Iterator *Iterator_create(long size, void **elements) {
    Iterator *it = (Iterator *)jsMalloc(sizeof(Iterator));

    if (it != NULL) {
        ItData *itd = (ItData *)jsMalloc(sizeof(ItData));

        if (itd != NULL) {
            itd->next = 0L;
            itd->size = size;
            itd->elements = elements;
            *it = template;
            it->self = itd;
        } else {
            jsFree(it);
            it = NULL;
        }
    }
    return it;
}
