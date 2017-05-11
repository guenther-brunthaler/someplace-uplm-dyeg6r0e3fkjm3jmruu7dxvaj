/*
 * Copyright (c) 2017 Guenther Brunthaler. All rights reserved.
 *
 * This source file is free software.
 * Distribution is permitted under the terms of the GPLv3.
 */

#include "endian_27aq18pth4y0m1zzesylkwjk5.h"
#include "getopt_nh7lll77vb62ycgwzwf30zlln.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <assert.h>


int main(int argc, char **argv) {
   int optind;
   {
      int optpos, opt;
      optind= optpos= 0;
      switch (
         opt= getopt_simplest(
            &optind, &optpos, argc, (char const *const *)argv
         )
      ) {
         case 0: break;
         default: getopt_simplest_perror(opt); return EXIT_FAILURE;
      }
   }
   return EXIT_SUCCESS;
}
