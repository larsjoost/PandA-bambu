/**
 * Porting of the libm library to the PandA framework
 * starting from the original FDLIBM 5.3 (Freely Distributable LIBM) developed by SUN
 * plus the newlib version 1.19 from RedHat and plus uClibc version 0.9.32.1 developed by Erik Andersen.
 * The author of this port is Fabrizio Ferrandi from Politecnico di Milano.
 * The porting fall under the LGPL v2.1, see the files COPYING.LIB and COPYING.LIBM_PANDA in this directory.
 * Date: September, 11 2013.
 */
/*
 * infinityf () returns the representation of infinity.
 * Added by Cygnus Support.
 */

#include "math_privatef.h"

float infinityf()
{
   float x;

   SET_FLOAT_WORD(x, 0x7f800000);
   return x;
}

#ifdef _DOUBLE_IS_32BITS

double infinity()
{
   return (double)infinityf();
}

#endif /* defined(_DOUBLE_IS_32BITS) */
