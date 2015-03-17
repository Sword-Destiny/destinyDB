/*******************************************************
 *	query.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: 请阅读 LICENSE 文件
 *	Description(描述):查询函数
 ******************************************************/
#pragma once
#ifndef QUERY_H
#define QUERY_H

#include "command_cycle_defination.h"

bool CommandCycle::query(sregex_token_iterator &it, ResultSet* &current_result_set) {
	if (it == end) {
		lose_argument_error("select之后需要紧跟列名等参数!");
		return false;
	}

	string select_column_str = *it;
	it++;
	if (it == end) {
		lose_argument_error("select之后需要where或者from等参数!");
		return false;
	}

	string where_str = *it;
	it++;
	bool has_where = false;
	if (where_str != keyword_where) {
		if (where_str != keyword_from) {
			print_error(error_unknown_command, where_str, "是否应该是where关键字!");
			end_of_last_command = true;
			return false;
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
			lose_argument_error("where之后需要紧跟条件表达式等参数!");
			return false;
		}

		condition_str = *it;
		it++;
		if (it == end) {
			lose_argument_error("缺少from等参数!");
			return false;
		}

		string from_str = *it;it++;
		if (from_str != keyword_from) {
			if (condition_str == keyword_from) {
				print_error(error_lose_arguments, "where之后需要条件!");
				end_of_last_command = true;
				return false;
			}
			else {
				print_error(error_unknown_command, from_str, "需要from关键字!");
				end_of_last_command = true;
				return false;
			}
		}
	}
	else {
		condition_str = "";
	}
	if (it == end) {
		lose_argument_error(keyword_from, "之后需要表名等参数!");
		return false;
	}

	string table_name = *it;
	it++;

	if (table_name != "select") {
		DestinyTable* p_table = NULL;
		if (database->contains_table(table_name, p_table)) {
			current_result_set = new ResultSet();
			current_result_set->column_names = p_table->column_names;
			current_result_set->objects = p_table->objects;
		}
		else {
			print_error(error_table_not_exists, table_name);
			end_of_last_command = true;
			if (current_result_set) {
				delete current_result_set;
				current_result_set = NULL;
			}
			return false;
		}
	}
	else {
		if (!query(it, current_result_set)) {
			delete current_result_set;
			current_result_set = NULL;
			return false;
		}
	}
	//NOTICE
	//if (current_result_set == NULL) {
	//	end_of_last_command = false;
	//	return false;
	//}

	sregex_token_iterator column_it(select_column_str.begin(), select_column_str.end(), regex_comma, -1);
	SingleList<string> columns;
	while (column_it != end) {
		string single_column = *column_it;
		column_it++;

		SingleNode<string> *p_c = current_result_set->column_names.head_node;
		while (p_c != NULL) {
			if (p_c->element == single_column) {
				if (columns.index_of(p_c->element) == -1) {
					columns.add_tail(p_c->element);
				}
			}
			else {
				try {
					regex pattern(single_column);
					if (regex_match(p_c->element, pattern)) {
						if (columns.index_of(p_c->element) == -1) {
							columns.add_tail(p_c->element);
						}
					}
				}
				catch (regex_error) {
					;//忽略正则表达式错误
				}
			}
			p_c = p_c->next;
		}
	}

	SingleList<Condition*> all_conditions;
	if (!get_conditions_by_str(condition_str, current_result_set->column_names, all_conditions)) {
		delete current_result_set;
		current_result_set = NULL;
		return false;
	}

	ResultSet* result_set_final = current_result_set->select_objects(all_conditions, columns);
	delete current_result_set;
	current_result_set = result_set_final;
	list_free(all_conditions);
	end_of_last_command = true;
	return true;
}

#endif