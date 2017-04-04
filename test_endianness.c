#ifdef ASSUME_STDINT_H
   #include <stdint.h>
   typedef uintmax_t uint;
#else
   typedef unsigned long uint;
#endif
#include <limits.h>

int main(void) {
   unsigned bit, pupos, lpos;
   #ifdef ARM_ENABLE_BIGENDIAN
      __asm("SETEND BE");
   #endif
   pupos= lpos= UINT_MAX;
   for (bit= sizeof(uint) * CHAR_BIT; bit--; ) {
      uint const var= (uint)1 << bit;
      unsigned char const *p= (void const *)&var;
      unsigned found= UINT_MAX;
      {
         unsigned bytei, pos= sizeof var * CHAR_BIT;
         for (bytei= sizeof var; bytei--; ) {
            unsigned byte= p[bytei], bytebit;
            for (bytebit= 1u << CHAR_BIT - 1; bytebit; bytebit>>= 1) {
               if (byte & bytebit) {
                  if (found != UINT_MAX) goto unsupported;
                  found= pos;
               }
               --pos;
            }
         }
      }
      if (found == UINT_MAX) goto unsupported;
      if (pupos != UINT_MAX) {
         if (found - lpos != lpos - pupos) goto unsupported;
      }
      pupos= lpos;
      lpos= found;
   }
   {
      char rc; /* Will be unaffected by endianness. */
      if (lpos + 1 == pupos) rc= 1; /* Big endian. */
      else if (pupos + 1 == lpos) rc= 2; /* Little endian. */
      else {
         unsupported:
         rc= 0; /* Unsupported endianness. */
      }
      #ifdef ARM_ENABLE_BIGENDIAN
         __asm("SETEND LE");
      #endif
      return rc;
   }
}
