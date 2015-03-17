/*******************************************************
 *	command_cycle.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: 请阅读 LICENSE 文件
 *	Description(描述):命令循环
 ******************************************************/
#pragma once
#ifndef COMMAND_CYCLE_H
#define COMMAND_CYCLE_H

#include "destiny.h"
#include "error.h"
#include "database_file.h"
#include "query.h"

//NOTICE:转义字符处理

 /*提醒提交更改*/
void CommandCycle::warning_commit() {
	if (database&&!database->fresh_bit) {
		if (auto_commit) {
			database->commit();
		}
		else {
			cout << "有未提交的更改,是否提交更改?(y/n)";
			string user_answer = "";
			getline(cin, user_answer);
			if (user_answer == "" || regex_match(user_answer, regex_empty) || regex_match(user_answer, regex_empty_yes)) {
				database->commit();
				cout << "已提交更改!" << endl;
			}
			else {
				cout << "已放弃提交更改!" << endl;
			}
		}
	}
}

/*提醒提交更改*/
bool CommandCycle::check_database_null() {
	if (database == NULL) {
		print_error(error_no_database_file);
		end_of_last_command = true;
		return true;
	}
	return false;
}

/*提取conditions*/
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
/*释放链表空间*/
void CommandCycle::list_free(SingleList<T*> &list) {
	SingleNode<T*> *p = list.head_node;
	while (p != NULL) {
		delete p->element;
		p = p->next;
	}
}

/*打印参数错误信息*/
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

/*version命令*/
void CommandCycle::command_do_version(sregex_token_iterator &it) {
	if (it == end) {
		print_version();
	}
	else {
		print_error(Error::error_too_much_arguments, "version不需要参数!");
	}
	end_of_last_command = true;
}

/*help命令*/
void CommandCycle::command_do_help(sregex_token_iterator &it) {
	if (it == end) {
		print_help_information();
	}
	else {
		print_error(error_too_much_arguments, "help不需要参数!");
	}
	end_of_last_command = true;
}

/*exit命令*/
void CommandCycle::command_do_exit(sregex_token_iterator &it) {
	if (it == end) {
		warning_commit();
		print_exit();
		exit(0);
	}
	else {
		print_error(error_too_much_arguments, "exit不需要参数!");
		end_of_last_command = true;
	}
}

/*open命令*/
void CommandCycle::command_do_open(sregex_token_iterator &it) {
	string file_path;
	if (it == end) {
		lose_argument_error("open之后需要一个代表文件的参数!");
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
			print_error(warning_no_such_file, "已创建空数据库文件:", file_path);
			create_file(file_path);
			open_file(file_path);
		}
	}
	else {
		print_error(error_too_much_arguments, "open只需要一个参数!");
	}
	end_of_last_command = true;
}

/*show命令*/
void CommandCycle::command_do_show(sregex_token_iterator &it) {
	if (check_database_null()) {
		return;
	}
	if (it == end) {
		lose_argument_error("show之后需要一个代表变量的参数!");
		return;
	}
	string str = *it;
	it++;
	if (it == end) {
		if (str == "tables") {
			if (database->tables.length < 1) {
				cout << "数据库是空的,没有表!" << endl;
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
		print_error(error_too_much_arguments, "show只需要一个参数!");
	}
	end_of_last_command = true;
}

/*drop命令*/
void CommandCycle::command_do_drop(sregex_token_iterator &it) {
	if (check_database_null()) {
		return;
	}
	if (it == end) {
		lose_argument_error("drop之后需要table!");
		return;
	}
	string table_str = *it;
	it++;
	if (table_str != keyword_table) {
		print_error(error_unknown_command, table_str, "此处需要table!");
		end_of_last_command = true;
		return;
	}
	if (it == end) {
		lose_argument_error(keyword_table, "之后需要一个代表表名的参数!");
		return;
	}
	string table_name = *it;
	it++;
	if (it != end) {
		print_error(error_too_much_arguments, "drop只需要两个参数!");
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
		cout << "删除表" << table_name << "成功!" << endl;
		database->fresh_bit = false;
	}
	else {
		print_error(error_unknown, "删除表失败!");
	}
	end_of_last_command = true;
	return;
}

/*drop命令*/
void CommandCycle::command_do_sort(sregex_token_iterator &it) {
	if (check_database_null()) {
		return;
	}
	if (it == end) {
		lose_argument_error("sort之后需要一个代表表名的参数!");
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
		lose_argument_error(table_name, "之后需要by!");
		return;
	}
	string by_str = *it;
	it++;
	if (by_str != "by") {
		print_error(error_unknown_command, by_str, "此处需要by!");
		end_of_last_command = true;
		return;
	}
	if (it == end) {
		lose_argument_error(keyword_table, "by之后需要一个代表列名的参数!");
		return;
	}
	string column_name = *it;
	it++;
	if (it != end) {
		print_error(error_too_much_arguments, "sort只需要三个参数!");
		end_of_last_command = true;
		return;
	}
	if (p_table->column_names.index_of(column_name) == -1) {
		print_error(error_column_not_found, column_name);
		end_of_last_command = true;
		return;
	}
	p_table->sort_by(column_name);
	cout << "排序完成!" << endl;
	database->fresh_bit = false;
	end_of_last_command = true;
	return;
}

/*autocommit命令*/
void CommandCycle::command_do_auto_commit(sregex_token_iterator &it) {
	if (it == end) {
		lose_argument_error(keyword_auto_commit, "之后需要yes/y/true/t或者no/n/false/f!");
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
			print_error(error_unknown_command, str, "此处需要yes/y/true/t或者no/n/false/f!");
		}
	}
	else {
		print_error(error_too_much_arguments, "autocommit只需要一个参数!");
	}
	end_of_last_command = true;
}

/*commit命令*/
void CommandCycle::command_do_commit(sregex_token_iterator &it) {
	if (check_database_null()) {
		return;
	}
	if (it == end) {
		database->commit();
		cout << "提交更改成功!" << endl;
	}
	else {
		print_error(error_too_much_arguments, "commit不需要参数!");
	}
	end_of_last_command = true;
}

/*run命令*/
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
				print_error(warning_no_such_file, file_path, ":不会执行任何操作!");
			}
		}
		else {
			print_error(error_too_much_arguments, "run只需要一个参数!");
		}
		end_of_last_command = true;
		return;
	}
	lose_argument_error("run之后需要一个代表destinyDB脚本的参数!");
}

/*insert命令*/
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
						lose_argument_error(p_table->name, "后缺少了要插入表中的数据!");
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
								print_error(error_column_num_not_match, "此数据对象字段太多或太少,不能插入表中:", obj_str);
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
						cout << "插入数据共" << insert_num << "行!" << endl;
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
				lose_argument_error("insert之后需要代表表名的参数!");
			}
		}
		else {
			print_error(error_unknown_command, str);
			end_of_last_command = true;
		}
	}
	else {
		lose_argument_error("insert之后需要紧跟into!");
	}
}

/*create命令*/
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
					print_error(error_keyword, str, "不能作为表名!");
					end_of_last_command = true;
					return;
				}
				if (it != end) {
					DestinyTable* p_table = NULL;
					if (database->contains_table(str, p_table)) {
						print_error(error_table_exists, str, ":不可重复建表!");
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
									print_error(error_keyword, str, "不能作为列名!");
									end_of_last_command = true;
									return;
								}
								if (columns.index_of(str_column) != -1) {
									print_error(error_column_repeat, str_column, ":建表失败!");
									end_of_last_command = true;
									return;
								}
								columns.add_tail(str_column);
							}
							p_table = new DestinyTable(table_name, columns);
							if (database->add_table(p_table)) {
								cout << "建表成功!" << endl;
								database->fresh_bit = false;
							}
							else {
								print_error(error_table_num_overflow, MAX_TABLE_NUM_STR);
							}
						}
						else {
							print_error(error_too_much_arguments, "create只需要三个参数!");
						}
					}
					end_of_last_command = true;
				}
				else {
					lose_argument_error(table_name, "之后需要输入列名等参数!");
				}
			}
			else {
				lose_argument_error("table之后缺少表名等参数!");
			}
		}
		else {
			print_error(error_unknown_command, str, ":此处是否应该为table?");
			end_of_last_command = true;
		}
	}
	else {
		lose_argument_error("create后需要紧跟table等参数!");
	}
}

/*select命令*/
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
			cout << "查询结果为空!" << endl;
		}
		delete result;
	}
	else {
		return;
	}
}

/*更新操作*/
void CommandCycle::command_do_update(sregex_token_iterator &it) {
	if (check_database_null()) {
		return;
	}
	if (it == end) {
		lose_argument_error("update之后需要一个代表表名的参数!");
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
		lose_argument_error(table_name, "后需要紧跟where或者set!");
		return;
	}

	string where_str = *it;
	it++;
	bool has_where = false;
	if (where_str != keyword_where) {
		if (where_str != keyword_set) {
			print_error(error_unknown_command, where_str, ":此处是否应该是where关键字?");
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
			lose_argument_error("where之后需要紧跟条件参数!");
			return;
		}

		condition_str = *it;
		it++;
		if (it == end) {
			lose_argument_error("缺少set!");
			return;
		}

		string set = *it;
		it++;
		if (set != keyword_set) {
			if (condition_str == keyword_set) {
				print_error(error_lose_arguments, "where之后需要条件!");
				end_of_last_command = true;
				return;
			}
			else {
				print_error(error_unknown_command, set, "此处是否应该是set!");
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
		lose_argument_error("set之后需要紧跟更新列等参数!");
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
		print_error(error_too_much_arguments, "update需要3或5个参数!");
		end_of_last_command = true;
		list_free(all_conditions);
		return;
	}

	int update_num = p_table->update_objects(all_conditions, update_fields);
	cout << "成功更新" << update_num << "条数据!" << endl;
	database->fresh_bit = false;
	list_free(all_conditions);
	end_of_last_command = true;
}

/*删除操作*/
void CommandCycle::command_do_delete(sregex_token_iterator &it) {
	if (check_database_null()) {
		return;
	}
	if (it == end) {
		lose_argument_error("delete之后需要from!");
		return;
	}
	string from_str = *it;
	it++;
	if (from_str != keyword_from) {
		print_error(error_unknown_command, from_str, ":此处需要from关键字!");
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
			cout << "删除" << delete_num << "条数据!" << endl;
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
		print_error(error_unknown_command, where_str, ":此处是否应该是where关键字?");
		end_of_last_command = true;
		return;
	}

	string condition_str;
	if (it == end) {
		lose_argument_error("where之后需要紧跟条件参数!");
		return;
	}

	condition_str = *it;
	it++;
	if (it != end) {
		print_error(error_too_much_arguments, "delete只需要2个或者4个参数!");
		end_of_last_command = true;
		return;
	}

	SingleList<Condition*> all_conditions;
	if (!get_conditions_by_str(condition_str, p_table->column_names, all_conditions)) {
		return;
	}

	delete_num = p_table->delete_object(all_conditions);
	cout << "成功删除" << delete_num << "条数据!" << endl;
	database->fresh_bit = false;
	list_free(all_conditions);
	end_of_last_command = true;
}

/*rename命令*/
void CommandCycle::command_do_rename(sregex_token_iterator &it) {
	if (check_database_null()) {
		return;
	}
	if (it == end) {
		lose_argument_error("rename之后需要紧跟table或者column!");
		return;
	}
	string type_str = *it;
	it++;

	if (type_str == keyword_table) {
		if (it == end) {
			lose_argument_error("table之后需要紧跟表名!");
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
				lose_argument_error(table_name, "之后需要一个表示新表名的参数!");
				return;
			}
			string new_name = *it;
			it++;
			if (it == end) {
				if (p_table->name != new_name) {
					p_table->name = new_name;
					database->fresh_bit = false;
					cout << "重命名成功!" << endl;
				}
				else {
					cout << "未做任何改变!" << endl;
				}
				end_of_last_command = true;
				return;
			}
			else {
				print_error(error_too_much_arguments, "rename命令只需要3个或者5个参数!");
				end_of_last_command = true;
				return;
			}
		}
	}
	else if (type_str == "column") {
		if (it == end) {
			lose_argument_error("column之后需要代表列名的参数!");
			return;
		}
		string column_name = *it;
		it++;
		if (it == end) {
			lose_argument_error(column_name, "之后需要in参数!");
			return;
		}
		string in_str = *it;
		it++;
		if (in_str != "in") {
			if (column_name == "in") {
				print_error(error_lose_arguments, "column之后需要代表列名的参数!");
				end_of_last_command = true;
				return;
			}
			print_error(error_unknown_command, in_str, ":此处是否应该是in!");
			end_of_last_command = true;
			return;
		}
		if (it == end) {
			lose_argument_error("in之后需要一个代表表名的参数!");
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
			lose_argument_error(table_name, "之后需要一个代表新列名的参数!");
			return;
		}
		string new_column = *it;
		it++;
		if (new_column == column_name) {
			end_of_last_command = true;
			cout << "未做任何改变!" << endl;
			return;
		}
		if (it == end) {
			if (p_table->column_names.set(index, new_column)) {
				cout << "更改列名成功!" << endl;
				database->fresh_bit = false;
				end_of_last_command = true;
				return;
			}
			else {
				print_error(error_unknown, "更改列名失败!");
				end_of_last_command = true;
				return;
			}
		}
		else {
			print_error(error_too_much_arguments, "rename命令只需要3个或者5个参数!");
			end_of_last_command = true;
			return;
		}
	}
	else {
		print_error(error_unknown_command, type_str, ":此处需要table或者column!");
		end_of_last_command = true;
		return;
	}
}

/*单条命令循环*/
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

/*命令循环主函数*/
/*child_cycle:是否为命令子循环*/
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
		if (child_cycle) {//子循环
			cout << endl;
		}
		else {//主循环
			print_destiny_line_head();
		}
	}
}

#endif
