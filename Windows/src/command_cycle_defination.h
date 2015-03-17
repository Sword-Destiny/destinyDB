/*******************************************************
 *	command_cycle_defination.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: 请阅读 LICENSE 文件
 *	Description(描述):命令循环定义头文件
 ******************************************************/
#pragma once
#ifndef COMMAND_CYCLE_DEFINATION
#define COMMAND_CYCLE_DEFINATION
#include "destiny.h"
#include "error.h"
#include "database_file.h"

/*命令循环*/
namespace CommandCycle {

	string command = "";//命令行命令
	string single_command = "";
	bool end_of_last_command = true;//上一条命令是否执行完毕,或上一条命令是否完整
	bool enable_last_command = true;//是否允许不完整命令连接
	
	/*version命令*/
	void command_do_version(sregex_token_iterator &it);

	/*help命令*/
	void command_do_help(sregex_token_iterator &it);

	/*exit命令*/
	void command_do_exit(sregex_token_iterator &it);

	/*open命令*/
	void command_do_open(sregex_token_iterator &it);

	/*commit命令*/
	void command_do_commit(sregex_token_iterator &it);

	/*run命令*/
	void command_do_run(sregex_token_iterator &it);

	/*insert命令*/
	void command_do_insert(sregex_token_iterator &it);

	/*create命令*/
	void command_do_create(sregex_token_iterator &it);

	/*show命令*/
	void command_do_show(sregex_token_iterator &it);

	/*select命令*/
	void command_do_select(sregex_token_iterator &it);

	/*update命令*/
	void command_do_update(sregex_token_iterator &it);

	/*update命令*/
	void command_do_delete(sregex_token_iterator &it);

	/*rename命令*/
	void command_do_rename(sregex_token_iterator &it);

	/*autocommit命令*/
	void command_do_auto_commit(sregex_token_iterator &it);

	/*drop命令*/
	void command_do_drop(sregex_token_iterator &it);

	/*sort命令*/
	void command_do_sort(sregex_token_iterator &it);

	/*单条命令循环*/
	void command_single_cycle(const string &single_command_str);

	/*命令循环主函数*/
	void command_cycle(istream &ist, bool child_cycle = false);

	/*查询*/
	bool query(sregex_token_iterator &it, ResultSet *&current_result_set);

	/*打印参数错误信息*/
	inline void lose_argument_error(string error_information = "", string error_argument = "");

	template<class T>
	/*释放链表空间*/
	void list_free(SingleList<T*> &list);

	/*提醒提交更改*/
	void warning_commit();

	/*提醒提交更改*/
	bool check_database_null();

	/*提取conditions*/
	bool get_conditions_by_str(const string &condition_str, SingleList<string> &column_names, SingleList<Condition*> &all_conditions);
}

using namespace DestinyDB;
using namespace Error;
using namespace DatabaseFile;

#endif