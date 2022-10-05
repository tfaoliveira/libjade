#ifndef JADE_KEM_KYBER_KYBER512_AMD64_REF_API_H
#define JADE_KEM_KYBER_KYBER512_AMD64_REF_API_H

#include <stdint.h>

#define JADE_KEM_KYBER_KYBER512_AMD64_REF_SECRETKEYBYTES  1632
#define JADE_KEM_KYBER_KYBER512_AMD64_REF_PUBLICKEYBYTES  800
#define JADE_KEM_KYBER_KYBER512_AMD64_REF_CIPHERTEXTBYTES 768
#define JADE_KEM_KYBER_KYBER512_AMD64_REF_BYTES           32
#define JADE_KEM_KYBER_KYBER512_AMD64_REF_ALGNAME         "Kyber512"


int jade_kem_kyber_kyber512_amd64_ref_keypair(uint8_t *pk, uint8_t *sk);

int jade_kem_kyber_kyber512_amd64_ref_enc(uint8_t *ct, uint8_t *ss, const uint8_t *pk);

int jade_kem_kyber_kyber512_amd64_ref_dec(uint8_t *ss, const uint8_t *ct, const uint8_t *sk);

#endif
