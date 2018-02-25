#ifndef TERMINAL_h
#define TERMINAL_h

#include "datatypes.h"

/*$PAGE*/
/*
*********************************************************************************************************
*                                       FUNCTION PROTOTYPES
*********************************************************************************************************
*/
uint8_t operation(uint8_t *in) reentrant;

uint8_t check_hex(uint8_t *in) reentrant;

void get_hex(uint8_t* out,uint8_t* in) reentrant;

uint8_t str_comp(uint8_t* str1,uint8_t* str2, uint8_t nbytes) reentrant;

char* bin_to_string(const unsigned char input[], int nbytes);

#endif

