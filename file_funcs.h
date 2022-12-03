#pragma once

#include "type_aliases.h"


// Разделение строки  на вектор строк через указанный символ.
std::vector<std::string> split(const std::string& str, char d);

// Чтение списка ip адресов из указанного файла.
size_t get_ip_list_from_file(ip_vector_strings& vvs, const std::string& filename);

// Запись списка ip адресов в файл.
bool write_ip_list_to_file(const ip_vector_arrays& ip_pool, const std::string& filename);