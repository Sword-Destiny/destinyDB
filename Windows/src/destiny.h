/*******************************************************
 *	destiny.h
 *	author:��������
 *	copyright(c) 2015 - ~: ���Ķ� LICENSE �ļ�
 *	Description(����):�������ռ�,�ؼ��ֶ���
 ******************************************************/
#pragma once
#ifndef DESTINY_DB_H
#define DESTINY_DB_H

#include "database.h"

/*DestinyDBȫ�������ռ�*/
namespace DestinyDB {
	static const string keyword_exit = "exit";//�˳�
	static const string keyword_open = "open";//��
	static const string keyword_help = "help";//����
	static const string keyword_version = "version";//�汾��Ϣ
	static const string keyword_seperator = ";";//�ָ���
	static const string keyword_commit = "commit";//�ύ
	static const string keyword_run = "run";//����destinyDB�ű��ļ�
	static const string keyword_insert = "insert";//�������
	static const string keyword_create = "create";//�������
	static const string keyword_rename = "rename";//���������
	static const string keyword_show = "show";//��ʾ���
	static const string keyword_auto_commit = "autocommit";//�Զ��ύ����
	static const string keyword_select = "select";//��ѯ
	static const string keyword_from = "from";//�ؼ���from
	static const string keyword_into = "into";//�ؼ���into
	static const string keyword_table = "table";//��
	static const string keyword_where = "where";//��ѯ����
	static const string keyword_update = "update";//��������
	static const string keyword_set = "set";//�ؼ���set
	static const string keyword_delete = "delete";//ɾ������
	static const string keyword_drop = "drop";//ɾ����
	static const string keyword_sort = "sort";//�����

	/*�Ƿ��Զ��ύ*/
	bool auto_commit = true;
	/*Ĭ�����ݿ��ļ���չ��*/
	//static const string default_file_ext = "*.ddb";
	/*���ݿ�*/
	DestinyDatabase * database = NULL;

	/*���йؼ����б�*/
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

	/*���йؼ�������*/
	static const int full_keywords_num = sizeof(full_keywords) / sizeof(string);

	/*��ʼ�ؼ����б�*/
	static const string init_keywords[] = {
		keyword_exit,
		keyword_help,
		keyword_open,
		keyword_version,
		keyword_run,
		keyword_seperator,
		keyword_auto_commit
	};

	/*��ʼ�ؼ�������*/
	static const int init_keywords_num = sizeof(init_keywords) / sizeof(string);

	/*����ļ��Ƿ����*/
	bool is_file_exists(const string &file_path);

	/*���keyword�Ƿ������йؼ����б�*/
	bool check_full_keyword(const string &keyword);

	/*��ӡ����������*/
	inline void print_line_head();

	/*��ӡ������������ʾ��Ϣ*/
	inline void print_destiny_line_head();

	/*��ӡ�汾��Ϣ*/
	inline void print_version();

	/*��ӡ������Ϣ*/
	inline void print_help_line();

	/*��ӡ�˳���Ϣ*/
	inline void print_exit();

	/*��ӡ��ӭ��Ϣ*/
	inline void print_welcome();

	/*��ӡUsage��ʹ��˵��*/
	inline void print_usage();

	/*��ӡ������Ϣ*/
	inline void print_help_information();

}

/*����ļ��Ƿ����*/
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

/*���keyword�Ƿ������йؼ����б�*/
bool DestinyDB::check_full_keyword(const string &keyword) {
	for (int i = 0; i < full_keywords_num; i++) {
		if (keyword == full_keywords[i]) {
			return true;
		}
	}
	return false;
}

/*��ӡ����������*/
void DestinyDB::print_line_head() {
	cout << ">";
}

/*��ӡ������������ʾ��Ϣ*/
void DestinyDB::print_destiny_line_head() {
	if (database != NULL) {
		cout << "DestinyDB:" << database->database_file << ">";
	}
	else {
		cout << "DestinyDB>";
	}
}

/*��ӡ�汾��Ϣ*/
void DestinyDB::print_version() {
	cout << "DB-version 0.1" << endl;
}

/*��ӡ������Ϣ*/
void DestinyDB::print_help_line() {
	cout << "   ����help�����������͹ؼ��ֵ���Ϣ." << endl;
}

/*��ӡ�˳���Ϣ*/
void DestinyDB::print_exit() {
	cout << "bye!" << endl;
}

/*��ӡ��ӭ��Ϣ*/
void DestinyDB::print_welcome() {
	print_version();
	print_help_line();
}

/*��ӡUsage��ʹ��˵��*/
void DestinyDB::print_usage() {
	cout << "Usage: destinyDB				��������" << endl;
	cout << "   or: destinyDB <ddb_file>		�򿪻򴴽�һ�����ݿ��ļ�" << endl;
	cout << "   or: destinyDB open <ddb_file>	�򿪻򴴽�һ�����ݿ��ļ�" << endl;
	print_help_line();
}

/*��ӡ������Ϣ*/
void DestinyDB::print_help_information() {
	cout << "destinyDB����:" << endl;
	cout << "        help: ��ӡ������Ϣ." << endl;
	cout << "            : ʾ��: help" << endl;
	cout << endl;
	cout << "        exit: �˳�destinyDB." << endl;
	cout << "            : ʾ��: exit" << endl;
	cout << endl;
	cout << "     version: ��ӡ�汾��Ϣ." << endl;
	cout << "            : ʾ��: version" << endl;
	cout << endl;
	cout << "        open: �򿪻򴴽����ݿ��ļ�." << endl;
	cout << "            : ʾ��: open main.ddb" << endl;
	cout << endl;
	cout << "         run: ����destinyDB�ű��ļ�." << endl;
	cout << "            : ʾ��: run main.ddbsql" << endl;
	cout << endl;
	cout << "           ;: �ֺ�." << endl;
	cout << "            : ʾ��: ;" << endl;
	cout << endl;
	cout << "      commit: �ύ����." << endl;
	cout << "            : ʾ��: commit" << endl;
	cout << endl;
	cout << "      create: ������." << endl;
	cout << "            : ʾ��: create table student id,name" << endl;
	cout << endl;
	cout << "      insert: �������ݵ�����(������һ�������в����������)." << endl;
	cout << "            : ʾ��: insert into tbl_student 1,Lili 2,Tom ..." << endl;
	cout << endl;
	cout << "      rename: �����������ƻ���������." << endl;
	cout << "            : ʾ��1:��������studentΪtbl_student" << endl;
	cout << "                  : rename table student tbl_student" << endl;
	cout << "            : ʾ��2:��������tbl_student�е�id��Ϊstu_id" << endl;
	cout << "                  : rename column id in tbl_student std_id" << endl;
	cout << endl;
	cout << "        show: ��ʾһЩ����." << endl;
	cout << "            : ʾ��1: show tables" << endl;
	cout << "            : ʾ��2: show database_file" << endl;
	cout << endl;
	cout << "  autocommit: ����auto_commit����.yes/y/true/t�����Զ��ύ,no/n/false/f�����Զ��ύ(���Դ�Сд)." << endl;
	cout << "            : ʾ��: autocommit true" << endl;
	cout << endl;
	cout << "      select: ��ѯ���(֧������������ʽƥ��,��Ƕ�ײ�ѯ)." << endl;
	cout << "            : ʾ��1: select id,name where id=1||name=Tom from tbl_student" << endl;
	cout << "            : ʾ��2: select id where name=Tom from select id,name where id>0 from tbl_student" << endl;
	cout << endl;
	cout << "      delete: ɾ������." << endl;
	cout << "            : ʾ��: delete from tbl_student where id=1" << endl;
	cout << endl;
	cout << "        drop: ɾ����." << endl;
	cout << "            : ʾ��: drop table tbl_student" << endl;
	cout << endl;
	cout << "        sort: ��������(������������ǰ,�������,���Ӣ��)." << endl;
	cout << "            : ʾ��: sort tbl_student by id" << endl;
	cout << endl;
}
#endif