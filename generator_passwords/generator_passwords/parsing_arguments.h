#pragma once

#include<string.h>
#include"check_arguments.h"
#include<malloc.h>

#define MAX_ALPHABET_LEN 92
#define DEFAULT_PASSWORD_LENGTH 8
#define DEFAULT_PASSWORD_COUNT 8

int get_password_length(char* argv[], int* min_password_length, int* max_password_length)
{
	int i = 1;
	int check = 0;

	while (argv[i] != NULL)
	{
		if (strcmp(argv[i], "-m1") == 0 && strcmp(argv[i - 1], "-a") != 0)
		{
			if (argv[i + 1] != NULL)
			{
				*min_password_length = atoi(argv[i + 1]);
				check++;
			}
		}
		if (strcmp(argv[i], "-m2") == 0 && strcmp(argv[i - 1], "-a") != 0)
		{
			if (argv[i + 1] != NULL)
			{
				*max_password_length = atoi(argv[i + 1]);
				check++;
			}
		}
		if (strcmp(argv[i], "-n") == 0 && strcmp(argv[i - 1], "-a") != 0)
		{
			if (argv[i + 1] == NULL)
			{
				printf("Inappropriate argument for -n, set default value of 8\n");
				*max_password_length = DEFAULT_PASSWORD_LENGTH;
				*min_password_length = DEFAULT_PASSWORD_LENGTH;
			}
			else
			{
				if (convert_to_int(argv[i + 1]) == 0)
				{
					*min_password_length = atoi(argv[i + 1]);
					*max_password_length = atoi(argv[i + 1]);
				}
				else
				{
					printf("Inappropriate argument for -n , set default value of 8\n");
					*max_password_length = DEFAULT_PASSWORD_LENGTH;
					*min_password_length = DEFAULT_PASSWORD_LENGTH;
				}
				check++;
			}
			i++;
		}
	}
	if (*max_password_length > RAND_MAX)
	{
		printf("Error: maximal length of a password shouldn`t exceed 32767\n");
		return -1;
	}
	if (*min_password_length > RAND_MAX)
	{
		printf("Error: minimal length of a password shouldn`t exceed 32767\n");
		return -1;
	}
	if (check == 0)
	{
		printf("No length parameters found: assuming the default value of 8\n");
		*max_password_length = DEFAULT_PASSWORD_LENGTH;
		*min_password_length = DEFAULT_PASSWORD_LENGTH;
	}
	return 0;
}

char* get_password_alphabet(const char* argv[])
{
	int i = 1;
	int argument_length;
	int check = 0;
	int result_alphabet_length = 1;

	char* result_alphabet;
	result_alphabet = (char*)malloc(MAX_ALPHABET_LEN * sizeof(char));
	if (!result_alphabet)
	{
		printf("Error: memory allocation failure\n");
		return;
	}
	for (int i = 0; i < MAX_ALPHABET_LEN; i++)
	{
		result_alphabet[i] = '\0';
	}
	const char default_alphabet[] = "HELLOWORLD";
	const char capital_alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const char lowercase_alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	const char digits_alphabet[] = "1234567890";
	const char special_alphabet[] = "!#$%&'()*+,-./:;<=>?@[]^_{|}~";

	while (argv[i] != NULL)
	{
		if (strcmp(argv[i], "-C") == 0 || strcmp(argv[i], "-a") == 0)
		{
			check++;
			i++;
		}
	}
	if (check == 0)
	{
		printf("Couldn't find a correct alphabet argument: assuming 'HELLOWORLD' as base alphabet\n");
		strcat_s(result_alphabet, strlen(default_alphabet) + 1, default_alphabet);
		return result_alphabet;
	}
	i = 1;

	while (argv[i] != NULL)
	{
		if (strcmp(argv[i], "-a") == 0)
		{
			if (argv[i + 1] == NULL)
			{
				strcat_s(result_alphabet, strlen(default_alphabet) + 1, default_alphabet);
				return result_alphabet;
			}
			strcat_s(result_alphabet, strlen(argv[i + 1]) + 1, argv[i + 1]);
			return result_alphabet;
		}


		if (strcmp(argv[i], "-C") == 0 && strcmp(argv[i - 1], "-a") != 0)
		{
			if (argv[i + 1] == NULL || strcmp(argv[i + 1], "-m1") == 0 || strcmp(argv[i + 1], "-m2") == 0 || strcmp(argv[i + 1], "-n") == 0 || strcmp(argv[i + 1], "-c") == 0);
			{
				strcat_s(result_alphabet, strlen(default_alphabet) + 1, default_alphabet);
				return result_alphabet;
			}
			argument_length = strlen(argv[i + 1]);
			for (int j = 0; j < argument_length; j++)
			{
				if (argv[i + 1][j] == 'a')
				{
					result_alphabet_length = result_alphabet_length + strlen(lowercase_alphabet);
					strcat_s(result_alphabet, result_alphabet_length, lowercase_alphabet);
				}
				if (argv[i + 1][j] == 'A')
				{
					result_alphabet_length += strlen(capital_alphabet);
					strcat_s(result_alphabet, result_alphabet_length, capital_alphabet);
				}
				if (argv[i + 1][j] == 'D')
				{
					result_alphabet_length += strlen(digits_alphabet);
					strcat_s(result_alphabet, result_alphabet_length, digits_alphabet);
				}
				if (argv[i + 1][j] == 'S')
				{
					result_alphabet_length += strlen(special_alphabet);
					strcat_s(result_alphabet, result_alphabet_length, special_alphabet);
				}
			}
		}
		i++;
	}
	return result_alphabet;
}

unsigned long get_password_count(const char* argv[])
{
	int i = 1;
	unsigned long count = 0;
	while (argv[i] != NULL)
	{
		if (strcmp(argv[i], "-c") == 0)
		{
			if (strcmp(argv[i + 1], "-a") == 0 || strcmp(argv[i + 1], "-m1") == 0 || strcmp(argv[i + 1], "-m2") == 0 || strcmp(argv[i + 1], "-C") == 0 || strcmp(argv[i + 1], "-n") == 0 || argv[i + 1] == NULL)
			{
				printf("Couldn't find the passwords number:assuming default value of 8\n");
				return DEFAULT_PASSWORD_COUNT;
			}
			count = str_to_ulong(argv[i + 1]);
			return count;
		}
		i++;
	}
	printf("Couldn't find the passwords number:assuming default value of 8\n");
	return DEFAULT_PASSWORD_COUNT;
}