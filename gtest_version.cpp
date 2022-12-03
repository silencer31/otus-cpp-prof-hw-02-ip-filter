#include "lib.h"
#include "file_funcs.h"

#include <gtest/gtest.h>

// 
TEST(SomeGtests, TestVersionA){

    // Assert
    ASSERT_TRUE(version() > 0);
}

TEST(SomeGtests, TestIpList) {
    ip_vector_strings ip_list_from_file; // ������, ���������� �� �����.
    
    ip_vector_arrays ip_pool; // ������, ������� ���������.
    ip_vector_arrays ip_pool_control; // ����������� ������.

    size_t ip_pool_size = get_ip_list_from_file(ip_list_from_file, std::string{ "ip_filter.tsv" });
    ASSERT_TRUE( ip_pool_size > 0 );
    ASSERT_TRUE( ip_list_transform(ip_list_from_file, ip_pool, ip_pool_size) );

    ip_list_from_file.clear();
    
    size_t ip_pool_control_size = get_ip_list_from_file(ip_list_from_file, std::string{ "control_ip_list.txt" });
    ASSERT_TRUE(ip_pool_size > 0);
    ASSERT_TRUE(ip_list_transform(ip_list_from_file, ip_pool_control, ip_pool_control_size));

    ASSERT_TRUE(ip_pool_size == ip_pool_control_size); // ��������� �������� ������������ � ������������ �������.

    reverse_sort(ip_pool); // ����������.

    // ��������� ���������������� ������ � �����������.
    auto ip_iter = ip_pool.begin();
    auto ip_iter_control = ip_pool_control.begin();

    while (ip_iter != ip_pool.end()) {
        ASSERT_TRUE(*ip_iter == *ip_iter_control);
        ++ip_iter;
        ++ip_iter_control;
    }
}