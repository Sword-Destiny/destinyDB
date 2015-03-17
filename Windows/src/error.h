/*******************************************************
 *	error.h
 *	author:��������
 *	copyright(c) 2015 - ~: ���Ķ� LICENSE �ļ�
 *	Description(����):����;��涨��
 ******************************************************/
#pragma once
#ifndef ERROR_H
#define ERROR_H

#include "destiny.h"
#include "log.h"

/*log��־��¼*/

/*����*/
namespace Error {

	static const int error_unknown = 0;//δ֪����
	static const int error_no_such_file = 1;//δ�ҵ��ļ�
	static const int error_syntax_error = 2;//�﷨����
	static const int error_no_file = 3;//û���ļ�
	static const int error_lose_arguments = 4;//����ȱʧ
	static const int error_too_much_arguments = 5;//��������
	static const int warning_no_such_file = 6;//δ�ҵ��ļ�
	static const int error_no_database_file = 7;//û�д����ݿ�
	static const int error_unknown_command = 8;//δָ֪��
	static const int error_table_not_exists = 9;//�����ڴ˱�
	static const int error_table_exists = 10;//�Ѵ��ڴ˱�
	static const int error_table_num_overflow = 11;//�������ﵽ����
	static const int error_column_num_not_match = 12;//�����ֶ�������ƥ��
	static const int error_column_repeat = 13;//�����ֶ��ظ�
	static const int error_row_overflow = 14;//�������������
	static const int error_column_not_found = 15;//ĳЩ�в�����
	static const int error_keyword = 16;//�ؼ���
	static const int error_logic_expression = 17;//������߼����ʽ
	static const int error_database_file_crash = 18;//���ݿ��ļ���
	static const int error_expression = 19;//���ݿ��ļ���

}

using namespace Error;

/*��ӡ������Ϣ*/
void print_error(int error_code, string error_information, string error_arguments) {
	bool error_or_warning = true;//error
	string default_error_str = "";
	switch (error_code) {
		case error_unknown:
			default_error_str = "error:δ֪����:";
			break;
		case error_no_such_file:
			default_error_str = "error:����������ļ�:";
			break;
		case error_syntax_error:
			default_error_str = "error:�﷨����:";
			break;
		case error_no_file:
			default_error_str = "error:�ļ�ȱʧ:";
			break;
		case error_lose_arguments:
			default_error_str = "error:����ȱʧ:";
			break;
		case error_too_much_arguments:
			default_error_str = "error:��������:";
			break;
		case warning_no_such_file:
			error_or_warning = false;//warning
			default_error_str = "warning:δ�ҵ����ļ�:";
			break;
		case error_no_database_file:
			default_error_str = "error:û�д����ݿ�:";
			break;
		case error_unknown_command:
			default_error_str = "error:δָ֪��:";
			break;
		case error_table_not_exists:
			default_error_str = "eror:�����ڴ˱�:";
			break;
		case error_table_exists:
			default_error_str = "error:�Ѵ��ڴ˱�:";
			break;
		case error_table_num_overflow:
			default_error_str = "error:�������Ѵﵽ����:";
			break;
		case error_column_num_not_match:
			default_error_str = "error:�����ֶ�������ƥ��:";
			break;
		case error_column_repeat:
			default_error_str = "error:�ֶ��ظ�:";
			break;
		case error_row_overflow:
			default_error_str = "error:�������������:";
			break;
		case error_column_not_found:
			default_error_str = "error:ĳЩ�в�����:";
			break;
		case error_keyword:
			default_error_str = "error:�ؼ���:";
			break;
		case error_logic_expression:
			default_error_str = "error:������߼����ʽ:";
			break;
		case error_database_file_crash:
			default_error_str = "error:���ݿ��ļ���:";
			break;
		case error_expression:
			default_error_str = "error:����ı��ʽ:";
			break;
		default:
			break;
	}
	cout << default_error_str << error_information << error_arguments << endl;
	stringstream ss;
	ss << (error_or_warning ? "error_code_" : "warning_code_") << error_code << "\t" << default_error_str << error_information << error_arguments;
	Log::log(ss.str());
}
#endif