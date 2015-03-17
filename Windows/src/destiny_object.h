/*******************************************************
 *	destiny_object.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: 请阅读 LICENSE 文件
 *	Description(描述):数据对象
 ******************************************************/
#pragma once
#ifndef DESTINY_OBJECT
#define DESTINY_OBJECT

#include "includes.h"
#include "update_pair.h"

/*数据对象*/
class DestinyObject {
public:
	Array<string> datas;//数据

	DestinyObject() {}

	DestinyObject(const Array<string> &datas) :datas(datas) {

	}

	DestinyObject(const SingleList<string> &datas) :datas(datas.length) {
		SingleNode<string> *p = datas.head_node;
		int i = 0;
		while (p != NULL) {
			this->datas[i++] = p->element;
			p = p->next;
		}
	}

	int serialize_size()const {
		int serialize_size_t = 0;
		for (int i = 0; i < this->datas.length; i++) {
			serialize_size_t += 4;
			serialize_size_t += this->datas[i].length();
		}
		serialize_size_t++;
		return serialize_size_t;
	}

	ostream& serialize(ostream &os)const {
		os.write((const char*)&this->datas.length, 4);
		for (int i = 0; i < this->datas.length; i++) {
			int len = this->datas[i].length();
			os.write((char*)&len, 4);
			os << this->datas[i];
		}
		return os;
	}

	static DestinyObject& deserialize(istream &is) {
		DestinyObject* obj = new DestinyObject();
		int data_len = 0;
		char* p_len = (char*)&data_len;
		if (!is.read(p_len, 4)) {
			throw database_file_error;
		}
		Array<string> *r_datas = new Array<string>(data_len);
		for (int i = 0; i < data_len; i++) {
			int len = 0;
			char* c_len = (char*)&len;
			if (!is.read(c_len, 4)) {
				throw database_file_error;
			}
			char* temp = new char[len];
			if (!is.read(temp, len)) {
				throw database_file_error;
			}
			r_datas->operator[](i) = string(temp, len);
			delete[] temp;
		}
		obj->datas = *r_datas;
		return *obj;
	}

	friend ostream& operator<<(ostream& os, const DestinyObject& obj) {
		return obj.serialize(os);
	}

	friend istream& operator>>(istream& is, DestinyObject& obj) {
		obj = DestinyObject::deserialize(is);
		return is;
	}

	inline bool operator==(const DestinyObject& obj) {
		return this->datas == obj.datas;
	}

	inline bool operator!=(const DestinyObject& obj) {
		return this->datas != obj.datas;
	}

	/*更新数据项*/
	void update(SingleList<UpdatePair> &update_fields) {
		SingleNode<UpdatePair> *p = update_fields.head_node;
		while (p != NULL) {
			this->datas[p->element.column_id] = p->element.new_value;
			p = p->next;
		}
	}

	/*查询子对象*/
	DestinyObject select(const SingleList<string> &select_columns, const SingleList<string> &columns)const {
		SingleList<string> list;
		SingleNode<string> *p = select_columns.head_node;
		while (p != NULL) {
			list.add_tail(this->datas[columns.index_of(p->element)]);
			p = p->next;
		}
		return DestinyObject(list);
	}
};

#endif