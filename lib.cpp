#include "lib.h"

#include "version.h"

#include <algorithm>
#include <iostream>
#include <fstream>

#include <boost/algorithm/string.hpp>

int version() {
    return PROJECT_VERSION_PATCH;
}

// Чтение списка ip адресов из указанного файла.
bool get_ip_list_from_file(std::vector<std::vector<std::string> >& vvs, const std::string& filename)
{
    std::ifstream input{ filename };
    
    if (!input.is_open()) {
        std::cerr << "Failed to open file " << filename << '\n';
        return false;
    }

    bool result = true;

    std::for_each(std::istream_iterator<std::string>(input),
        std::istream_iterator<std::string>(),
        [&vvs, &result](const std::string& line) { 
            //std::vector<std::string> v = split(line, '\t'); // Тут такой способ не подходит.
            if (line.find('.') != std::string::npos) {
                std::vector<std::string> vec = split(line, '.');
                if (vec.size() == 4) { // Проверяем чтобы ай пи был корректен.
                    vvs.push_back(vec);
                } 
                else {
                    result = false;
                }
            }
            
        }
    );

    input.close();

    return result;
}

// Запись списка ip адресов в файл.
bool write_ip_list_to_file(std::vector<std::vector<std::string> >& vvs_ip, const std::string& filename)
{
    std::ofstream output{ filename };

    if (!output.is_open()) {
        std::cerr << "Failed to open file " << filename << '\n';
        return false;
    }

    bool result = true;

    auto lambda_write_tf = [&output](std::vector<std::string> str_vector) {
        for (size_t i = 0; i < str_vector.size(); ++i) {
            output << str_vector.at(i);
            if (i < 3) { output << '.'; }
        }
        output << '\n';
    };

    std::for_each(vvs_ip.begin(), vvs_ip.end(), lambda_write_tf);

    output.close();

    return result;
}

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string& str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

// Печать вектора-строк, представляющий ip адрес.
void print_ip_address(const std::vector<std::string>& ip_addr)
{
    for (std::vector<std::string>::const_iterator ip_part = ip_addr.cbegin(); ip_part != ip_addr.cend(); ++ip_part)
    {
        if (ip_part != ip_addr.cbegin())
        {
            std::cout << ".";

        }
        std::cout << *ip_part;
    }
    std::cout << std::endl;
}

// Вывод на экран вектора с ip адресами - векторами строк .
void print_ip_vector(const std::vector<std::vector<std::string> >& vvs)
{
    for (std::vector<std::vector<std::string> >::const_iterator ip = vvs.cbegin(); ip != vvs.cend(); ++ip)
    //for (std::vector<std::vector<std::string> >::const_iterator ip = vvs.cbegin(); ip != (vvs.cbegin() + 30); ++ip)
    {
        print_ip_address(*ip);
    }
}

// Спрашиваем пользователя, выводить ли в печать.
bool ask_to_print(const std::string& question)
{
    std::cout << question << std::endl;

    std::string user_answer;
    std::getline(std::cin, user_answer);
    boost::algorithm::to_lower(user_answer);

    if (user_answer.compare("y") == 0) {
        return true;
    }
    
    return false;
}

// Сортировка в обратном порядке.
void reverse_sort(std::vector<std::vector<std::string> >& vvs_ip)
{
    if (vvs_ip.empty()) return;

    // Номер октеты адреса, по которому сортируем.
    size_t position = 0;

    // Итераторы начала и конца диаппазона сортировки.
    auto iter_01 = vvs_ip.begin();
    auto iter_02 = vvs_ip.end();

    // Лямбда для сортировки.
    auto reverse_lambda = [&position](std::vector<std::string> str_vec_1, std::vector<std::string> str_vec_2) mutable -> bool {
        return std::stoi(str_vec_1.at(position)) > std::stoi(str_vec_2.at(position));
    };

    // Сортируем по первой октете весь вектор.
    std::sort(iter_01, iter_02, reverse_lambda);

    // Сортируем по второй октете, сохраняя начальную сортировку.
    int octet_1 = std::stoi(vvs_ip.at(0).at(0));
    position = 1;

    for (size_t i = 0; i < vvs_ip.size(); ++i) {
        if (octet_1 == std::stoi(vvs_ip.at(i).at(0))) { continue; }

        iter_02 = vvs_ip.begin() + i;
        std::sort(iter_01, iter_02, reverse_lambda); // Сортируем кусочек.

        iter_01 = iter_02;
        octet_1 = std::stoi(vvs_ip.at(i).at(0));
    }

    std::sort(iter_01, vvs_ip.end(), reverse_lambda); // Сортируем кусочек.

    // Сортируем по третьей октете, сохраняя предыдущую сортировку.
    std::pair<int, int> octets_1_2 = std::make_pair( std::stoi(vvs_ip.at(0).at(0)), std::stoi(vvs_ip.at(0).at(1)) );
    position = 2;
    iter_01 = vvs_ip.begin();

    for (size_t i = 0; i < vvs_ip.size(); ++i) {
        if (octets_1_2 == std::make_pair( std::stoi(vvs_ip.at(i).at(0)), std::stoi(vvs_ip.at(i).at(1))) ) { continue; }

        iter_02 = vvs_ip.begin() + i;
        std::sort(iter_01, iter_02, reverse_lambda); // Сортируем кусочек.

        iter_01 = iter_02;
        octets_1_2 = std::make_pair(std::stoi(vvs_ip.at(i).at(0)), std::stoi(vvs_ip.at(i).at(1)) );
    }

    std::sort(iter_01, vvs_ip.end(), reverse_lambda); // Сортируем кусочек.


    // Сортируем по последней октете, сохраняя предыдущую сортировку.
    std::tuple<int, int, int> octets_1_2_3 = std::make_tuple(std::stoi(vvs_ip.at(0).at(0)), std::stoi(vvs_ip.at(0).at(1)), std::stoi(vvs_ip.at(0).at(2)));
    position = 3;
    iter_01 = vvs_ip.begin();

    for (size_t i = 0; i < vvs_ip.size(); ++i) {
        if ( octets_1_2_3 == std::make_tuple(std::stoi(vvs_ip.at(i).at(0)), std::stoi(vvs_ip.at(i).at(1)), std::stoi(vvs_ip.at(i).at(2))) ) { continue; }

        iter_02 = vvs_ip.begin() + i;
        std::sort(iter_01, iter_02, reverse_lambda); // Сортируем кусочек.

        iter_01 = iter_02;
        octets_1_2_3 = std::make_tuple(std::stoi(vvs_ip.at(i).at(0)), std::stoi(vvs_ip.at(i).at(1)), std::stoi(vvs_ip.at(i).at(2)));
    }

    std::sort(iter_01, vvs_ip.end(), reverse_lambda); // Сортируем кусочек.
}

// Отсортированный вывод в консоль.
void filter_output(const std::vector<std::vector<std::string> >& vvs_ip, const std::vector<int>& vi_numbers)
{
    if (vvs_ip.empty()) return;
    if (vi_numbers.empty() || (vi_numbers.size() > 4)) return;

    auto lambda_output = [vi_numbers](std::vector<std::string> str_vector) {
        bool compare_flag = true;
        for (size_t i = 0; i < vi_numbers.size(); ++i) {
            if (std::stoi(str_vector.at(i)) != vi_numbers.at(i)) {
                compare_flag = false;
                break;
            }
        }
        
        if (compare_flag) {
            print_ip_address(str_vector);
        }
    };

    std::for_each(vvs_ip.begin(), vvs_ip.end(), lambda_output);
}

// Отсортированный вывод в консоль по значению любой октеты.
void filter_output_by_any_octet(const std::vector<std::vector<std::string> >& vvs_ip, int value)
{
    if (vvs_ip.empty()) return;

    auto lambda_output = [value](std::vector<std::string> str_vector) {
         for (size_t i = 0; i < str_vector.size(); ++i) {
            if (std::stoi(str_vector.at(i)) == value) {
                print_ip_address(str_vector);
                break;
            }
        }
    };

    std::for_each(vvs_ip.begin(), vvs_ip.end(), lambda_output);
}