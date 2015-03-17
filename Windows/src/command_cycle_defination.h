/*******************************************************
 *	command_cycle_defination.h
 *	author:��������
 *	copyright(c) 2015 - ~: ���Ķ� LICENSE �ļ�
 *	Description(����):����ѭ������ͷ�ļ�
 ******************************************************/
#pragma once
#ifndef COMMAND_CYCLE_DEFINATION
#define COMMAND_CYCLE_DEFINATION
#include "destiny.h"
#include "error.h"
#include "database_file.h"

/*����ѭ��*/
namespace CommandCycle {

	string command = "";//����������
	string single_command = "";
	bool end_of_last_command = true;//��һ�������Ƿ�ִ�����,����һ�������Ƿ�����
	bool enable_last_command = true;//�Ƿ�����������������
	
	/*version����*/
	void command_do_version(sregex_token_iterator &it);

	/*help����*/
	void command_do_help(sregex_token_iterator &it);

	/*exit����*/
	void command_do_exit(sregex_token_iterator &it);

	/*open����*/
	void command_do_open(sregex_token_iterator &it);

	/*commit����*/
	void command_do_commit(sregex_token_iterator &it);

	/*run����*/
	void command_do_run(sregex_token_iterator &it);

	/*insert����*/
	void command_do_insert(sregex_token_iterator &it);

	/*create����*/
	void command_do_create(sregex_token_iterator &it);

	/*show����*/
	void command_do_show(sregex_token_iterator &it);

	/*select����*/
	void command_do_select(sregex_token_iterator &it);

	/*update����*/
	void command_do_update(sregex_token_iterator &it);

	/*update����*/
	void command_do_delete(sregex_token_iterator &it);

	/*rename����*/
	void command_do_rename(sregex_token_iterator &it);

	/*autocommit����*/
	void command_do_auto_commit(sregex_token_iterator &it);

	/*drop����*/
	void command_do_drop(sregex_token_iterator &it);

	/*sort����*/
	void command_do_sort(sregex_token_iterator &it);

	/*��������ѭ��*/
	void command_single_cycle(const string &single_command_str);

	/*����ѭ��������*/
	void command_cycle(istream &ist, bool child_cycle = false);

	/*��ѯ*/
	bool query(sregex_token_iterator &it, ResultSet *&current_result_set);

	/*��ӡ����������Ϣ*/
	inline void lose_argument_error(string error_information = "", string error_argument = "");

	template<class T>
	/*�ͷ�����ռ�*/
	void list_free(SingleList<T*> &list);

	/*�����ύ����*/
	void warning_commit();

	/*�����ύ����*/
	bool check_database_null();

	/*��ȡconditions*/
	bool get_conditions_by_str(const string &condition_str, SingleList<string> &column_names, SingleList<Condition*> &all_conditions);
}

using namespace DestinyDB;
using namespace Error;
using namespace DatabaseFile;

#endif