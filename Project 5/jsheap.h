#ifndef _JSHEAP_H_
#define _JSHEAP_H_
#include <stdlib.h>

void *jsMalloc(size_t nBytes);
void jsFree(void *heapChunk);

#endif /* _JSHEAP_H_ */
