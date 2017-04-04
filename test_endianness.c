#if ASSUME_STDINT_H
   #include <stdint.h>
   typedef uintmax_t uint;
#else
   typedef unsigned long uint;
#endif
#include <limits.h>

int main(void) {
   unsigned bit, pupos, lpos;
   #if ARM_ENABLE_BIGENDIAN
      __asm("SETEND BE");
   #endif
   pupos= lpos= UINT_MAX;
   for (bit= sizeof(uint) * CHAR_BIT; bit--; ) {
      uint const var= (uint)1 << bit;
      unsigned char const *p= (void const *)&var;
      unsigned found= UINT_MAX;
      {
         unsigned bytei;
         for (bytei= sizeof var; bytei--; ) {
            unsigned byte= p[bytei], bytebit;
            for (bytebit= 1u << CHAR_BIT - 1; bytebit; bytebit>>= 1) {
               if (byte & bytebit) {
                  if (found != UINT_MAX) goto unsupported;
                  found= bytei;
               }
            }
         }
      }
      if (found == UINT_MAX) goto unsupported;
      if (found == lpos) continue;
      if (pupos != UINT_MAX) {
         if (lpos - found != pupos - lpos) goto unsupported;
      }
      pupos= lpos;
      lpos= found;
   }
   {
      char rc; /* Will be unaffected by endianness. */
      /* <lpos> is offset of least significant byte. */
      if (lpos == 0 && pupos == 1) {
         rc= 2; /* Little endian. */
      } else if (lpos == pupos + 1 && lpos + 1 == sizeof(uint)) {
         rc= 1; /* Big endian. */
      } else {
         unsupported:
         rc= 0; /* Unsupported endianness. */
      }
      #if ARM_ENABLE_BIGENDIAN
         __asm("SETEND LE");
      #endif
      return rc;
   }
}
