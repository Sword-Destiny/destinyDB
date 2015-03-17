/*******************************************************
 *	includes.h
 *	author:��������
 *	copyright(c) 2015 - ~: All rifgts reserved! ��������Ȩ����
 *	Description(����):��Ŀ��������������C++11��׼���ļ�,һЩȫ�ֱ���,��������,���ݽṹ����
 ******************************************************/
#pragma once
#ifndef INCLUDES_H
#define INCLUDES_H


#define MAX_TABLE_NUM 10000
#define MAX_TABLE_NUM_STR "10000"
#define MAX_LINE_NUM 10000000
#define MAX_LINE_NUM_STR "10000000"
#define MAX_COLUMN_NUM 100000
#define MAX_COLUMN_NUM_STR "100000"

#include <regex>
using std::regex;
using std::regex_error;
using std::regex_match;
using std::regex_search;
using std::sregex_token_iterator;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::ios;
using std::istream;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <string>
using std::string;
using std::getline;

#include <sstream>
using std::stringstream;

#include <iomanip>
using std::setw;

#include <cstdio>
#include <cstdlib>
using std::sprintf;

#include "../data_struct/single_list.h"
#include "../data_struct/Array.h"

const string database_file_error = "���ݿ��ļ���!";

static const regex regex_bigger_than(">");
static const regex regex_smaller_than("<");
static const regex regex_bigger_equal(">=");
static const regex regex_smaller_equal("<=");
static const regex regex_equal("=");
static const regex regex_equality("={1,2}");
static const regex regex_not_equal("!=");
static const regex regex_op("[><=!]+");
static const regex regex_empty("[ \\t]+");//ƥ�����������հ��ַ�,�������س��ͻ���
static const regex regex_empty_seperator("[ \\t]*;[ \\t]*");//ƥ��հ��ַ������ֺ�
static const regex regex_seperator(";");//ƥ��ֺ�
static const regex regex_comma(",");//ƥ�䶺��
static const regex regex_or("\\|");
static const regex regex_and("\\&");
static const regex regex_empty_yes("[ \\t]*[Yy][Ee][Ss][ \\t]*|[ \\t]*[Yy][ \\t]*");
static const regex regex_yes("[Yy][Ee][Ss]|[Yy]|[Tt][Rr][Uu][Ee]|[Tt]");
static const regex regex_no("[Nn][Oo]|[Nn]|[Ff][Aa][Ll][Ss][Ee]|[Ff]");

static const sregex_token_iterator end;//������ʽĩβ

/*�߼�ƥ������*/
enum logic_match_type {
	equal, not_equal, bigger_than, smaller_than, bigger_or_equal, smaller_or_equal
};

static const regex logic_match_types[6] = {
	regex_bigger_than,
	regex_smaller_than,
	regex_equality,
	regex_bigger_equal,
	regex_smaller_equal,
	regex_not_equal
};

/*�߼�ת��:��*/
static logic_match_type logic_reverse(const logic_match_type &m) {
	switch (m) {
		case equal:
			return not_equal;
		case not_equal:
			return equal;
		case bigger_than:
			return smaller_or_equal;
		case bigger_or_equal:
			return smaller_than;
		case smaller_than:
			return bigger_or_equal;
		case smaller_or_equal:
			return bigger_than;
		default:
			return equal;
	}
}

logic_match_type get_match_type(int type_id) {
	switch (type_id) {
		case 0:
			return bigger_than;
		case 1:
			return smaller_than;
		case 2:
			return equal;
		case 3:
			return bigger_or_equal;;
		case 4:
			return smaller_or_equal;
		case 5:
			return not_equal;
		default:
			return equal;
	}
}

/*�Ƿ�����*/
bool is_num(const string &str) {
	int dot_num = 0;
	for (unsigned int i = 0; i < str.length(); i++) {
		if (str[i] < 48 || str[i]>57) {
			if (str[i] == '.') {
				dot_num++;
			}
			else if (str[i] == '-'&&i == 0) {
				continue;
			}
			else {
				return false;
			}
		}
	}
	if (dot_num > 1) {
		return false;
	}
	return true;
}

bool is_str_equal(const string &str1, const string &str2) {
	if (is_num(str1) && is_num(str2)) {
		return atof(str1.c_str()) == atof(str2.c_str());
	}
	return str1 == str2;
}

/*Ѱ���ַ����е�logic_match_type,���ƥ��һ��,����0-5,����logic_match_types�����±�,���򷵻�6*/
static int match_type_num(const string& str) {
	sregex_token_iterator it(str.begin(), str.end(), regex_op, -1);
	int match_num = 0;
	while (it != end) {
		match_num++;
		it++;
	}
	if (match_num < 2 || match_num > 2) {
		return 6;
	}
	for (int i = 5; i >= 0; i--) {
		if (regex_search(str, logic_match_types[i])) {
			return i;
		}
	}
	return 6;
}

/*�ַ�������������*/
static bool bigger_than_str(const string& str1, const string& str2) {
	if (is_num(str1) && is_num(str2)) {
		return atof(str1.c_str()) > atof(str2.c_str());
	}
	for (unsigned int i = 0; i < str1.length(); i++) {
		if (i < str2.length()) {
			if (str1[i]>str2[i]) {
				return true;
			}
			else if (str1[i] < str2[i]) {
				return false;
			}
		}
		else {
			return true;
		}
	}
	return false;
}

/*��ӡ������Ϣ*/
void print_error(int error_code, string error_information = "", string error_arguments = "");

#endif
