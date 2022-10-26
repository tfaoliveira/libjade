#ifndef JADE_SCALARMULT_CURVE25519_AMD64_MULXRA_API_H
#define JADE_SCALARMULT_CURVE25519_AMD64_MULXRA_API_H

#define JADE_SCALARMULT_CURVE25519_AMD64_MULXRA_BYTES 32
#define JADE_SCALARMULT_CURVE25519_AMD64_MULXRA_SCALARBYTES 32
#define JADE_SCALARMULT_CURVE25519_AMD64_MULXRA_ALGNAME "Curve25519"

#include <stdint.h>

int jade_scalarmult_curve25519_amd64_mulxra(
 uint8_t *r,
 uint8_t *k,
 uint8_t *u
);

int jade_scalarmult_curve25519_amd64_mulxra_base(
 uint8_t *r,
 uint8_t *k
);

// TODO : to be replaced for opt. Jasmin implementation
int jade_scalarmult_curve25519_amd64_mulxra_base(
 uint8_t *r,
 uint8_t *k
)
{
  uint8_t basepoint[32] = {9};
  int res = jade_scalarmult_curve25519_amd64_mulxra(r,k,basepoint);
  return res;
}

#endif
