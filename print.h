#pragma once

#include "type_aliases.h"

// ���������� ������������, �������� �� � ������.
bool ask_to_print(const std::string& question);

// ������ ip ������.
void print_ip_address(const std::array<int, 4>& ip_address);

// ����� �� ����� ������� � ip �������� - ��������� ����� .
void print_ip_vector(const ip_vector_arrays& ip_pool);