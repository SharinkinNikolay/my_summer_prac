#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int generate_passwords(int* min_length, int* max_length, unsigned long count, char* alphabet)
{
	srand(time(NULL));

	char* password = (char*)malloc((*max_length + 1) * sizeof(char));
	if (!password)
	{
		printf("Error: memory allocation failure");
		return -1;
	}
	else
	{
		for (int i = 0; i < *max_length + 1; i++)
		{
			password[i] = '\0';
		}
		for (unsigned long j = 0; j < count; j++)
		{
			int length = rand() % (*max_length - *min_length + 1) + *min_length;
			int alphabet_length = strlen(alphabet);

			for (int i = 0; i < length; i++)
			{
				password[i] = alphabet[rand() % (alphabet_length)];
			}
			printf("%s\n", password);
			for (int i = 0; i < *max_length + 1; i++)
			{
				password[i] = '\0';
			}
			free(password);
			return 0;
		}
	}
}