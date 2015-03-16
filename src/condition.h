/*******************************************************
 *	condition.h
 *	author:��������
 *	copyright(c) 2015 - ~: All rifgts reserved! ��������Ȩ����
 *	Description(����):����ƥ�����
 ******************************************************/
#pragma once
#ifndef CONDITION_H
#define CONDITION_H

#include "destiny_object.h"
#include "includes.h"

 /*��һƥ������*/
class SingleCondition {
public:
	int match_field_column_id;//ƥ���ֶε�����
	logic_match_type m_type;//ƥ������
	string match_value;//ƥ��ֵ

	inline SingleCondition() {}

	inline SingleCondition(const int &id, const logic_match_type &match, const string &val) {
		this->match_field_column_id = id;
		this->m_type = match;
		this->match_value = val;
	}

	inline bool operator!=(const SingleCondition &sc)const {
		return this->match_field_column_id != sc.match_field_column_id || this->m_type != sc.m_type || this->match_value == sc.match_value;
	}
	inline bool operator==(const SingleCondition &sc)const {
		return !this->operator!=(sc);
	}
	/*�߼���*/
	void reverse() {
		this->m_type = logic_reverse(this->m_type);
	}
	static string get_single_condition(const string &str, const SingleList<string> &columns, SingleCondition* &ret) {
		int match_num = match_type_num(str);
		if (match_num == 6) {
			return "";
		}
		sregex_token_iterator it(str.begin(), str.end(), logic_match_types[match_num], -1);
		if (it == end) {
			return "";
		}
		string match_column = *it++;
		int index = columns.index_of(match_column);
		if (index == -1) {
			return match_column;
		}
		if (it == end) {
			return "";
		}
		string match_value = *it++;
		if (it != end) {
			return "";
		}
		ret = new SingleCondition(index, get_match_type(match_num), match_value);
		return "";
	}
private:
	inline bool operator>(const SingleCondition &sc)const {
		return this->match_field_column_id > sc.match_field_column_id;
	}
	inline bool operator<(const SingleCondition &sc)const {
		return this->match_field_column_id < sc.match_field_column_id;
	}
	inline bool operator>=(const SingleCondition &sc)const {
		return this->match_field_column_id >= sc.match_field_column_id;
	}
	inline bool operator<=(const SingleCondition &sc)const {
		return this->match_field_column_id <= sc.match_field_column_id;
	}
};

/*ƥ������*/
class Condition {
public:

	Array<SingleCondition> conditions;

	Condition(const SingleList<SingleCondition> &cons) :conditions(cons.length) {
		SingleNode<SingleCondition> *p = cons.head_node;
		int i = 0;
		while (p != NULL) {
			this->conditions[i++] = p->element;
			p = p->next;
		}
	}

	/*�Ƿ�ƥ��*/
	bool match(const DestinyObject &obj)const {
		for (int i = 0; i < this->conditions.length; i++) {
			SingleCondition con = this->conditions[i];
			string val = obj.datas[con.match_field_column_id];
			switch (con.m_type) {
				case equal:
					if (!is_str_equal(con.match_value, val)) {
						return false;
					}
					break;
				case not_equal:
					if (is_str_equal(con.match_value, val)) {
						return false;
					}
					break;
				case bigger_than:
					if (!bigger_than_str(val, con.match_value)) {
						return false;
					}
					break;
				case smaller_than:
					if (is_str_equal(con.match_value, val) || bigger_than_str(val, con.match_value)) {
						return false;
					}
					break;
				case bigger_or_equal:
					if (!is_str_equal(con.match_value, val) &&!bigger_than_str(val, con.match_value)) {
						return false;
					}
					break;
				case smaller_or_equal:
					if (bigger_than_str(val, con.match_value)) {
						return false;
					}
					break;
				default:
					break;
			}
		}
		return true;
	}

};

#endif