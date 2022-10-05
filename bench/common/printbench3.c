#ifndef PRINTBENCH3_C
#define PRINTBENCH3_C

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

static void pb_alloc_3(uint64_t** results[OP][LOOPS], size_t _x, size_t _y)
{
  size_t o, l, x;
  for (o=0; o<OP; o++)
  { for (l=0; l<LOOPS; l++)
    { results[o][l] = (uint64_t**) malloc(sizeof(uint64_t*) * _x);
      for (x=0; x<_x; x++)
      { results[o][l][x] = (uint64_t*) malloc(sizeof(uint64_t) * _y); }
    }
  }
}

static void pb_free_3(uint64_t** results[OP][LOOPS], size_t _x)
{
  size_t o, l, x;
  for (o=0; o<OP; o++)
  { for (l=0; l<LOOPS; l++)
    { for (x=0; x<_x; x++)
      { free(results[o][l][x]); }
      free(results[o][l]);
    }
  }
}

static void pb_print_3(int argc, uint64_t** results[OP][LOOPS], char *op_str[])
{
  int op, loop, r0, r1;
  uint64_t outlen, inlen, min;
  double cpb;
  FILE *f;

  // get min median of LOOP runs
  for (outlen = MINOUTBYTES, r0 = 0; outlen <= MAXOUTBYTES; outlen = inc_out(outlen), r0 += 1)
  { for (inlen = MININBYTES, r1 = 0; inlen <= MAXINBYTES; inlen = inc_in(inlen), r1 += 1)
    { for (op = 0; op < OP; op++)
      { min = results[op][0][r0][r1];
        for (loop = 1; loop < LOOPS; loop++)
        { if (min > results[op][loop][r0][r1])
          { min = results[op][loop][r0][r1]; } }
        results[op][0][r0][r1] = min;
      }
    }
  }

  // print to file
  f = stdout;
  for (op = 0; op < OP; op++)
  { if(argc == 1) { f = fopen(op_str[op], "w"); }
    loop = 0;
    for (outlen = MINOUTBYTES, r0 = 0; outlen <= MAXOUTBYTES; outlen = inc_out(outlen), r0 += 1)
    { for (inlen = MININBYTES, r1 = 0; inlen <= MAXINBYTES; inlen = inc_in(inlen), r1 += 1)
      { if(inlen == 0)
        { fprintf(f, "%" PRIu64 ", %" PRIu64 ", %" PRIu64 ", undef\n", outlen, inlen, results[op][loop][r0][r1]); }
        else
        { cpb = ((double)results[op][loop][r0][r1]) / ((double)inlen); // cycles per input byte
          fprintf(f, "%" PRIu64 ", %" PRIu64 ", %" PRIu64 ", %.2f\n", outlen, inlen, results[op][loop][r0][r1], cpb );
        }
      }
    }
    if(argc == 1) { fclose(f); }
  }
}

#endif
