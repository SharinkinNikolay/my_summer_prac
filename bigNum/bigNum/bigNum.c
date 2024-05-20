#include "bigNum.h"

void str_to_bignum(const char* string, BigNum* bignum)
{
	char* dupstr = string;
	if (dupstr[0] == '-')
	{
		bignum->sign = -1;
		dupstr++;
	}
	else
	{
		bignum->sign = 1;
	}
	int length = strlen(dupstr);
	bignum->size = length / 8;
	if (length % 8 != 0)
	{
		bignum->size += 1;
	}
	bignum->num = (unsigned int*)malloc(sizeof(unsigned int) * bignum->size);
	for (int i = 0; i < bignum->size; i++)
	{
		bignum->num[i] = 0;
	}
	unsigned int power = 1;

	for (int i = length - 1; i >= 0; i--)
	{
		int tmp = 0;
		if (dupstr[i] >= 'A' && dupstr[i] <= 'F')
		{
			tmp = 10 + dupstr[i] - 'A';
		}
		else
		{
			if (dupstr[i] >= '0' && dupstr[i] <= '9')
			{
				tmp = dupstr[i] - '0';
			}
			else
			{
				printf("Error: incorrect symbol detected: %c\n", dupstr[i]);
				bignum->sign = 0;
				return;
			}
		}
		bignum->num[((length - i - 1) / 8)] += tmp * power;
		power *= 16;
		if ((length - i) % 8 == 0)
		{
			power = 1;
		}
	}
	return;
}

void print_bignum(BigNum* bignum)
{
	int hexLength = 8;
	char* hex = (char*)malloc(sizeof(char) * (hexLength + 1));
	if (bignum->sign == -1)
	{
		printf("-");
	}
	for (int i = bignum->size - 1; i >= 0; i--)
	{
		for (int j = 0; j < hexLength; j++)
		{
			hex[j] = '0';
		}
		hex[hexLength] = '\0';

		unsigned int tmp = bignum->num[i];
		int iterator = 0;
		if (tmp == 0 && bignum->size == 1)
		{
			printf("0");
		}
		else
		{
			while (tmp > 0)
			{
				int tmpDec = tmp % 16;
				tmp /= 16;
				if (tmpDec < 10)
				{
					hex[iterator] = '0' + tmpDec;
				}
				else 
				{
					hex[iterator] = 'A' + tmpDec - 10;
				}
				iterator++;
			}
			if (i == bignum->size - 1)
			{
				iterator = iterator - 1;
			}
			else
			{
				iterator = hexLength - 1;
			}
			for (; iterator >= 0; iterator--)
			{
				printf("%c", hex[iterator]);
			}
		}
	}
	printf("\n");
	return;
}

int compare_bignum(BigNum* bignum1, BigNum* bignum2)
{
	if(bignum1->size > bignum2->size)
		{
			return 1;
		}
	if (bignum2->size > bignum1->size)
	{
		return -1;
	}
	for (int i = bignum1->size - 1; i >= 0; i--)
	{
		if(bignum1->num[i] > bignum2->num[i])
		{
			return 1;
		}
		if (bignum2->num[i] > bignum1->num[i])
		{
			return -1;
		}
	}
	return 0;
}

void add_bignums(BigNum* bignum1, BigNum* bignum2, BigNum* res)
{
	int bignum1_sign_holder = bignum1->sign;
	int bignum2_sign_holder = bignum2->sign;
	unsigned int* resTmp;

	if (bignum1->sign != bignum2->sign)
	{
		switch (compare_bignum(bignum1, bignum2))
		{
		case 1: 
			bignum2->sign = bignum1->sign;
			res->sign = bignum1->sign;
			sub_bignums(bignum1, bignum2, res);
			bignum1->sign = bignum1_sign_holder;
			bignum2->sign = bignum2_sign_holder;
			return;

		case -1:
			bignum1->sign = bignum2->sign;
			res->sign = bignum2->sign;
			sub_bignums(bignum2, bignum1, res);
			bignum1->sign = bignum1_sign_holder;
			bignum2->sign = bignum2_sign_holder;
			return;
		default:
			res->size = 1;
			res->sign = 1;
			resTmp = (unsigned int*)malloc(sizeof(unsigned int));
			resTmp[0] = 0;
			res->num = resTmp;
			return;
		}
	}
	else
	{
		res->sign = bignum1->sign;
	}
	if (bignum1->size > bignum2->size)
	{
		res->size = bignum1->size + 1;
		resTmp = (unsigned int*)malloc(sizeof(unsigned int) * (res->size));
	}
	else
	{
		res->size = bignum2->size + 1;
		resTmp = (unsigned int*)malloc(sizeof(unsigned int) * (res->size));
	}
	for (int i = 0; i < res->size; i++)
	{
		resTmp[i] = 0;
	}
	int over = 0;
	for (int i = 0; i < res->size; i++)
	{
		unsigned int tmpDec1;
		unsigned int tmpDec2;

		if (i >= bignum1->size)
		{
			tmpDec1 = 0;
		}
		else
		{
			tmpDec1 = bignum1->num[i];
		}
		if (i >= bignum2->size)
		{
			tmpDec2 = 0;
		}
		else
		{
			tmpDec2 = bignum2->num[i];
		}
		unsigned int power = 1;

		for (int index = 7; index >= 0; index--)
		{
			int tmp1 = tmpDec1 % 16;
			int tmp2 = tmpDec2 % 16;
			tmpDec1 /= 16;
			tmpDec2 /= 16;
			int sum = tmp1 + tmp2 + over;
			if (sum >= 16)
			{
				sum -= 16;
				over = 1;
			}
			else
			{
				over = 0;
			}
			resTmp[i] += power * sum;
			power *= 16;
		}
	}
	if (resTmp[res->size - 1] == 0)
	{
		res->size -= 1;
	}
	res->num = resTmp;
	return;
}

void sub_bignums(BigNum* bignum1, BigNum* bignum2, BigNum* res)
{
	int bignum1_sign_holder = bignum1->sign;
	int bignum2_sign_holder = bignum2->sign;
	unsigned int* resTmp;
	unsigned int* tmpNum;
	size_t tmpSize;

	if (bignum1->sign != bignum2->sign)
	{
		switch (compare_bignum(bignum1, bignum2))
		{
		case 1: 
			bignum2->sign = bignum1->sign;
			res->sign = bignum1->sign;
			add_bignums(bignum1, bignum2, res);
			bignum1->sign = bignum1_sign_holder;
			bignum2->sign = bignum2_sign_holder;
			return;

		case -1: 
			bignum2->sign = bignum1->sign;
			res->sign = bignum1->sign;
			add_bignums(bignum2, bignum1, res);
			bignum1->sign = bignum1_sign_holder;
			bignum2->sign = bignum2_sign_holder;
			return;

		case 0: 
			bignum2->sign = bignum1->sign;
			res->sign = bignum1->sign;
			add_bignums(bignum1, bignum2, res);
			bignum1->sign = bignum1_sign_holder;
			bignum2->sign = bignum2_sign_holder;
			return;
		}
	}
	switch (compare_bignum(bignum1, bignum2))
	{
	case 1: 
		res->sign = bignum1->sign;
		res->size = bignum1->size;
		break;
	case -1: 
		res->sign = bignum2->sign * (-1);
		res->size = bignum2->size;

		tmpNum = bignum1->num;
		bignum1->num = bignum2->num;
		bignum2->num = tmpNum;

		tmpSize = bignum1->size;
		bignum1->size = bignum2->size;
		bignum2->size = tmpSize;
		break;
	case 0: 
		res->sign = 1;
		res->size = 1;
		resTmp = (unsigned int*)malloc(sizeof(unsigned int) * (res->size));
		resTmp[0] = 0;
		res->num = resTmp;
		return;
	}
	int borrow = 0;
	resTmp = (unsigned int*)malloc(sizeof(unsigned int) * (res->size));

	for (int i = 0; i < res->size; i++)
	{
		resTmp[i] = 0;
	}
	for (int i = 0; i < res->size; i++)
	{
		unsigned int tmpDec1;
		unsigned int tmpDec2;

		if (i >= bignum1->size)
		{
			tmpDec1 = 0;
		}
		else
		{
			tmpDec1 = bignum1->num[i];
		}
		if (i >= bignum2->size)
		{
			tmpDec2 = 0;
		}
		else
		{
			tmpDec2 = bignum2->num[i];
		}
		unsigned int power = 1;

		for (int iterator = 7; iterator >= 0; iterator--)
		{
			int tmp1 = tmpDec1 % 16;
			int tmp2 = tmpDec2 % 16;
			tmpDec1 /= 16;
			tmpDec2 /= 16;
			int sub = tmp1 - tmp2 - borrow;
			if (sub < 0)
			{
				borrow = 1;
				sub += 16;
			}
			else
			{
				borrow = 0;
			}
			resTmp[i] += power * sub;
			power *= 16;
		}
	}
	int realLength = res->size - 1;
	while (realLength > 0 && resTmp[realLength] == 0)
	{
		realLength--;
		res->size--;
	}
	res->num = resTmp;
	return;
}