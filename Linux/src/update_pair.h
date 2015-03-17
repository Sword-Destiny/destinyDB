/*******************************************************
 *	update_pair.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: 请阅读 LICENSE 文件
 *	Description(描述):更新数据时匹配对
 ******************************************************/
#pragma once
#ifndef UPDATE_PAIR_H
#define UPDATE_PAIR_H

#include "includes.h"

class UpdatePair {
public:
	string new_value;
	int column_id;
	UpdatePair(const int &id, const string &val) {
		this->column_id = id;
		this->new_value = val;
	}
	inline bool operator!=(const UpdatePair &up)const {
		return this->new_value != up.new_value || this->column_id != up.column_id;
	}
	inline bool operator==(const UpdatePair &up)const {
		return !this->operator!=(up);
	}
	~UpdatePair() {}
	inline bool operator >(const UpdatePair& up)const {
		return this->column_id > up.column_id;
	}
	inline bool operator <(const UpdatePair& up)const {
		return this->column_id < up.column_id;
	}
	inline bool operator >=(const UpdatePair& up)const {
		return this->column_id >= up.column_id;
	}
	inline bool operator <=(const UpdatePair& up)const {
		return this->column_id <= up.column_id;
	}
};

#endif