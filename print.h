#pragma once

#include "type_aliases.h"

// Спрашиваем пользователя, выводить ли в печать.
bool ask_to_print(const std::string& question);

// Печать ip адреса.
void print_ip_address(const std::array<int, 4>& ip_address);

// Вывод на экран вектора с ip адресами - векторами строк .
void print_ip_vector(const ip_vector_arrays& ip_pool);