#pragma once

#include"check_all_arguments.h"
#include"parsing_arguments.h"
#include"generate_passwords.h"

int main(int number_of_arguments, char* command_line_arguments[])
{
    if (number_of_arguments <= 1)
    {
        display_error_message();
        return -1;
    }

    if (check_all_arguments(command_line_arguments) != 0)
        return 1;
    int max_password_length;
    int min_password_length;
    unsigned long password_count = get_password_count(command_line_arguments);
    char* password_alphabet = get_password_alphabet(command_line_arguments);
    get_password_length(command_line_arguments, &min_password_length, &max_password_length);
    generate_passwords(&min_password_length, &max_password_length, password_count, password_alphabet);

    free(password_alphabet);
    return 0;
}