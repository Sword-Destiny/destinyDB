/*******************************************************
 *	destiny.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: 请阅读 LICENSE 文件
 *	Description(描述):主命名空间,关键字定义
 ******************************************************/
#pragma once
#ifndef DESTINY_DB_H
#define DESTINY_DB_H

#include "database.h"

/*DestinyDB全局命名空间*/
namespace DestinyDB {
	static const string keyword_exit = "exit";//退出
	static const string keyword_open = "open";//打开
	static const string keyword_help = "help";//帮助
	static const string keyword_version = "version";//版本信息
	static const string keyword_seperator = ";";//分隔符
	static const string keyword_commit = "commit";//提交
	static const string keyword_run = "run";//运行destinyDB脚本文件
	static const string keyword_insert = "insert";//插入语句
	static const string keyword_create = "create";//建表语句
	static const string keyword_rename = "rename";//重命名语句
	static const string keyword_show = "show";//显示语句
	static const string keyword_auto_commit = "autocommit";//自动提交更新
	static const string keyword_select = "select";//查询
	static const string keyword_from = "from";//关键字from
	static const string keyword_into = "into";//关键字into
	static const string keyword_table = "table";//表
	static const string keyword_where = "where";//查询条件
	static const string keyword_update = "update";//更新数据
	static const string keyword_set = "set";//关键字set
	static const string keyword_delete = "delete";//删除数据
	static const string keyword_drop = "drop";//删除表
	static const string keyword_sort = "sort";//排序表

	/*是否自动提交*/
	bool auto_commit = true;
	/*默认数据库文件扩展名*/
	//static const string default_file_ext = "*.ddb";
	/*数据库*/
	DestinyDatabase * database = NULL;

	/*所有关键字列表*/
	static const string full_keywords[] = {
		keyword_exit,
		keyword_open,
		keyword_help,
		keyword_version,
		keyword_seperator,
		keyword_commit,
		keyword_run,
		keyword_insert,
		keyword_create,
		keyword_rename,
		keyword_show,
		keyword_auto_commit,
		keyword_select,
		keyword_from,
		keyword_into,
		keyword_table,
		keyword_where,
		keyword_update,
		keyword_set,
		keyword_delete,
		keyword_drop,
		keyword_sort
	};

	/*所有关键字总数*/
	static const int full_keywords_num = sizeof(full_keywords) / sizeof(string);

	/*初始关键字列表*/
	static const string init_keywords[] = {
		keyword_exit,
		keyword_help,
		keyword_open,
		keyword_version,
		keyword_run,
		keyword_seperator,
		keyword_auto_commit
	};

	/*初始关键字数量*/
	static const int init_keywords_num = sizeof(init_keywords) / sizeof(string);

	/*检查文件是否存在*/
	bool is_file_exists(const string &file_path);

	/*检查keyword是否在所有关键字列表*/
	bool check_full_keyword(const string &keyword);

	/*打印命令行行首*/
	inline void print_line_head();

	/*打印命令行行首提示信息*/
	inline void print_destiny_line_head();

	/*打印版本信息*/
	inline void print_version();

	/*打印帮助信息*/
	inline void print_help_line();

	/*打印退出信息*/
	inline void print_exit();

	/*打印欢迎信息*/
	inline void print_welcome();

	/*打印Usage：使用说明*/
	inline void print_usage();

	/*打印帮助信息*/
	inline void print_help_information();

}

/*检查文件是否存在*/
bool DestinyDB::is_file_exists(const string &file_path) {
	ifstream ifs(file_path, ios::in);
	if (ifs) {
		ifs.close();
		return true;
	}
	else {
		ifs.close();
		return false;
	}
}

/*检查keyword是否在所有关键字列表*/
bool DestinyDB::check_full_keyword(const string &keyword) {
	for (int i = 0; i < full_keywords_num; i++) {
		if (keyword == full_keywords[i]) {
			return true;
		}
	}
	return false;
}

/*打印命令行行首*/
void DestinyDB::print_line_head() {
	cout << ">";
}

/*打印命令行行首提示信息*/
void DestinyDB::print_destiny_line_head() {
	if (database != NULL) {
		cout << "DestinyDB:" << database->database_file << ">";
	}
	else {
		cout << "DestinyDB>";
	}
}

/*打印版本信息*/
void DestinyDB::print_version() {
	cout << "DB-version 0.1" << endl;
}

/*打印帮助信息*/
void DestinyDB::print_help_line() {
	cout << "   输入help获得所有命令和关键字的信息." << endl;
}

/*打印退出信息*/
void DestinyDB::print_exit() {
	cout << "bye!" << endl;
}

/*打印欢迎信息*/
void DestinyDB::print_welcome() {
	print_version();
	print_help_line();
}

/*打印Usage：使用说明*/
void DestinyDB::print_usage() {
	cout << "Usage: destinyDB				启动程序" << endl;
	cout << "   or: destinyDB <ddb_file>		打开或创建一个数据库文件" << endl;
	cout << "   or: destinyDB open <ddb_file>	打开或创建一个数据库文件" << endl;
	print_help_line();
}

/*打印帮助信息*/
void DestinyDB::print_help_information() {
	cout << "destinyDB命令:" << endl;
	cout << "        help: 打印帮助信息." << endl;
	cout << "            : 示例: help" << endl;
	cout << endl;
	cout << "        exit: 退出destinyDB." << endl;
	cout << "            : 示例: exit" << endl;
	cout << endl;
	cout << "     version: 打印版本信息." << endl;
	cout << "            : 示例: version" << endl;
	cout << endl;
	cout << "        open: 打开或创建数据库文件." << endl;
	cout << "            : 示例: open main.ddb" << endl;
	cout << endl;
	cout << "         run: 运行destinyDB脚本文件." << endl;
	cout << "            : 示例: run main.ddbsql" << endl;
	cout << endl;
	cout << "           ;: 分号." << endl;
	cout << "            : 示例: ;" << endl;
	cout << endl;
	cout << "      commit: 提交更改." << endl;
	cout << "            : 示例: commit" << endl;
	cout << endl;
	cout << "      create: 创建表." << endl;
	cout << "            : 示例: create table student id,name" << endl;
	cout << endl;
	cout << "      insert: 插入数据到表中(可以在一条命令中插入多条数据)." << endl;
	cout << "            : 示例: insert into tbl_student 1,Lili 2,Tom ..." << endl;
	cout << endl;
	cout << "      rename: 重命名表名称或者列名称." << endl;
	cout << "            : 示例1:重命名表student为tbl_student" << endl;
	cout << "                  : rename table student tbl_student" << endl;
	cout << "            : 示例2:重命名表tbl_student中的id列为stu_id" << endl;
	cout << "                  : rename column id in tbl_student std_id" << endl;
	cout << endl;
	cout << "        show: 显示一些变量." << endl;
	cout << "            : 示例1: show tables" << endl;
	cout << "            : 示例2: show database_file" << endl;
	cout << endl;
	cout << "  autocommit: 更改auto_commit属性.yes/y/true/t代表自动提交,no/n/false/f代表不自动提交(忽略大小写)." << endl;
	cout << "            : 示例: autocommit true" << endl;
	cout << endl;
	cout << "      select: 查询语句(支持列名正则表达式匹配,可嵌套查询)." << endl;
	cout << "            : 示例1: select id,name where id=1||name=Tom from tbl_student" << endl;
	cout << "            : 示例2: select id where name=Tom from select id,name where id>0 from tbl_student" << endl;
	cout << endl;
	cout << "      delete: 删除数据." << endl;
	cout << "            : 示例: delete from tbl_student where id=1" << endl;
	cout << endl;
	cout << "        drop: 删除表." << endl;
	cout << "            : 示例: drop table tbl_student" << endl;
	cout << endl;
	cout << "        sort: 排序数据(排序结果中文在前,其次数字,最后英文)." << endl;
	cout << "            : 示例: sort tbl_student by id" << endl;
	cout << endl;
}
#endif