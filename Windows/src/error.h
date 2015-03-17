/*******************************************************
 *	error.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: 请阅读 LICENSE 文件
 *	Description(描述):错误和警告定义
 ******************************************************/
#pragma once
#ifndef ERROR_H
#define ERROR_H

#include "destiny.h"
#include "log.h"

/*log日志记录*/

/*错误*/
namespace Error {

	static const int error_unknown = 0;//未知错误
	static const int error_no_such_file = 1;//未找到文件
	static const int error_syntax_error = 2;//语法错误
	static const int error_no_file = 3;//没有文件
	static const int error_lose_arguments = 4;//参数缺失
	static const int error_too_much_arguments = 5;//参数过多
	static const int warning_no_such_file = 6;//未找到文件
	static const int error_no_database_file = 7;//没有打开数据库
	static const int error_unknown_command = 8;//未知指令
	static const int error_table_not_exists = 9;//不存在此表
	static const int error_table_exists = 10;//已存在此表
	static const int error_table_num_overflow = 11;//表数量达到上限
	static const int error_column_num_not_match = 12;//数据字段数量不匹配
	static const int error_column_repeat = 13;//数据字段重复
	static const int error_row_overflow = 14;//超出最大行限制
	static const int error_column_not_found = 15;//某些列不存在
	static const int error_keyword = 16;//关键字
	static const int error_logic_expression = 17;//错误的逻辑表达式
	static const int error_database_file_crash = 18;//数据库文件损坏
	static const int error_expression = 19;//数据库文件损坏

}

using namespace Error;

/*打印错误信息*/
void print_error(int error_code, string error_information, string error_arguments) {
	bool error_or_warning = true;//error
	string default_error_str = "";
	switch (error_code) {
		case error_unknown:
			default_error_str = "error:未知错误:";
			break;
		case error_no_such_file:
			default_error_str = "error:不存在这个文件:";
			break;
		case error_syntax_error:
			default_error_str = "error:语法错误:";
			break;
		case error_no_file:
			default_error_str = "error:文件缺失:";
			break;
		case error_lose_arguments:
			default_error_str = "error:参数缺失:";
			break;
		case error_too_much_arguments:
			default_error_str = "error:参数过多:";
			break;
		case warning_no_such_file:
			error_or_warning = false;//warning
			default_error_str = "warning:未找到此文件:";
			break;
		case error_no_database_file:
			default_error_str = "error:没有打开数据库:";
			break;
		case error_unknown_command:
			default_error_str = "error:未知指令:";
			break;
		case error_table_not_exists:
			default_error_str = "eror:不存在此表:";
			break;
		case error_table_exists:
			default_error_str = "error:已存在此表:";
			break;
		case error_table_num_overflow:
			default_error_str = "error:表数量已达到上限:";
			break;
		case error_column_num_not_match:
			default_error_str = "error:数据字段数量不匹配:";
			break;
		case error_column_repeat:
			default_error_str = "error:字段重复:";
			break;
		case error_row_overflow:
			default_error_str = "error:超出最大行限制:";
			break;
		case error_column_not_found:
			default_error_str = "error:某些列不存在:";
			break;
		case error_keyword:
			default_error_str = "error:关键字:";
			break;
		case error_logic_expression:
			default_error_str = "error:错误的逻辑表达式:";
			break;
		case error_database_file_crash:
			default_error_str = "error:数据库文件损坏:";
			break;
		case error_expression:
			default_error_str = "error:错误的表达式:";
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