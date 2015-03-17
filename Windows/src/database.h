/*******************************************************
 *	database.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: 请阅读 LICENSE 文件
 *	Description(描述):数据库类
 ******************************************************/
#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include "table.h"
/*数据库类*/
class DestinyDatabase {
public:
	bool fresh_bit;//标识位：最新
	SingleList<DestinyTable*> tables;//数据库表
	string database_file = "";//数据库文件

	DestinyDatabase() {}

	inline DestinyDatabase(const string &file_path) {
		this->fresh_bit = true;
		this->database_file = file_path;
	}
	virtual inline ~DestinyDatabase() {
		SingleNode<DestinyTable*> *p = this->tables.head_node;
		while (p != NULL) {
			delete p->element;
			p = p->next;
		}
	}

	/*是否包含表*/
	bool contains_table(const string &table_name) {
		SingleNode<DestinyTable*> *p = this->tables.head_node;
		while (p != NULL) {
			if (p->element->name == table_name) {
				return true;
			}
			p = p->next;
		}
		return false;
	}

	/*是否包含表*/
	bool contains_table(const string &table_name, DestinyTable* &ret_table) {
		SingleNode<DestinyTable*> *p = this->tables.head_node;
		while (p != NULL) {
			if (p->element->name == table_name) {
				ret_table = p->element;
				return true;
			}
			p = p->next;
		}
		return false;
	}

	//删除表
	bool drop_table(DestinyTable* p_table) {
		delete p_table;
		return this->tables.remove(p_table);
	}

	/*添加表*/
	bool add_table(DestinyTable *const &t) {
		this->fresh_bit = false;
		if (this->tables.length < MAX_TABLE_NUM) {
			this->tables.add_tail(t);
			return true;
		}
		return false;
	}

	/*是否新鲜:数据库是否有未提交的更改，若有，则不新鲜，若没有，则为最新*/
	inline bool is_fresh()const {
		return this->fresh_bit;
	}

	/*执行更新数据库操作*/
	void commit() {
		if (this->is_fresh()) {
			return;
		}
		this->write_database_to_file();
		this->fresh_bit = true;
	}

	/*将数据库写入文件*/
	void write_database_to_file()const {
		ofstream ofs(this->database_file, ios::out);
		this->serialize(ofs);
		ofs.close();
	}

	int serialize_size()const {
		int serialize_size_t = 0;
		SingleNode<DestinyTable*> *p = this->tables.head_node;
		while (p != NULL) {
			serialize_size_t += 4;
			serialize_size_t += p->element->serialize_size();
			p = p->next;
		}
		return serialize_size_t;
	}

	ostream& serialize(ostream &os)const {
		SingleNode<DestinyTable*> *p = this->tables.head_node;
		os.write((const char*)&this->tables.length, 4);
		while (p != NULL) {
			os << *(p->element);
			p = p->next;
		}
		return os;
	}

	static DestinyDatabase* deserialize(const string& file_path) {
		DestinyDatabase* database = new DestinyDatabase();
		ifstream ifs(file_path, ios::in);
		int data_len = 0;
		char* p_len = (char*)&data_len;
		if (!ifs.read(p_len, 4)) {
			throw database_file_error;
		}
		for (int i = 0; i < data_len; i++) {
			DestinyTable *table = DestinyTable::deserialize(ifs);
			database->tables.add_tail(table);
		}
		database->fresh_bit = true;
		database->database_file = file_path;
		return database;
	}

	friend ostream& operator<<(ostream& os, const DestinyDatabase& obj) {
		return obj.serialize(os);
	}

};

#endif