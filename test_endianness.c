/* Copyright (c) 2017 Guenther Brunthaler. All rights reserved.
 *
 * This source file is free software.
 * Distribution is permitted under the terms of the GPLv3. */
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
   unsigned bits, lpos= UINT_MAX;
   biggest_uint volatile var;
   unsigned char volatile const *p= (void volatile const *)&var;
   var= 1;
   for (bits= CHAR_BIT * sizeof var; bits--; ) {
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
      if (found == UINT_MAX) abort();
      var+= var;
      if (found == lpos) continue;
      if (printf("%s%u", lpos == UINT_MAX ? "" : "-", found) <= 0) abort();
      lpos= found;
   }
   if (puts("") < 0 || fflush(0)) abort();
   return EXIT_SUCCESS;
}
