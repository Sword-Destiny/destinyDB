/*******************************************************
 *	command_cycle.h
 *	author:��������
 *	copyright(c) 2015 - ~: ���Ķ� LICENSE �ļ�
 *	Description(����):����ѭ��
 ******************************************************/
#pragma once
#ifndef COMMAND_CYCLE_H
#define COMMAND_CYCLE_H

#include "destiny.h"
#include "error.h"
#include "database_file.h"
#include "query.h"

//NOTICE:ת���ַ�����

 /*�����ύ����*/
void CommandCycle::warning_commit() {
	if (database&&!database->fresh_bit) {
		if (auto_commit) {
			database->commit();
		}
		else {
			cout << "��δ�ύ�ĸ���,�Ƿ��ύ����?(y/n)";
			string user_answer = "";
			getline(cin, user_answer);
			if (user_answer == "" || regex_match(user_answer, regex_empty) || regex_match(user_answer, regex_empty_yes)) {
				database->commit();
				cout << "���ύ����!" << endl;
			}
			else {
				cout << "�ѷ����ύ����!" << endl;
			}
		}
	}
}

/*�����ύ����*/
bool CommandCycle::check_database_null() {
	if (database == NULL) {
		print_error(error_no_database_file);
		end_of_last_command = true;
		return true;
	}
	return false;
}

/*��ȡconditions*/
bool CommandCycle::get_conditions_by_str(const string &condition_str, SingleList<string> &column_names, SingleList<Condition*> &all_conditions) {
	sregex_token_iterator condition_it(condition_str.begin(), condition_str.end(), regex_or, -1);
	while (condition_it != end) {
		string condition_group = *condition_it;
		condition_it++;
		if (condition_group == "") {
			continue;
		}
		SingleList<SingleCondition> conditions;
		sregex_token_iterator single_condition_it(condition_group.begin(), condition_group.end(), regex_and, -1);
		while (single_condition_it != end) {
			string single_condition_str = *single_condition_it;
			single_condition_it++;
			if (single_condition_str == "") {
				continue;
			}
			bool reverse = false;
			if (single_condition_str[0] == '!') {
				single_condition_str = single_condition_str.substr(1, single_condition_str.length() - 1);
				reverse = true;
			}
			SingleCondition *single_condition = NULL;
			string result_id = SingleCondition::get_single_condition(single_condition_str, column_names, single_condition);
			if (single_condition != NULL) {
				if (reverse) {
					single_condition->reverse();
				}
				conditions.add_tail(*single_condition);
				delete single_condition;
				continue;
			}
			if (result_id == "") {
				print_error(error_logic_expression, single_condition_str);
				end_of_last_command = true;
				list_free(all_conditions);
				return false;
			}
			else {
				print_error(error_column_not_found, result_id);
				end_of_last_command = true;
				list_free(all_conditions);
				return false;
			}
		}
		Condition *con = new Condition(conditions);
		all_conditions.add_tail(con);
	}
	return true;
}

template<class T>
/*�ͷ�����ռ�*/
void CommandCycle::list_free(SingleList<T*> &list) {
	SingleNode<T*> *p = list.head_node;
	while (p != NULL) {
		delete p->element;
		p = p->next;
	}
}

/*��ӡ����������Ϣ*/
void CommandCycle::lose_argument_error(string error_information, string error_argument) {
	if (enable_last_command) {
		end_of_last_command = false;
	}
	else {
		print_error(error_lose_arguments, error_information, error_argument);
		end_of_last_command = true;
		enable_last_command = true;
	}
}

/*version����*/
void CommandCycle::command_do_version(sregex_token_iterator &it) {
	if (it == end) {
		print_version();
	}
	else {
		print_error(Error::error_too_much_arguments, "version����Ҫ����!");
	}
	end_of_last_command = true;
}

/*help����*/
void CommandCycle::command_do_help(sregex_token_iterator &it) {
	if (it == end) {
		print_help_information();
	}
	else {
		print_error(error_too_much_arguments, "help����Ҫ����!");
	}
	end_of_last_command = true;
}

/*exit����*/
void CommandCycle::command_do_exit(sregex_token_iterator &it) {
	if (it == end) {
		warning_commit();
		print_exit();
		exit(0);
	}
	else {
		print_error(error_too_much_arguments, "exit����Ҫ����!");
		end_of_last_command = true;
	}
}

/*open����*/
void CommandCycle::command_do_open(sregex_token_iterator &it) {
	string file_path;
	if (it == end) {
		lose_argument_error("open֮����Ҫһ�������ļ��Ĳ���!");
		return;
	}
	file_path = *it;
	it++;
	if (it == end) {
		warning_commit();
		if (is_file_exists(file_path)) {
			open_file(file_path);
		}
		else {
			print_error(warning_no_such_file, "�Ѵ��������ݿ��ļ�:", file_path);
			create_file(file_path);
			open_file(file_path);
		}
	}
	else {
		print_error(error_too_much_arguments, "openֻ��Ҫһ������!");
	}
	end_of_last_command = true;
}

/*show����*/
void CommandCycle::command_do_show(sregex_token_iterator &it) {
	if (check_database_null()) {
		return;
	}
	if (it == end) {
		lose_argument_error("show֮����Ҫһ����������Ĳ���!");
		return;
	}
	string str = *it;
	it++;
	if (it == end) {
		if (str == "tables") {
			if (database->tables.length < 1) {
				cout << "���ݿ��ǿյ�,û�б�!" << endl;
				return;
			}
			SingleNode<DestinyTable*> *p = database->tables.head_node;
			while (p != NULL) {
				cout << "table: " << p->element->name << endl;
				SingleNode<string> *q = p->element->column_names.head_node;
				cout << "    ";
				while (q != NULL) {
					cout << q->element << "  ";
					q = q->next;
				}
				cout << endl;
				p = p->next;
			}
		}
		else if (str == "database_file") {
			cout << database->database_file << endl;
		}
		else {
			print_error(error_unknown_command, str);
		}
	}
	else {
		print_error(error_too_much_arguments, "showֻ��Ҫһ������!");
	}
	end_of_last_command = true;
}

/*drop����*/
void CommandCycle::command_do_drop(sregex_token_iterator &it) {
	if (check_database_null()) {
		return;
	}
	if (it == end) {
		lose_argument_error("drop֮����Ҫtable!");
		return;
	}
	string table_str = *it;
	it++;
	if (table_str != keyword_table) {
		print_error(error_unknown_command, table_str, "�˴���Ҫtable!");
		end_of_last_command = true;
		return;
	}
	if (it == end) {
		lose_argument_error(keyword_table, "֮����Ҫһ����������Ĳ���!");
		return;
	}
	string table_name = *it;
	it++;
	if (it != end) {
		print_error(error_too_much_arguments, "dropֻ��Ҫ��������!");
		end_of_last_command = true;
		return;
	}
	DestinyTable* p_table = NULL;
	if (!database->contains_table(table_name, p_table)) {
		print_error(error_table_not_exists, table_name);
		end_of_last_command = true;
		return;
	}
	if (database->drop_table(p_table)) {
		cout << "ɾ����" << table_name << "�ɹ�!" << endl;
		database->fresh_bit = false;
	}
	else {
		print_error(error_unknown, "ɾ����ʧ��!");
	}
	end_of_last_command = true;
	return;
}

/*drop����*/
void CommandCycle::command_do_sort(sregex_token_iterator &it) {
	if (check_database_null()) {
		return;
	}
	if (it == end) {
		lose_argument_error("sort֮����Ҫһ����������Ĳ���!");
		return;
	}
	string table_name = *it;
	it++;
	DestinyTable* p_table = NULL;
	if (!database->contains_table(table_name, p_table)) {
		print_error(error_table_not_exists, table_name);
		end_of_last_command = true;
		return;
	}
	if (it == end) {
		lose_argument_error(table_name, "֮����Ҫby!");
		return;
	}
	string by_str = *it;
	it++;
	if (by_str != "by") {
		print_error(error_unknown_command, by_str, "�˴���Ҫby!");
		end_of_last_command = true;
		return;
	}
	if (it == end) {
		lose_argument_error(keyword_table, "by֮����Ҫһ�����������Ĳ���!");
		return;
	}
	string column_name = *it;
	it++;
	if (it != end) {
		print_error(error_too_much_arguments, "sortֻ��Ҫ��������!");
		end_of_last_command = true;
		return;
	}
	if (p_table->column_names.index_of(column_name) == -1) {
		print_error(error_column_not_found, column_name);
		end_of_last_command = true;
		return;
	}
	p_table->sort_by(column_name);
	cout << "�������!" << endl;
	database->fresh_bit = false;
	end_of_last_command = true;
	return;
}

/*autocommit����*/
void CommandCycle::command_do_auto_commit(sregex_token_iterator &it) {
	if (it == end) {
		lose_argument_error(keyword_auto_commit, "֮����Ҫyes/y/true/t����no/n/false/f!");
		return;
	}
	string str = *it;
	it++;
	if (it == end) {
		if (regex_match(str, regex_yes)) {
			auto_commit = true;
		}
		else if (regex_match(str, regex_no)) {
			auto_commit = false;
		}
		else {
			print_error(error_unknown_command, str, "�˴���Ҫyes/y/true/t����no/n/false/f!");
		}
	}
	else {
		print_error(error_too_much_arguments, "autocommitֻ��Ҫһ������!");
	}
	end_of_last_command = true;
}

/*commit����*/
void CommandCycle::command_do_commit(sregex_token_iterator &it) {
	if (check_database_null()) {
		return;
	}
	if (it == end) {
		database->commit();
		cout << "�ύ���ĳɹ�!" << endl;
	}
	else {
		print_error(error_too_much_arguments, "commit����Ҫ����!");
	}
	end_of_last_command = true;
}

/*run����*/
void CommandCycle::command_do_run(sregex_token_iterator &it) {
	if (it != end) {
		string file_path = *it;
		it++;
		if (it == end) {
			if (is_file_exists(file_path)) {
				ifstream ifs(file_path, ios::in);
				command_cycle(ifs, true);
				ifs.close();
			}
			else {
				print_error(warning_no_such_file, file_path, ":����ִ���κβ���!");
			}
		}
		else {
			print_error(error_too_much_arguments, "runֻ��Ҫһ������!");
		}
		end_of_last_command = true;
		return;
	}
	lose_argument_error("run֮����Ҫһ������destinyDB�ű��Ĳ���!");
}

/*insert����*/
void CommandCycle::command_do_insert(sregex_token_iterator &it) {
	if (check_database_null()) {
		return;
	}
	if (it != end) {
		string str = *it;
		it++;
		if (str == keyword_into) {
			if (it != end) {
				str = *it;
				it++;
				DestinyTable* p_table = NULL;
				if (database->contains_table(str, p_table)) {
					if (it == end) {
						lose_argument_error(p_table->name, "��ȱ����Ҫ������е�����!");
					}
					else {
						int insert_num = 0;
						while (it != end) {
							string obj_str = *it;
							it++;
							sregex_token_iterator column_it(obj_str.begin(), obj_str.end(), regex_comma, -1);
							SingleList<string> datas;
							while (column_it != end) {
								datas.add_tail(*column_it); 
								column_it++;
							}
							if (datas.length != p_table->column_names.length) {
								print_error(error_column_num_not_match, "�����ݶ����ֶ�̫���̫��,���ܲ������:", obj_str);
								continue;
							}
							DestinyObject obj(datas);
							if (p_table->insert_object(obj)) {
								insert_num++;
							}
							else {
								print_error(error_row_overflow, MAX_LINE_NUM_STR);
								break;
							}
						}
						cout << "�������ݹ�" << insert_num << "��!" << endl;
						database->fresh_bit = false;
						end_of_last_command = true;
					}
				}
				else {
					print_error(error_table_not_exists, str);
					end_of_last_command = true;
				}
			}
			else {
				lose_argument_error("insert֮����Ҫ��������Ĳ���!");
			}
		}
		else {
			print_error(error_unknown_command, str);
			end_of_last_command = true;
		}
	}
	else {
		lose_argument_error("insert֮����Ҫ����into!");
	}
}

/*create����*/
void CommandCycle::command_do_create(sregex_token_iterator &it) {
	if (check_database_null()) {
		return;
	}
	if (it != end) {
		string str = *it;
		it++;
		if (str == keyword_table) {
			if (it != end) {
				str = *it;
				it++;
				string table_name = str;
				if (check_full_keyword(str)) {
					print_error(error_keyword, str, "������Ϊ����!");
					end_of_last_command = true;
					return;
				}
				if (it != end) {
					DestinyTable* p_table = NULL;
					if (database->contains_table(str, p_table)) {
						print_error(error_table_exists, str, ":�����ظ�����!");
					}
					else {
						str = *it;
						it++;
						if (it == end) {
							SingleList<string> columns;
							sregex_token_iterator it_column(str.begin(), str.end(), regex_comma, -1);
							while (it_column != end) {
								string str_column = *it_column;
								it_column++;
								if (check_full_keyword(str)) {
									print_error(error_keyword, str, "������Ϊ����!");
									end_of_last_command = true;
									return;
								}
								if (columns.index_of(str_column) != -1) {
									print_error(error_column_repeat, str_column, ":����ʧ��!");
									end_of_last_command = true;
									return;
								}
								columns.add_tail(str_column);
							}
							p_table = new DestinyTable(table_name, columns);
							if (database->add_table(p_table)) {
								cout << "����ɹ�!" << endl;
								database->fresh_bit = false;
							}
							else {
								print_error(error_table_num_overflow, MAX_TABLE_NUM_STR);
							}
						}
						else {
							print_error(error_too_much_arguments, "createֻ��Ҫ��������!");
						}
					}
					end_of_last_command = true;
				}
				else {
					lose_argument_error(table_name, "֮����Ҫ���������Ȳ���!");
				}
			}
			else {
				lose_argument_error("table֮��ȱ�ٱ����Ȳ���!");
			}
		}
		else {
			print_error(error_unknown_command, str, ":�˴��Ƿ�Ӧ��Ϊtable?");
			end_of_last_command = true;
		}
	}
	else {
		lose_argument_error("create����Ҫ����table�Ȳ���!");
	}
}

/*select����*/
void CommandCycle::command_do_select(sregex_token_iterator &it) {
	if (check_database_null()) {
		return;
	}
	ResultSet* result = NULL;
	if (query(it, result)) {
		if (result->objects.length > 0) {
			SingleNode<string> *p = result->column_names.head_node;
			cout << "| ";
			while (p != NULL) {
				cout << setw(8) << p->element << " | ";
				p = p->next;
			}
			cout << endl << endl;
			SingleNode<DestinyObject> *q = result->objects.head_node;
			while (q != NULL) {
				cout << "| ";
				for (int i = 0; i < q->element.datas.length; i++) {
					cout << setw(8) << q->element.datas[i] << " | ";
				}
				cout << endl;
				q = q->next;
			}
		}
		else {
			cout << "��ѯ���Ϊ��!" << endl;
		}
		delete result;
	}
	else {
		return;
	}
}

/*���²���*/
void CommandCycle::command_do_update(sregex_token_iterator &it) {
	if (check_database_null()) {
		return;
	}
	if (it == end) {
		lose_argument_error("update֮����Ҫһ����������Ĳ���!");
		return;
	}
	string table_name = *it;
	it++;
	DestinyTable* p_table = NULL;
	if (!database->contains_table(table_name, p_table)) {
		print_error(error_table_not_exists, table_name);
		end_of_last_command = true;
		return;
	}
	if (it == end) {
		lose_argument_error(table_name, "����Ҫ����where����set!");
		return;
	}

	string where_str = *it;
	it++;
	bool has_where = false;
	if (where_str != keyword_where) {
		if (where_str != keyword_set) {
			print_error(error_unknown_command, where_str, ":�˴��Ƿ�Ӧ����where�ؼ���?");
			end_of_last_command = true;
			return;
		}
		else {
			has_where = false;
		}
	}
	else {
		has_where = true;
	}
	string condition_str;
	if (has_where) {
		if (it == end) {
			lose_argument_error("where֮����Ҫ������������!");
			return;
		}

		condition_str = *it;
		it++;
		if (it == end) {
			lose_argument_error("ȱ��set!");
			return;
		}

		string set = *it;
		it++;
		if (set != keyword_set) {
			if (condition_str == keyword_set) {
				print_error(error_lose_arguments, "where֮����Ҫ����!");
				end_of_last_command = true;
				return;
			}
			else {
				print_error(error_unknown_command, set, "�˴��Ƿ�Ӧ����set!");
				end_of_last_command = true;
				return;
			}
			print_error(error_unknown_command, set);
			end_of_last_command = true;
			return;
		}
	}
	else {
		condition_str = "";
	}

	SingleList<Condition*> all_conditions;
	if (!get_conditions_by_str(condition_str, p_table->column_names, all_conditions)) {
		return;
	}

	if (it == end) {
		lose_argument_error("set֮����Ҫ���������еȲ���!");
		list_free(all_conditions);
		return;
	}

	string update_columns_str = *it;
	it++;
	SingleList<UpdatePair> update_fields;

	sregex_token_iterator update_it(update_columns_str.begin(), update_columns_str.end(), regex_comma, -1);
	while (update_it != end) {
		string update_pair_str = *update_it;
		update_it++;
		sregex_token_iterator update_pair_it(update_pair_str.begin(), update_pair_str.end(), regex_equal, -1);
		if (update_pair_it == end) {
			continue;
		}
		string update_column_name = *update_pair_it;
		update_pair_it++;
		int index = p_table->column_names.index_of(update_column_name);
		if (index == -1) {
			print_error(error_column_not_found, update_column_name);
			end_of_last_command = true;
			list_free(all_conditions);
			return;
		}
		if (update_pair_it == end) {
			print_error(error_expression, update_pair_str);
			list_free(all_conditions);
			return;
		}
		string new_value = *update_pair_it;
		update_pair_it++;
		if (update_pair_it != end) {
			print_error(error_expression, update_columns_str);
			end_of_last_command = true;
			list_free(all_conditions);
			return;
		}
		UpdatePair pair(index, new_value);
		update_fields.add_tail(pair);
	}

	if (it != end) {
		print_error(error_too_much_arguments, "update��Ҫ3��5������!");
		end_of_last_command = true;
		list_free(all_conditions);
		return;
	}

	int update_num = p_table->update_objects(all_conditions, update_fields);
	cout << "�ɹ�����" << update_num << "������!" << endl;
	database->fresh_bit = false;
	list_free(all_conditions);
	end_of_last_command = true;
}

/*ɾ������*/
void CommandCycle::command_do_delete(sregex_token_iterator &it) {
	if (check_database_null()) {
		return;
	}
	if (it == end) {
		lose_argument_error("delete֮����Ҫfrom!");
		return;
	}
	string from_str = *it;
	it++;
	if (from_str != keyword_from) {
		print_error(error_unknown_command, from_str, ":�˴���Ҫfrom�ؼ���!");
		end_of_last_command = true;
		return;
	}

	string table_name = *it;
	it++;
	DestinyTable* p_table = NULL;
	if (!database->contains_table(table_name, p_table)) {
		print_error(error_table_not_exists, table_name);
		end_of_last_command = true;
		return;
	}
	int delete_num;
	if (it == end) {
		if (!enable_last_command) {
			delete_num = p_table->objects.length;
			p_table->objects.clear();
			cout << "ɾ��" << delete_num << "������!" << endl;
			end_of_last_command = true;
			return;
		}
		else {
			end_of_last_command = false;
			return;
		}
		return;
	}

	string where_str = *it;
	it++;
	if (where_str != keyword_where) {
		print_error(error_unknown_command, where_str, ":�˴��Ƿ�Ӧ����where�ؼ���?");
		end_of_last_command = true;
		return;
	}

	string condition_str;
	if (it == end) {
		lose_argument_error("where֮����Ҫ������������!");
		return;
	}

	condition_str = *it;
	it++;
	if (it != end) {
		print_error(error_too_much_arguments, "deleteֻ��Ҫ2������4������!");
		end_of_last_command = true;
		return;
	}

	SingleList<Condition*> all_conditions;
	if (!get_conditions_by_str(condition_str, p_table->column_names, all_conditions)) {
		return;
	}

	delete_num = p_table->delete_object(all_conditions);
	cout << "�ɹ�ɾ��" << delete_num << "������!" << endl;
	database->fresh_bit = false;
	list_free(all_conditions);
	end_of_last_command = true;
}

/*rename����*/
void CommandCycle::command_do_rename(sregex_token_iterator &it) {
	if (check_database_null()) {
		return;
	}
	if (it == end) {
		lose_argument_error("rename֮����Ҫ����table����column!");
		return;
	}
	string type_str = *it;
	it++;

	if (type_str == keyword_table) {
		if (it == end) {
			lose_argument_error("table֮����Ҫ��������!");
			return;
		}
		else {
			string table_name = *it;
			it++;
			DestinyTable* p_table = NULL;
			if (!database->contains_table(table_name, p_table)) {
				print_error(error_table_not_exists, table_name);
				end_of_last_command = true;
				return;
			}
			if (it == end) {
				lose_argument_error(table_name, "֮����Ҫһ����ʾ�±����Ĳ���!");
				return;
			}
			string new_name = *it;
			it++;
			if (it == end) {
				if (p_table->name != new_name) {
					p_table->name = new_name;
					database->fresh_bit = false;
					cout << "�������ɹ�!" << endl;
				}
				else {
					cout << "δ���κθı�!" << endl;
				}
				end_of_last_command = true;
				return;
			}
			else {
				print_error(error_too_much_arguments, "rename����ֻ��Ҫ3������5������!");
				end_of_last_command = true;
				return;
			}
		}
	}
	else if (type_str == "column") {
		if (it == end) {
			lose_argument_error("column֮����Ҫ���������Ĳ���!");
			return;
		}
		string column_name = *it;
		it++;
		if (it == end) {
			lose_argument_error(column_name, "֮����Ҫin����!");
			return;
		}
		string in_str = *it;
		it++;
		if (in_str != "in") {
			if (column_name == "in") {
				print_error(error_lose_arguments, "column֮����Ҫ���������Ĳ���!");
				end_of_last_command = true;
				return;
			}
			print_error(error_unknown_command, in_str, ":�˴��Ƿ�Ӧ����in!");
			end_of_last_command = true;
			return;
		}
		if (it == end) {
			lose_argument_error("in֮����Ҫһ����������Ĳ���!");
			return;
		}
		string table_name = *it;
		it++;
		DestinyTable *p_table = NULL;
		if (!database->contains_table(table_name, p_table)) {
			print_error(error_table_not_exists, table_name);
			end_of_last_command = true;
			return;
		}
		int index = p_table->column_names.index_of(column_name);
		if (index == -1) {
			print_error(error_column_not_found, column_name);
			end_of_last_command = true;
			return;
		}
		if (it == end) {
			lose_argument_error(table_name, "֮����Ҫһ�������������Ĳ���!");
			return;
		}
		string new_column = *it;
		it++;
		if (new_column == column_name) {
			end_of_last_command = true;
			cout << "δ���κθı�!" << endl;
			return;
		}
		if (it == end) {
			if (p_table->column_names.set(index, new_column)) {
				cout << "���������ɹ�!" << endl;
				database->fresh_bit = false;
				end_of_last_command = true;
				return;
			}
			else {
				print_error(error_unknown, "��������ʧ��!");
				end_of_last_command = true;
				return;
			}
		}
		else {
			print_error(error_too_much_arguments, "rename����ֻ��Ҫ3������5������!");
			end_of_last_command = true;
			return;
		}
	}
	else {
		print_error(error_unknown_command, type_str, ":�˴���Ҫtable����column!");
		end_of_last_command = true;
		return;
	}
}

/*��������ѭ��*/
void CommandCycle::command_single_cycle(const string &single_command_str) {
	if (end_of_last_command) {
		single_command = "";
	}
	else {
		single_command.append(" ");
	}
	single_command.append(single_command_str);
	sregex_token_iterator it(single_command.begin(), single_command.end(), regex_empty, -1);
	if (it != end) {//NOTICE:"if" or "while"
		string str = *it;
		it++;
		if (str == keyword_insert) {
			command_do_insert(it);
		}
		else if (str == keyword_select) {
			command_do_select(it);
		}
		else if (str == keyword_update) {
			command_do_update(it);
		}
		else if (str == keyword_delete) {
			command_do_delete(it);
		}
		else if (str == keyword_create) {
			command_do_create(it);
		}
		else if (str == keyword_sort) {
			command_do_sort(it);
		}
		else if (str == keyword_drop) {
			command_do_drop(it);
		}
		else if (str == keyword_seperator) {
			;
		}
		else if (str == keyword_show) {
			command_do_show(it);
		}
		else if (str == keyword_exit) {
			command_do_exit(it);
		}
		else if (str == keyword_rename) {
			command_do_rename(it);
		}
		else if (str == keyword_version) {
			command_do_version(it);
		}
		else if (str == keyword_open) {
			command_do_open(it);
		}
		else if (str == keyword_auto_commit) {
			command_do_auto_commit(it);
		}
		else if (str == keyword_help) {
			command_do_help(it);
		}
		else if (str == keyword_commit) {
			command_do_commit(it);
		}
		else if (str == keyword_run) {
			command_do_run(it);
		}
		else if (str == "") {
			;
		}
		else {
			print_error(error_unknown_command, str);
			return;
		}
		if (auto_commit&&database) {
			database->commit();
		}
	}
}

/*����ѭ��������*/
/*child_cycle:�Ƿ�Ϊ������ѭ��*/
void CommandCycle::command_cycle(istream &ist, bool child_cycle) {
	while (getline(ist, command)) {
		command.append(" ");
		if (regex_match(command, regex_empty)) {
			if (end_of_last_command) {
				print_destiny_line_head();
				continue;
			}
			else {
				print_line_head();
				continue;
			}
		}
		else if (regex_match(command, regex_empty_seperator)) {
			enable_last_command = false;
			command_single_cycle(string(""));
			if (!end_of_last_command) {
				print_line_head();
				continue;
			}
		}
		else {
			sregex_token_iterator it(command.begin(), command.end(), regex_seperator, -1);
			while (it != end) {
				string command_temp_str = *it;
				it++;
				if (it == end) {
					enable_last_command = true;
				}
				else {
					enable_last_command = false;
				}
				command_single_cycle(command_temp_str);
			}
			if (!end_of_last_command) {
				print_line_head();
				continue;
			}
		}
		if (child_cycle) {//��ѭ��
			cout << endl;
		}
		else {//��ѭ��
			print_destiny_line_head();
		}
	}
}

#endif
