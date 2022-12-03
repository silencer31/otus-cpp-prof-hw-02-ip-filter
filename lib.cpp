#include "lib.h"
#include "print.h"
#include "version.h"

#include <algorithm>
#include <iostream>
#include <tuple>


int version() {
    return PROJECT_VERSION_PATCH;
}

// Преобразование вектора векторов строк в вектор массивов константного размера.
bool ip_list_transform(const ip_vector_strings& ip_list_from_file, ip_vector_arrays& ip_list_ready_to_use, const size_t& check_size)
{
    if (ip_list_from_file.empty()) {
        return false;
    }

    size_t result_size = 0; // Для проверки кол-ва удачно преобразованных векторов строк в int массивы.

    auto lambda_transform = [&ip_list_ready_to_use, &result_size](std::vector<std::string> str_vector) {
        std::array<int, 4> ip_address;

        for (size_t i = 0; i < 4; ++i) {
            try {
                const int octet{ std::stoi(str_vector.at(i)) };
                ip_address[i] = octet;
            }
            catch (const std::exception& ex) {
                std::cout << "Error IP transformation from string to int: " << ex.what() << '\n';
                break;
            }

            if (i == 3) { // Обработали все 4 части ай пи адреса.
                ip_list_ready_to_use.push_back(ip_address);
                ++result_size;
            }
        }
    };

    std::for_each(ip_list_from_file.begin(), ip_list_from_file.end(), lambda_transform);

    if (result_size != check_size) {
        return false;
    }

    return true;
}

// Сортировка в обратном порядке.
void reverse_sort( ip_vector_arrays& ip_pool)
{
    if (ip_pool.empty()) return;

    // Номер октеты адреса, по которому сортируем.
    size_t position = 0;

    // Итераторы начала и конца диаппазона сортировки.
    auto iter_01 = ip_pool.begin();
    auto iter_02 = ip_pool.end();

    // Лямбда для сортировки.
    auto reverse_lambda = [&position](std::array<int, 4> arr_1, std::array<int, 4> arr_2) mutable -> bool {
        return arr_1.at(position) > arr_2.at(position);
    };

    // Сортируем по первой октете весь вектор.
    std::sort(iter_01, iter_02, reverse_lambda);

    // Сортируем по второй октете, сохраняя начальную сортировку.
    int octet_1 = ip_pool.at(0).at(0);
    position = 1;

    for (size_t i = 0; i < ip_pool.size(); ++i) {
        if (octet_1 == ip_pool.at(i).at(0)) { continue; }

        iter_02 = ip_pool.begin() + i;
        std::sort(iter_01, iter_02, reverse_lambda); // Сортируем кусочек.

        iter_01 = iter_02;
        octet_1 = ip_pool.at(i).at(0);
    }

    std::sort(iter_01, ip_pool.end(), reverse_lambda); // Сортируем кусочек.

    // Сортируем по третьей октете, сохраняя предыдущую сортировку.
    std::pair<int, int> octets_1_2 = std::make_pair(ip_pool.at(0).at(0), ip_pool.at(0).at(1) );
    position = 2;
    iter_01 = ip_pool.begin();

    for (size_t i = 0; i < ip_pool.size(); ++i) {
        if ( octets_1_2 == std::make_pair( ip_pool.at(i).at(0), ip_pool.at(i).at(1) ) ) { continue; }

        iter_02 = ip_pool.begin() + i;
        std::sort(iter_01, iter_02, reverse_lambda); // Сортируем кусочек.

        iter_01 = iter_02;
        octets_1_2 = std::make_pair( ip_pool.at(i).at(0), ip_pool.at(i).at(1)  );
    }

    std::sort(iter_01, ip_pool.end(), reverse_lambda); // Сортируем кусочек.


    // Сортируем по последней октете, сохраняя предыдущую сортировку.
    std::tuple<int, int, int> octets_1_2_3 = std::make_tuple( ip_pool.at(0).at(0), ip_pool.at(0).at(1), ip_pool.at(0).at(2) );
    position = 3;
    iter_01 = ip_pool.begin();

    for (size_t i = 0; i < ip_pool.size(); ++i) {
        if ( octets_1_2_3 == std::make_tuple( ip_pool.at(i).at(0), ip_pool.at(i).at(1), ip_pool.at(i).at(2) ) ) { continue; }

        iter_02 = ip_pool.begin() + i;
        std::sort(iter_01, iter_02, reverse_lambda); // Сортируем кусочек.

        iter_01 = iter_02;
        octets_1_2_3 = std::make_tuple( ip_pool.at(i).at(0), ip_pool.at(i).at(1), ip_pool.at(i).at(2) );
    }

    std::sort(iter_01, ip_pool.end(), reverse_lambda); // Сортируем кусочек.
}

// Отсортированный вывод в консоль.
void filter_output(const ip_vector_arrays& ip_pool, const std::vector<int>& vi_numbers)
{
    if (ip_pool.empty()) return;
    if (vi_numbers.empty() || (vi_numbers.size() > 4)) return;

    auto lambda_output = [vi_numbers](const std::array<int, 4>& ip_address) {
        bool compare_flag = true;
        for (size_t i = 0; i < vi_numbers.size(); ++i) {
            if ( ip_address.at(i) != vi_numbers.at(i)) {
                compare_flag = false;
                break;
            }
        }
        
        if (compare_flag) {
            print_ip_address(ip_address);
        }
    };

    std::for_each(ip_pool.begin(), ip_pool.end(), lambda_output);
}

// Отсортированный вывод в консоль по значению любой октеты.
void filter_output_by_any_octet(const ip_vector_arrays& ip_pool, int value)
{
    if (ip_pool.empty()) return;

    auto lambda_output = [value](const std::array<int, 4>& ip_address) {
         for (size_t i = 0; i < 4; ++i) {
            if ( ip_address.at(i) == value) {
                print_ip_address(ip_address);
                break;
            }
        }
    };

    std::for_each(ip_pool.begin(), ip_pool.end(), lambda_output);
}