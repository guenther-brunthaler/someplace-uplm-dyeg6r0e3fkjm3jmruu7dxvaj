#if __STDC_VERSION__ >= 199901L
   #include <stdint.h>
   typedef uintmax_t biggest_uint;
#else
   typedef unsigned long biggest_uint;
#endif
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
   unsigned bit, lpos= UINT_MAX;
   biggest_uint volatile var;
   unsigned char volatile const *p= (void volatile const *)&var;
   #if ARM_ENFORCE_BIGENDIAN
      asm("setend be");
   #endif
   var= (biggest_uint)1;
   #if ARM_ENFORCE_BIGENDIAN
      asm("setend le");
   #endif
   for (bit= sizeof(biggest_uint) * CHAR_BIT; bit--; ) {
      unsigned bytei, found= UINT_MAX;
      for (bytei= sizeof var; bytei--; ) {
         unsigned byte= p[bytei], bytebit;
         for (bytebit= 1u << CHAR_BIT - 1; bytebit; bytebit>>= 1) {
            if (byte & bytebit) {
               if (found != UINT_MAX) abort();
               found= bytei;
            }
         }
      }
      #if ARM_ENFORCE_BIGENDIAN
         asm("setend be");
      #endif
      var+= var;
      #if ARM_ENFORCE_BIGENDIAN
         asm("setend le");
      #endif
      if (found == UINT_MAX) abort();
      if (found == lpos) continue;
      if (printf("%s%u", lpos == UINT_MAX ? "" : "-", found) <= 0) abort();
      lpos= found;
   }
   if (puts("") < 0 || fflush(0)) abort();
   return EXIT_SUCCESS;
}
