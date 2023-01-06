#include <stdio.h>
#include "mem.h"
#include "util.h"

int main(void)
{
   void *p1, *p2, *p3, *p4, *p5, *p6, *p7;

   p1 = checked_malloc(40 * sizeof(int));
   p2 = checked_malloc(40 * sizeof(int));
   p3 = checked_malloc(40 * sizeof(int));
   p4 = checked_malloc(40 * sizeof(int));
   p5 = checked_malloc(40 * sizeof(int));

   printf("1. %p -- %ld (%ld bytes)\n", p1, (long) p1, 40 * sizeof(int));
   printf("2. %p -- %ld (%ld bytes)\n", p2, (long) p2, 40 * sizeof(int));
   printf("3. %p -- %ld (%ld bytes)\n", p3, (long) p3, 40 * sizeof(int));
   printf("4. %p -- %ld (%ld bytes)\n", p4, (long) p4, 40 * sizeof(int));
   printf("5. %p -- %ld (%ld bytes)\n", p5, (long) p5, 40 * sizeof(int));

   printf("Freeing 4th -- %p\n", p4);
   lab_free(p4);

   p6 = checked_malloc(10 * sizeof(int));
   printf("Allocated -- %p -- %ld (%ld bytes)\n", p6, (long) p6,
      10 * sizeof(int));
   printf("Freeing 2nd -- %p\n", p2);
   lab_free(p2);
   p7 = checked_malloc(7 * sizeof(int));
   printf("Allocated -- %p -- %ld (%ld bytes)\n", p7, (long) p7,
      7 * sizeof(int));

   lab_free(p1);
   lab_free(p3);
   lab_free(p5);
   lab_free(p6);
   lab_free(p7);
   return 0;
}
