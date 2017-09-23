#ifndef SDES_H
#define SDES_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void main(int argc,char **argv);
uint8_t SDES_Decrypt(uint8_t *byte);
uint8_t SDES_Encrypt(uint8_t *byte);
uint8_t SDES_Crack(uint8_t *byte);
uint8_t TripleSDES_Decrypt(uint8_t *byte);
uint8_t TripleSDES_Encrypt(uint8_t *byte);
uint8_t TripleSDES_Crack(uint8_t *byte);
#endif
