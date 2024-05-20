#pragma once
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct
{
	unsigned int* num;
	size_t size;
	int sign;
} BigNum;

void str_to_bignum(const char* string, BigNum* bignum);
void print_bignum(BigNum* bignum);
int compare_bignum(BigNum* bignum1, BigNum* bignum2);
void add_bignums(BigNum* bignum1, BigNum* bignum2, BigNum* res);
void sub_bignums(BigNum* bignum1, BigNum* bignum2, BigNum* res);