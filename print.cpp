#include "print.h"

#include <iostream>

#include <boost/algorithm/string.hpp>

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

// Печать ip адреса.
void print_ip_address(const std::array<int, 4>& ip_address)
{
    for (int i = 0; i < 4; ++i) {
        if (i != 0) {
            std::cout << ".";
        }

        std::cout << ip_address.at(i);
    }

    std::cout << std::endl;
}

// Вывод на экран вектора с ip адресами - векторами строк .
void print_ip_vector(const ip_vector_arrays& ip_pool)
{
    for (ip_vector_arrays::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
        print_ip_address(*ip);
    }
}

