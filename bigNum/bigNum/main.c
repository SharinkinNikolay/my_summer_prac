#include "bigNum.h"

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("Error: insufficient number of arguments\n");
		return -1;
	}
	BigNum bignum1;
	BigNum bignum2;
	BigNum bignum3;
	BigNum bignum4;

	str_to_bignum(argv[1], &bignum1);
	str_to_bignum(argv[2], &bignum2);

	if (bignum1.sign == 0 || bignum2.sign == 0)
	{
		return -1;
	}

	printf("Big number 1: ");
	print_bignum(&bignum1);
	printf("Big number 2: ");
	print_bignum(&bignum2);

	add_bignums(&bignum1, &bignum2, &bignum3);
	sub_bignums(&bignum1, &bignum2, &bignum4);

	printf("Add 1 and 2 big numbers: ");
	print_bignum(&bignum3);

	printf("Sub 1 and 2 big numbers: ");
	print_bignum(&bignum4);

	return 0;
}

