/*******************************************************
 *	database_file.h
 *	author:��������
 *	copyright(c) 2015 - ~: ���Ķ� LICENSE �ļ�
 *	Description(����):���ݿ��ļ�����
 ******************************************************/
#pragma once
#ifndef DATABASE_FILE_H
#define DATABASE_FILE_H

#include "destiny.h"

/*���ݿ��ļ�����*/
namespace DatabaseFile {

	/*���keyword�Ƿ��ڳ�ʼ�ؼ����б�*/
	bool check_init_keyword(const string &keyword);

	/*�������ݿ��ļ�*/
	inline void create_file(const string &file_path);

	/*��ȡ���ݿ��ļ�*/
	static void read_database_file(const string &file_path);

	/*�����ݿ��ļ�*/
	inline void open_file(const string &file_path);
}

using namespace DestinyDB;

/*���keyword�Ƿ��ڳ�ʼ�ؼ����б�*/
bool DatabaseFile::check_init_keyword(const string &keyword) {
	for (int i = 0; i < init_keywords_num; i++) {
		if (keyword == init_keywords[i]) {
			return true;
		}
	}
	return false;
}

/*�������ݿ��ļ�*/
void DatabaseFile::create_file(const string &file_path) {
	ofstream ofs(file_path, ios::out);
	ofs.close();
}

/*��ȡ���ݿ��ļ�*/
static void DatabaseFile::read_database_file(const string &file_path) {
	if (database&&database->database_file == file_path&&database->fresh_bit) {
		return;
	}
	database = DestinyDatabase::deserialize(file_path);
}

/*�����ݿ��ļ�*/
void DatabaseFile::open_file(const string &file_path) {
	cout << "ʹ�����ݿ��ļ�:" << file_path << endl;
	try {
		read_database_file(file_path);
	}
	catch (string error_string) {
		print_error(error_database_file_crash, file_path);
		database = new DestinyDatabase(file_path);
	}
}
#endif