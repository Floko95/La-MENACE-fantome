#ifndef MYT_H
#define MYT_H

void* mymalloc(uint64_t i);
uint64_t mymemsize(void* t);
uint64_t mytabsize(void *p, uint64_t sizeof_element);
void myfree(void *p);
void affichage(uint32_t *p);

#endif
