#pragma once

#include "type_aliases.h"

// ������ ���������.
int version();

// �������������� ������� �������� ����� � ������ �������� ������������ �������.
bool ip_list_transform(const ip_vector_strings& ip_list_from_file, ip_vector_arrays& ip_list_ready_to_use, const size_t& check_size );

// ���������� � �������� �������.
void reverse_sort(ip_vector_arrays& ip_pool);

// ��������������� ����� � �������.
void filter_output(const ip_vector_arrays& ip_pool, const std::vector<int>& vi_numbers);

// ��������������� ����� � ������� �� �������� ����� ������.
void filter_output_by_any_octet(const ip_vector_arrays& ip_pool, int value);

