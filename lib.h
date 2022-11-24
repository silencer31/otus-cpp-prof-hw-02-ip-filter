#pragma once

#include <string>
#include <vector>

// ������ ���������.
int version();

// ������ ������ ip ������� �� ���������� �����.
bool get_ip_list_from_file(std::vector<std::vector<std::string> >& vvs, const std::string& filename);

// ������ ������ ip ������� � ����.
bool write_ip_list_to_file(std::vector<std::vector<std::string> >& vvs_ip, const std::string& filename);

// ���������� ������  �� ������ ����� ����� ��������� ������.
std::vector<std::string> split(const std::string& str, char d);

// ������ �������-�����, �������������� ip �����.
void print_ip_address(const std::vector<std::string>& ip_addr);

// ����� �� ����� ������� � ip �������� - ��������� ����� .
void print_ip_vector(const std::vector<std::vector<std::string> >& vvs );

// ���������� ������������, �������� �� � ������.
bool ask_to_print(const std::string& question);

// ���������� � �������� �������.
void reverse_sort(std::vector<std::vector<std::string> >& vvs_ip);

// ��������������� ����� � �������.
void filter_output(const std::vector<std::vector<std::string> >& vvs_ip, const std::vector<int>& vi_numbers);

// ��������������� ����� � ������� �� �������� ����� ������.
void filter_output_by_any_octet(const std::vector<std::vector<std::string> >& vvs_ip, int value);

