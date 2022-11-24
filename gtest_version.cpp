#include "lib.h"

#include <gtest/gtest.h>

// 
TEST(SomeGtests, TestVersionA){

    // Assert
    ASSERT_TRUE(version() > 0);
}

TEST(SomeGtests, TestIpList) {
    std::vector<std::vector<std::string> > ip_pool; // ������, ������� ���������.
    std::vector<std::vector<std::string> > ip_pool_control; // ����������� ������.

    ASSERT_TRUE(get_ip_list_from_file(ip_pool, std::string{ "ip_filter.tsv" }));
    ASSERT_TRUE(get_ip_list_from_file(ip_pool_control, std::string{ "control_ip_list.txt" }));

    reverse_sort(ip_pool); // ����������.

    // ��������� ���������������� ������ � �����������.
    ASSERT_TRUE(ip_pool.size() == ip_pool_control.size());

    auto ip_iter = ip_pool.begin();
    auto ip_iter_control = ip_pool_control.begin();

    while (ip_iter != ip_pool.end()) {
        ASSERT_TRUE(*ip_iter == *ip_iter_control);
        ++ip_iter;
        ++ip_iter_control;
    }
}