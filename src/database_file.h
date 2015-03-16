/*******************************************************
 *	database_file.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: 请阅读 LICENSE 文件
 *	Description(描述):数据库文件操作
 ******************************************************/
#pragma once
#ifndef DATABASE_FILE_H
#define DATABASE_FILE_H

#include "destiny.h"

/*数据库文件操作*/
namespace DatabaseFile {

	/*检查keyword是否在初始关键字列表*/
	bool check_init_keyword(const string &keyword);

	/*创建数据库文件*/
	inline void create_file(const string &file_path);

	/*读取数据库文件*/
	static void read_database_file(const string &file_path);

	/*打开数据库文件*/
	inline void open_file(const string &file_path);
}

using namespace DestinyDB;

/*检查keyword是否在初始关键字列表*/
bool DatabaseFile::check_init_keyword(const string &keyword) {
	for (int i = 0; i < init_keywords_num; i++) {
		if (keyword == init_keywords[i]) {
			return true;
		}
	}
	return false;
}

/*创建数据库文件*/
void DatabaseFile::create_file(const string &file_path) {
	ofstream ofs(file_path, ios::out);
	ofs.close();
}

/*读取数据库文件*/
static void DatabaseFile::read_database_file(const string &file_path) {
	if (database&&database->database_file == file_path&&database->fresh_bit) {
		return;
	}
	database = DestinyDatabase::deserialize(file_path);
}

/*打开数据库文件*/
void DatabaseFile::open_file(const string &file_path) {
	cout << "使用数据库文件:" << file_path << endl;
	try {
		read_database_file(file_path);
	}
	catch (string error_string) {
		print_error(error_database_file_crash, file_path);
		database = new DestinyDatabase(file_path);
	}
}
#endif