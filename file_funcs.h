#pragma once

#include "type_aliases.h"


// ���������� ������  �� ������ ����� ����� ��������� ������.
std::vector<std::string> split(const std::string& str, char d);

// ������ ������ ip ������� �� ���������� �����.
size_t get_ip_list_from_file(ip_vector_strings& vvs, const std::string& filename);

// ������ ������ ip ������� � ����.
bool write_ip_list_to_file(const ip_vector_arrays& ip_pool, const std::string& filename);