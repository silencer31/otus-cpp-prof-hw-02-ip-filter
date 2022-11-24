#pragma once

#include <string>
#include <vector>

// Версия программы.
int version();

// Чтение списка ip адресов из указанного файла.
bool get_ip_list_from_file(std::vector<std::vector<std::string> >& vvs, const std::string& filename);

// Запись списка ip адресов в файл.
bool write_ip_list_to_file(std::vector<std::vector<std::string> >& vvs_ip, const std::string& filename);

// Разделение строки  на вектор строк через указанный символ.
std::vector<std::string> split(const std::string& str, char d);

// Печать вектора-строк, представляющий ip адрес.
void print_ip_address(const std::vector<std::string>& ip_addr);

// Вывод на экран вектора с ip адресами - векторами строк .
void print_ip_vector(const std::vector<std::vector<std::string> >& vvs );

// Спрашиваем пользователя, выводить ли в печать.
bool ask_to_print(const std::string& question);

// Сортировка в обратном порядке.
void reverse_sort(std::vector<std::vector<std::string> >& vvs_ip);

// Отсортированный вывод в консоль.
void filter_output(const std::vector<std::vector<std::string> >& vvs_ip, const std::vector<int>& vi_numbers);

// Отсортированный вывод в консоль по значению любой октеты.
void filter_output_by_any_octet(const std::vector<std::vector<std::string> >& vvs_ip, int value);

