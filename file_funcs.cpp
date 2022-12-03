#include "file_funcs.h"

#include <fstream>
#include <algorithm>
#include <iostream>
#include <iterator>

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

// Чтение списка ip адресов из указанного файла.
// В случае успеха возвращаем кол-во прочитанных строк с адресами.
size_t get_ip_list_from_file(ip_vector_strings& vvs, const std::string& filename)
{
    std::ifstream input{ filename };

    if (!input.is_open()) {
        std::cerr << "Failed to open file " << filename << '\n';
        return 0;
    }

    // Сделаем подсчет количества строк в файле для резервирования памяти в векторе - приёмнике.
    size_t strings_number = 0;

    std::for_each(std::istream_iterator<std::string>(input),
        std::istream_iterator<std::string>(),
        [&strings_number](const std::string& line) {
            if (line.find('.') != std::string::npos) {
                ++strings_number;
            }
        }
    );
    
    if (strings_number == 0) {
        input.close();
        return 0;
    }

    vvs.reserve(strings_number);

    input.clear();
    input.seekg(input.beg);
    
    std::for_each(std::istream_iterator<std::string>(input),
        std::istream_iterator<std::string>(),
        [&vvs, &strings_number](const std::string& line) {
            //std::vector<std::string> v = split(line, '\t'); // Тут такой способ не подходит.
            if (line.find('.') != std::string::npos) {
                std::vector<std::string> vec = split(line, '.');
                if (vec.size() == 4) { // Проверяем чтобы ай пи был корректен.
                    vvs.push_back(vec);
                }
                else {
                    strings_number = 0; // Обнуляем, если строка некорректна.
                }
            }

        }
    );

    input.close();

    return strings_number;
}

// Запись списка ip адресов в файл.
bool write_ip_list_to_file(const ip_vector_arrays& ip_pool, const std::string& filename)
{
    std::ofstream output{ filename };

    if (!output.is_open()) {
        std::cerr << "Failed to open file " << filename << '\n';
        return false;
    }

    bool result = true;

    auto lambda_write_tf = [&output](std::array<int, 4> ip_address) {
        for (size_t i = 0; i < 4; ++i) {
            output << ip_address.at(i);
            if (i < 3) { output << '.'; }
        }
        output << '\n';
    };

    std::for_each(ip_pool.begin(), ip_pool.end(), lambda_write_tf);

    output.close();

    return result;
}