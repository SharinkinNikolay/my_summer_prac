#pragma once

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int convert_to_int(const char* str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] < 47) || (str[i] > 58))
		{
			return 1;
		}
		i++;
	}
	return 0;
}

unsigned long str_to_ulong(const char* str)
{
	unsigned long res = strtoul(str, NULL, 0);
	return res;
}

int check_length_options(const char* argv[]) //проверка сосуществования -m1 -m2 и n
{
	int counter = 0;
	int i = 1;
	int j = 1;
	while (argv[i] != NULL)
	{
		if (strcmp(argv[i], "-m1") == 0 && strcmp(argv[i - 1], "-a") != 0)
		{
			counter++;
		}
		i++;
		if (counter > 1) //Если на этом шаге больше 2, значит m1 повторился
		{
			printf("Error: argument -m1 shouldn`t repeat\n");
			return -1;
		}
	}
	i = 1;
	while (argv[i] != NULL)
	{
		if (strcmp(argv[i], "-m2") == 0 && strcmp(argv[i - 1], "a") != 0)
		{
			counter++;
		}
		i++;
		if (counter > 2)
			//На этом шаге count=1 либо 0(либо уже произошел выход из функции),
			//поэтому он должен получиться либо 2,либо 0, иначе аргументы повторяются
		{
			printf("Error: aegument -m2 shoudn`t repeat\n");
			return -1;
		}
	}
	i = 1;
	while (argv[i] != NULL)
	{
		if ((strcmp(argv[i], "-n") == 0) && (counter > 0) && strcmp(argv[i - 1], "-a") != 0)
		{
			printf("Error: arguments -n and -m are incompatible\n");
			return -1;
		}
		i++;
	}
	if (counter == 1)
	{
		printf("Error: one of the -m arguments is missing\n");
		return -1;
	}
	return 0;
}

int check_alphabet_options(const char* argv[]) //проверка на повторы и  сосуществование -С и -а
{
	int i = 1;
	int check = 0;

	while (argv[i] != NULL)
	{
		if (strcmp(argv[i], "-a") == 0 && strcmp(argv[i - 1], "-a") != 0)
		{
			check++;
		}
		if (strcmp(argv[i], "-C") == 0 && strcmp(argv[i - 1], "-a") != 0)
		{
			check++;
		}
		i++;
	}
	if (check > 1)
	{
		printf("Error: two or more incompatible -a and -C arguments found\n");
		return -1;
	}
	i = 1;
	return 0;
}

int check_other_options(const char* argv[]) // проверка на повторы - n и - с
{
	int i = 1;
	int check = 0;
	while (argv[i] != NULL)
	{
		if (strcmp(argv[i], "-n") == 0 && strcmp(argv[i - 1], "-a") != 0)
		{
			check++;
		}
		if (check > 1)
		{
			printf("Error: argument -n shouldn`t repeat\n");
			return -1;
		}
		i++;
	}
	i = 1;
	check = 0;
	while (argv[i] != NULL)
	{
		if (strcmp(argv[i], "-c") == 0 && strcmp(argv[i - 1], "-a") != 0)
		{
			check++;
		}
		if (check > 1)
		{
			printf("Error: argument -c shouldn`t repeat\n");
			return -1;
		}
		i++;
	}
	return 0;
}

int check_arguments_are_numbers(const char* argv[]) // -m1 - m2 должны иметь аргументы в виде строк из цифр
{
	int i = 1;

	while (argv[i] != NULL)
	{
		if ((strcmp(argv[i], "-m1") == 0 && strcmp(argv[i], "-m2") == 0))
		{
			if (argv[i + 1] == NULL && strcmp(argv[i - 1], "-a") != 0)
			{
				printf("Error: one of the parameters' arguments cannot be converted to an unsigned number, or the argument for one of the -m1/-m2 commands was not present\n ");
				return -1;
			}
			if (strcmp(argv[i - 1], "-a") == 0)
			{
				i++;
				continue;
			}
			if (convert_to_int(argv[i + 1]) != 0)
			{
				printf("Error: -c argument cannot be converted to unsigned int");
				return -1;
			}
		}
		i++;
	}
	return 0;
}

int check_alphabet(const char* argv[]) // проверка аргументов -С [aADS]
{
	int a = 0;
	int A = 0;
	int D = 0;
	int S = 0;
	int arguments_end = 1;
	int arguments_length = 0;
	int i = 0;
	while (argv[i] != NULL)
	{
		if (strcmp(argv[i], "-C") == 0)
		{
			if (strcmp(argv[i - 1], "-a") == 0)
			{
				return 0;
			}
			if (argv[i + 1] == NULL || strcmp(argv[i + 1], "-n") == 0 || strcmp(argv[i + 1], "-m1") == 0 || strcmp(argv[i + 1], "-m2") == 0 || strcmp(argv[i + 1], "-c") == 0)
			{
				return 0;
			}
			while (argv[i + 1][arguments_length] != '\0')
			{
				arguments_length++;
			}
			if (arguments_length < 5) // "aADS" - не больше 4 символов
			{
				for (int j = 0; j < arguments_length; j++)
				{
					if (argv[i + 1][j] != 'a' && argv[i + 1][j] != 'A' && argv[i + 1][j] != 'D' && argv[i + 1][j] != 'S')
					{
						printf("Error: incorrect input of -C arguments(wrong arguments)\n");
						return -1;
					}
					switch (argv[i + 1][j])
					{
					case 'a':
						a++;
						break;
					case 'A':
						A++;
						break;
					case 'D':
						D++;
						break;
					case 'S':
						S++;
						break;
					}
					if (a > 1 || A > 1 || D > 1 || S > 1)
					{
						printf("Error: several identical arguments for -C were given\n");
						return -1;
					}
				}
			}
			else
			{
				printf("Error: incorrect input of -C arguments(more than 4 arguments were given)\n");
				return -1;
			}
		}
		i++;
	}
	return 0;
}

int check_min_max(const char* argv[])
{
	int i = 0;
	int m1 = 0;
	int m2 = 0;

	while (argv[i + 1] != NULL)
	{
		if (strcmp(argv[i], "-m1") == 0)
		{
			m1 = atoi(argv[i + 1]);
		}
		if (strcmp(argv[i], "-m2") == 0)
		{
			m2 = atoi(argv[i + 1]);
		}
		i++;
	}
	if (m1 > m2)
	{
		printf("Error: argument -m1 cannot be bigger than -m2 argument\n");
		return -1;
	}
	if (m1 > RAND_MAX || m2 > RAND_MAX)
	{
		printf("Error: -m1/-m2 arguments cannot exceed 32767\n");
		return -1;
	}
	return 0;
}