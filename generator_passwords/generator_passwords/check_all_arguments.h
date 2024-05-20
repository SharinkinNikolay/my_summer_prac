#pragma once

#include "check_arguments.h"

int check_all_arguments(const char* argv[])
{
    if (check_alphabet_options(argv) != 0)//проверка сосуществования -С и -а
        return 1;
    if (check_alphabet(argv) != 0) // проверка аргументов -С и -а
        return 1;
    if (check_length_options(argv) != 0)// проверка сосуществования -m1 -m2 и n
        return 1;
    if (check_other_options(argv) != 0)// проверка на повторы -n и -с
        return 1;
    if (check_arguments_are_numbers(argv) != 0)// проверка числовых аргументов после  -m1 -m2 -n -c 
        return 1;
    if (check_min_max(argv) != 0)//проверка соответствия значений -m1 -m2 (m1<m2)
        return 1;

    return 0;
}

void display_error_message()
{
    printf("COULD NOT DEFINE PASSWORD CHARACTERISTICS\n\nPlease specify at least one of the available options:\n\n -m1/-m2 | min/max length of a password\n -n      | password length\n -a abc  | password alphabet\n -c      | number of passwords\n -C aADS | choose one or more of the preset alphabets\n");
    printf("\nNote that:\n\n -m1/-m2 is incompatible with -n\n -C is incompatible with -a\n -m1 argument cannot be bigger than -m2 argument\n -C and -a parameters cannot be present more than once\n -C argument can only contain one or several of the following letters: aADS , but not more then one for each\n");
    printf("\nThese parameters have default argument values in case they are not found: \n [-n (10)] \n [-c (5)] \n [-a & -C (ILOVEROCKNROLL)] \n\nEvery parameter is optional on its own, but at least one should be specified\n");
}