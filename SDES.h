#ifndef SDES_H
#define SDES_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

int main(int argc, char *argv[]);
uint8_t SDES_Encrypt(uint8_t *byte, uint16_t key);
uint8_t SDES_Decrypt(uint8_t *byte, uint16_t key);
uint8_t SDES_Crack(uint8_t *byte);
uint8_t TripleSDES_Encrypt(uint8_t *byte, uint16_t key1, uint16_t key2);
uint8_t TripleSDES_Decrypt(uint8_t *byte, uint16_t key1, uint16_t key2);
uint8_t TripleSDES_Crack(uint8_t *byte);

uint8_t LS_1(uint8_t key);
uint8_t LS_2(uint8_t key);
uint8_t P4(uint8_t S);
uint8_t P8(uint8_t key);
uint16_t P10(uint16_t key);
uint8_t IP(uint8_t right);
uint8_t IP_1(uint8_t right);
uint8_t f(uint8_t right, uint8_t key);
uint8_t f_k(uint8_t byte, uint8_t key);
uint8_t SW(uint8_t right);
uint8_t EP(uint8_t right);
uint8_t S1(uint8_t msb);
uint8_t S2(uint8_t lsb);
uint8_t bit(uint16_t byte, uint8_t n);
uint16_t permutate(uint16_t byte, uint8_t length, uint8_t indexLength, uint8_t *index);

void test(uint8_t byte, uint8_t key);

#endif //SDES_H
