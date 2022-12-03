#pragma once

#include "type_aliases.h"

// ¬ерси€ программы.
int version();

// ѕреобразование вектора векторов строк в вектор массивов константного размера.
bool ip_list_transform(const ip_vector_strings& ip_list_from_file, ip_vector_arrays& ip_list_ready_to_use, const size_t& check_size );

// —ортировка в обратном пор€дке.
void reverse_sort(ip_vector_arrays& ip_pool);

// ќтсортированный вывод в консоль.
void filter_output(const ip_vector_arrays& ip_pool, const std::vector<int>& vi_numbers);

// ќтсортированный вывод в консоль по значению любой октеты.
void filter_output_by_any_octet(const ip_vector_arrays& ip_pool, int value);

