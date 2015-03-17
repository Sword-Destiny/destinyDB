/*******************************************************
 *	result_set.h
 *	author:��������
 *	copyright(c) 2015 - ~: ���Ķ� LICENSE �ļ�
 *	Description(����):���������
 ******************************************************/
#pragma once
#ifndef RESULT_SET
#define RESULT_SET

#include "condition.h"
#include "update_pair.h"

/*��ͨ��*/
class ResultSet {
public:
	SingleList<DestinyObject> objects;//������
	SingleList<string> column_names;//����

	ResultSet() {

	}

	ResultSet(const SingleList<string> & column_names) {
		this->column_names = column_names;
	}

	virtual ~ResultSet() {

	}
private:
	/*��ȡ����*/
	inline int get_line_num()const {
		return this->objects.length;
	}

	/*��ȡ����*/
	inline int get_column_num()const {
		return this->column_names.length;
	}
public:
	/*��������*/
	bool insert_object(const DestinyObject &obj) {
		if (this->objects.length < MAX_LINE_NUM) {
			this->objects.add_tail(obj);
			return true;
		}
		return false;
	}

	/*ɾ������*/
	/*����ɾ������*/
	int delete_object(const Condition *const condition) {
		int delete_num = 0;
		SingleNode<DestinyObject> *p = NULL, *q = this->objects.head_node;
		while (q != NULL) {
			if (condition->match(q->element)) {
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

	/*���½����*/
	/*���ظ�������*/
	int update_objects(const Condition *const condition, SingleList<UpdatePair> &update_fields) {
		SingleNode<DestinyObject> *q = this->objects.head_node;
		int update_num = 0;
		while (q != NULL) {
			if (condition->match(q->element)) {
				update_num++;
				q->element.update(update_fields);
			}
			q = q->next;
		}
		return update_num;
	}

	/*��ѯ��*/
	ResultSet* select_objects(const SingleList<Condition*> &conditions, const SingleList<string> &select_columns)const {
		ResultSet *result=new ResultSet(select_columns);
		SingleNode<DestinyObject> *q = this->objects.head_node;
		while (q != NULL) {
			SingleNode<Condition*> *p = conditions.head_node;
			if (p == NULL) {
				result->objects.add_tail(q->element.select(select_columns, this->column_names));
				q = q->next;
				continue;
			}
			while (p != NULL) {
				if (p->element->match(q->element)) {
					result->objects.add_tail(q->element.select(select_columns, this->column_names));
					break;
				}
				p = p->next;
			}
			q = q->next;
		}
		return result;
	}
};

#endif