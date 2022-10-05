#include "api.h"
#include "namespace.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
#define CRYPTO_BYTES           NAMESPACE(BYTES)
#define CRYPTO_SCALARBYTES     NAMESPACE(SCALARBYTES)
#define CRYPTO_ALGNAME         NAMESPACE(ALGNAME)

#define crypto_scalarmult      JADE_NAMESPACE_LC
#define crypto_scalarmult_base NAMESPACE_LC(base)

#define OP 2

//

#include "config.h"
#include "cpucycles.c"
#include "increment.c"
#include "printbench.c"
#include "alignedcalloc.c"
#include "benchrandombytes.c"

//

int main(int argc, char**argv)
{
  int loop, i;
  uint64_t cycles[TIMINGS];
  uint64_t results[OP][LOOPS];
  char *op_str[] = {xstr(crypto_scalarmult_base,.csv),
                    xstr(crypto_scalarmult,.csv)};

  uint8_t *_m, *m; // CRYPTO_SCALARBYTES
  uint8_t *_n, *n; // CRYPTO_SCALARBYTES
  uint8_t *_p, *p; // CRYPTO_BYTES
  uint8_t *_q, *q; // CRYPTO_BYTES

  m = alignedcalloc(&_m, CRYPTO_SCALARBYTES);
  n = alignedcalloc(&_n, CRYPTO_SCALARBYTES);
  p = alignedcalloc(&_p, CRYPTO_BYTES);
  q = alignedcalloc(&_q, CRYPTO_BYTES);

  for(loop = 0; loop < LOOPS; loop++)
  {
    benchrandombytes(m, CRYPTO_SCALARBYTES);
    benchrandombytes(n, CRYPTO_SCALARBYTES);

    // scalarmult_base
    for (i = 0; i < TIMINGS; i++)
    { cycles[i] = cpucycles();
      crypto_scalarmult_base(p,m); }
    results[1][loop] = cpucycles_median(cycles, TIMINGS);

    // scalarmult
    for (i = 0; i < TIMINGS; i++)
    { cycles[i] = cpucycles();
      crypto_scalarmult(q,n,p); }
    results[0][loop] = cpucycles_median(cycles, TIMINGS);

  }

  pb_print_1(argc, results, op_str);

  free(_m);
  free(_n);
  free(_p);
  free(_q);

  return 0;
}

