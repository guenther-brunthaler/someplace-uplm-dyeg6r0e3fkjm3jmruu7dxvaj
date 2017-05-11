UNIX-principle long-math
========================
    
The uplm package provides simple utilities for doing
arbitrary-precision unsigned integer arithmetic for cryptographic
purposes, such as "manually" performing Diffie-Hellman key
exchanges rather than using specialized tools like OpenSSL.

They are intended to follow the UNIX-principle of being small and
simple and act primarily as a filter, i. e. they read something
from the standard input stream and write something else to
standard output stream.

Multiple utilities can be combined using pipes or temporary files
to accomplish more complex tasks than any individual utility can
achieve on its own.

The utilities are also intended to be portable, i. e. they do not
depend on more than a C89 (or better) compliant C compiler and
the standard C library.


Crytographic security
---------------------

All utilities assume that they process highly confidential key
material, which dictates the actual numbers being processed will
never be provided as command line arguments, but will always be
read from a file, pipe or file descriptor (such as /dev/fd/*)
instead.

To avoid side-channel attacks which measure the processing time
or power consumption of some calculations, the implementation
avoids short-circuit evaluations or data-dependent branches
whereever possible. The run-time of the utilities should
therefore be dominated only by the magnitude of the numeric
operands, but not on their particular bit patterns.

The utilities do not try to mlock() their data while processing
or "burn" variables after use, because such functionality is not
provided by the C standard and the reliability of such features
is debatable even if it is available, such as in POSIX.

Therefore, make sure that your confidental data is read either
from encrypted storage or from volatile storage such as from a
RAM disk.

Make also sure that either no swapping is enabled, or that your
swap space is encrypted as well. Because otherwise the memory
image of the running process could be swapped out to disk
unprotected, where it could be found by an attacker later.

Of course, all this only matters if you are actually using uplm
for processing confidential data. You do not need to consider
such issues at all if you use uplm just for doing long math.
