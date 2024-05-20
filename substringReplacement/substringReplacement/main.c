#include <stdio.h>

#define MAX_BUFFER_SIZE 512

void shift_remainder(char* remainder)
{
	int len = get_string_length(remainder) - 1;
	for (int i = 0; i < len; i++)
	{
		remainder[i] = remainder[i + 1];
	}
}

int get_string_length(char* input_string)
{
	int counter = 0;
	while (input_string[counter] != '\0')
	{
		counter++;
	}
	return counter;
}

void copy_chars(char* source_buffer, char* destination_buffer, int counter, int source_index)
{
	int i = 0;
	for (int j = source_index; counter > 0; j++)
	{
		destination_buffer[i] = source_buffer[j + 1];
		i++;
		counter--;
	}
	return;
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		printf("Error: insufficient number of arguments\n");
		return -1;
	}

	char* input_file_name = argv[1];
	char* output_file_name = argv[2];
	char* string_to_replace = argv[3];
	char* replacement_string = argv[4];

	FILE* input_file = fopen(input_file_name, "r");
	FILE* output_file = fopen(output_file_name, "w");
	if (input_file == NULL || output_file == NULL)
	{
		printf("Error: files cannot be opened\n");
		return -1;
	}

	char buffer[MAX_BUFFER_SIZE];
	char remainder[MAX_BUFFER_SIZE];

	int bytes_read = 0;
	int found_count = 0;
	int block_start_index = 0;
	int remainder_is_empty = 1;
	while ((bytes_read = fread(buffer, 1, MAX_BUFFER_SIZE, input_file)) > 0)
	{
		//����� found_count ��������� � ������� �����, ������ ����� ��������� ��� get_string_length(string_to_replace)-found_count ���������
		//���� ��� ���������, ������� ���������� ������ � �������� ��������� �� get_string_length(string_to_replace)-found_count
		//���� ����� ������������ �� �����-�� �������, ������� � ���� found_count ���� �� remainder + i ����������������, ������� �� �������
		//� �������� ��������� �� i
		if (found_count > 0)
		{
			int elements_to_check = get_string_length(string_to_replace) - found_count;
			int check_sum = 0;
			int string_index = found_count;
			//���� ���� �������� ������� �����, ��� ����� ��� ����������
			if (bytes_read < elements_to_check)
			{
				fwrite(remainder, 1, found_count, output_file);
				fwrite(buffer, 1, bytes_read, output_file);
				found_count = 0;
				remainder_is_empty = 1;
				break;
			}
			for (int i = 0; i < elements_to_check; i++)
			{
				//����� ������������ � i-��, �������� ������ ������ �� �������, �������� �������� �� 1 ������ � ���������
				//���� ������� �� ��������
				if (buffer[i] != string_to_replace[string_index])
				{
					fwrite(remainder, 1, 1, output_file);
					shift_remainder(remainder);
					found_count--;
					string_index = found_count;
					elements_to_check++;
					check_sum = 0;
					i = -1;
					if (found_count == 0)
					{
						block_start_index = 0;
						break;
					}
				}
				//����� ����������, ���������, ������� �� ������: ���� ��, �� ���������� � �������� ��������� ������ ��
				else
				{
					check_sum++;
					string_index++;
				}
			}
			//���� ��� �������� �������, �� ������� ������ � �������� ��������� �� elements_to_check + 1
			if (check_sum == elements_to_check)
			{
				fwrite(replacement_string, 1, get_string_length(replacement_string), output_file);
				found_count = 0;
				block_start_index = elements_to_check;
				remainder_is_empty = 1;
			}
		}
		for (int i = block_start_index; i < bytes_read; i++)
		{
			if (buffer[i] != string_to_replace[0] && found_count == 0)
				//���� ������ ������ �� ���������, ����� ����� ������ ++
			{
				fwrite(buffer + i, 1, 1, output_file);
				continue;
			}
			if (buffer[i] == string_to_replace[0] && found_count == 0)
				//���� ����� ������ ���������, �������� ���������
			{
				int string_pos = 0;
				int init_pos = i; //��������� �������, � ������� ������ �������� ���������, ����� ������ ������ ����� ������
				for (int pos = i; pos < bytes_read && pos < init_pos + get_string_length(string_to_replace); pos++)
				{
					//���� ���������� �� ������� �� �� ������,������� ��� �������� ��������� � �������� �������
					if (buffer[pos] != string_to_replace[string_pos] && found_count > 0)
					{
						fwrite(string_to_replace, 1, found_count, output_file);
						i += found_count - 1;
						found_count = 0;
						break;
					}
					//�� �������,��� ����� �� ����� ���������� ������ ������� ��������� � ��������� �� ���������� � found_count
					if (buffer[pos] == string_to_replace[string_pos])
					{
						found_count++;
						string_pos++;
					}
					//���� ������ ������, �� ������� ���������� ������������������,������������� ��������� � �����
					// �� ����� ����� � �������� �������
					if (found_count == get_string_length(string_to_replace))
					{
						fwrite(replacement_string, 1, get_string_length(replacement_string), output_file);
						i += found_count - 1;
						found_count = 0;
						break;
					}
					//���� found_count > 0, �� ���� ������� � �����, ��������� found ���������� ��������� � remainder, ����� � ������� ����� 
					//��������� ������ ���������� �����
					if (found_count > 0 && pos + 1 == bytes_read)
					{
						copy_chars(buffer, remainder, found_count, pos - found_count);
						remainder_is_empty = 0;
						break;
					}
				}
			}
		}
	}
	if (remainder_is_empty == 0)
	{
		fwrite(remainder, 1, found_count, output_file);
	}

	fclose(input_file);
	fclose(output_file);
}