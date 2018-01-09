#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void* mymalloc(uint64_t i);
uint64_t mymemsize(void* t);
uint64_t mytabsize(void *p, uint64_t sizeof_element);
void myfree(void *p);
void affichage(uint32_t *p);


int main(int argc, char const *argv[]) {

  uint64_t i = 0;
  uint32_t *tab = mymalloc(100*sizeof(uint32_t));
  for (i=0; i<100; i++)
  {
    tab[i]=2*i;
  }
  affichage(tab);
  printf("%lu\n",mytabsize(tab,sizeof(float)));
  myfree(tab);
  return 0;
}

void* mymalloc(uint64_t i)
{
  uint64_t *p = malloc(i+8);
  if(p == NULL)
  {
    printf("malloc() error in %s %s:%d",__FILE__,__func__,__LINE__);
    exit(0);
  }
  p[0]=i;
  return (void*)(p+1);
}

uint64_t mymemsize(void* t)
{
  return *(((uint64_t*)t)-1);
}

uint64_t mytabsize(void *p, uint64_t sizeof_element)
{
  return mymemsize(p)/sizeof_element;
}

void myfree(void *p)
{
  free(((uint64_t*)p)-1);
}

void affichage(uint32_t *p)
{
  uint64_t i;
  for (i=0; i<mytabsize(p,sizeof(uint32_t)); i++)
  {
    printf("%d\n",p[i]);
  }
}
