/*******************************************************
 *	table.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: 请阅读 LICENSE 文件
 *	Description(描述):表定义
 ******************************************************/
#pragma once
#ifndef TABLE_H
#define TABLE_H

#include "destiny_object.h"
#include "condition.h"
#include "update_pair.h"
#include "result_set.h"

 /*NOTICE:字段类型检查支持*/

 /*普通表*/
class DestinyTable {
public:
	string name;//表名
	SingleList<DestinyObject> objects;//数据项
	SingleList<string> column_names;//列名

	DestinyTable() {

	}

	DestinyTable(const string &name, const SingleList<string> & column_names) {
		this->name = name;
		this->column_names = column_names;
	}

	virtual ~DestinyTable() {

	}

	int serialize_size()const {
		int serialize_size_t = 0;
		SingleNode<DestinyObject> *p = this->objects.head_node;
		while (p != NULL) {
			serialize_size_t += 4;
			serialize_size_t += p->element.serialize_size();
			p = p->next;
		}
		SingleNode<string> *sp = this->column_names.head_node;
		while (sp != NULL) {
			serialize_size_t += 4;
			serialize_size_t += sp->element.length();
			sp = sp->next;
		}
		serialize_size_t += 4;
		serialize_size_t += this->name.length();
		return serialize_size_t;
	}

	ostream& serialize(ostream &os)const {
		SingleNode<DestinyObject> *p = this->objects.head_node;
		os.write((const char*)&this->objects.length, 4);
		while (p != NULL) {
			//int serialize_size_t = p->element.serialize_size();
			//os.write((char*)&serialize_size_t, 4);
			os << p->element;
			p = p->next;
		}
		SingleNode<string> *sp = this->column_names.head_node;
		os.write((const char*)&this->column_names.length, 4);
		while (sp != NULL) {
			int serialize_size_t = sp->element.length();
			os.write((char*)&serialize_size_t, 4);
			os << sp->element;
			sp = sp->next;
		}
		int name_size = this->name.length();
		os.write((char*)&name_size, 4);
		os << this->name;
		return os;
	}

	static DestinyTable* deserialize(istream& is) {
		DestinyTable* table = new DestinyTable();
		int data_len = 0;
		char* p_len = (char*)&data_len;
		if (!is.read(p_len, 4)) {
			throw database_file_error;
		}
		for (int i = 0; i < data_len; i++) {
			DestinyObject obj = DestinyObject::deserialize(is);
			table->objects.add_tail(obj);
		}
		int column_len = 0;
		char* c_len = (char*)&column_len;
		if (!is.read(c_len, 4)) {
			throw database_file_error;
		}
		for (int i = 0; i < column_len; i++) {
			int len = 0;
			char* d_len = (char*)&len;
			if (!is.read(d_len, 4)) {
				throw database_file_error;
			}
			char* temp = new char[len];
			if (!is.read(temp, len)) {
				throw database_file_error;
			}
			table->column_names.add_tail(string(temp, len));
			delete[] temp;
		}
		int name_len = 0;
		char* name_char = (char*)&name_len;
		if (!is.read(name_char, 4)) {
			throw database_file_error;
		}
		char* temp = new char[name_len];
		if (!is.read(temp, name_len)) {
			throw database_file_error;
		}
		table->name = string(temp, name_len);
		delete[] temp;
		return table;
	}

	friend ostream& operator<<(ostream& os, const DestinyTable& obj) {
		return obj.serialize(os);
	}

	friend istream& operator>>(istream& is, DestinyTable* obj) {
		obj = DestinyTable::deserialize(is);
		return is;
	}

	/*插入数据*/
	bool insert_object(const DestinyObject &obj) {
		if (this->objects.length < MAX_LINE_NUM) {
			this->objects.add_tail(obj);
			return true;
		}
		return false;
	}

	/*删除数据*/
	/*返回删除数量*/
	int delete_object(SingleList<Condition*> &conditions) {
		int delete_num = 0;
		SingleNode<DestinyObject> *p = NULL, *q = this->objects.head_node;
		while (q != NULL) {
			SingleNode<Condition*> *p_c = conditions.head_node;
			bool b = false;
			if (p_c == NULL) {
				b = true;
			}
			while (p_c != NULL) {
				if (!p_c->element->match(q->element)) {
					p_c = p_c->next;
					continue;
				}
				else {
					b = true;
					break;
				}
			}
			if (b) {
				delete_num++;
				if (p == NULL) {
					this->objects.head_node = q->next;
					q->next = NULL;
					delete q;
					q = this->objects.head_node;
				}
				else {
					p->next = q->next;
					q->next = NULL;
					delete q;
					q = p->next;
				}
			}
			else {
				p = q;
				q = q->next;
			}
		}
		return delete_num;
	}

	/*更新表*/
	/*返回更新数量*/
	int update_objects(const SingleList<Condition*> &conditions, SingleList<UpdatePair> &update_fields) {
		int update_num = 0;
		SingleNode<DestinyObject> *q = this->objects.head_node;
		while (q != NULL) {
			SingleNode<Condition*> *p = conditions.head_node;
			if (p == NULL) {
				q->element.update(update_fields);
				update_num++;
				q = q->next;
				continue;
			}
			while (p != NULL) {
				if (!p->element->match(q->element)) {
					p = p->next;
					continue;
				}
				else {
					q->element.update(update_fields);
					update_num++;
					break;
				}
			}
			q = q->next;
		}
		return update_num;
	}

	/*查询表*/
	ResultSet select_objects(const SingleList<Condition*> &conditions, const SingleList<string> &select_columns)const {
		ResultSet result(select_columns);
		SingleNode<DestinyObject> *q = this->objects.head_node;
		while (q != NULL) {
			SingleNode<Condition*> *p = conditions.head_node;
			if (p == NULL) {
				result.objects.add_tail(q->element.select(select_columns, this->column_names));
				q = q->next;
				continue;
			}
			while (p != NULL) {
				if (!p->element->match(q->element)) {
					p = p->next;
					continue;
				}
				else {
					result.objects.add_tail(q->element.select(select_columns, this->column_names));
					break;
				}
			}
			q = q->next;
		}
		return result;
	}

	/*排序*/
	void sort_by(const string& column_name) {
		int index = this->column_names.index_of(column_name);
		if (this->objects.length < 2) {
			return;
		}
		DestinyObject temp;
		SingleNode<DestinyObject> *start = this->objects.head_node;
		SingleNode<DestinyObject> *s_end = this->objects.tail_node;
		SingleNode<DestinyObject> *i = start, *j = i->next;
		while (i != s_end) {
			while (j != s_end) {
				if (bigger_than_str(i->element.datas[index], j->element.datas[index])) {
					temp = j->element;
					j->element = i->element;
					i->element = temp;
				}
				i = i->next;
				j = i->next;
			}
			if (bigger_than_str(i->element.datas[index], j->element.datas[index])) {
				temp = j->element;
				j->element = i->element;
				i->element = temp;
			}
			s_end = i;
			i = start;
			j = i->next;
		}
	}
};

/*NOTICE:暂时不支持*/
/*有序表(带索引)*/
class OrderedDestinyTable { };

#endif