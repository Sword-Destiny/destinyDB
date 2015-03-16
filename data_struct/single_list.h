/*******************************************************
 *	SingleList.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: All rifgts reserved! 保留所有权利！
 *	Description(描述):单链表定义
 ******************************************************/
#pragma once
#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

#define name_to_str(a) (#a)

/*超前声明*/
template<class T> class SingleList;

template<class T>
/*节点类*/
class SingleNode {
public:
	T element;
	SingleNode<T>* next;
	friend class SingleList<T>;
	SingleNode(const SingleNode<T>& s) {}
	SingleNode& operator=(const SingleNode<T>& s) {
		return *this;
	}
public:
	inline SingleNode() :next(NULL) {}
	explicit SingleNode(const T&elem) :element(elem), next(NULL) {}
	~SingleNode() {
		delete next;
	}
};

template<class T>
/*单链表*/
class SingleList {
public:
	int length;
	SingleNode<T>* head_node;
	SingleNode<T> *tail_node;
public:
	SingleList() :length(0), head_node(NULL), tail_node(NULL) {}
	SingleList(const T* data, int dataSize) :length(dataSize) {
		if (dataSize == 0) {
			head_node = NULL;
			return;
		}
		head_node = new SingleNode<T>(data[0]);
		SingleNode<T>* p = head_node;
		for (int i = 1; i < dataSize; i++) {
			SingleNode<T>* r = new SingleNode<T>(data[i]);
			p->next = r;
			p = r;
		}
		tail_node = p;
	}
	SingleList(const SingleList<T>& s) :length(s.length) {
		if (s.length == 0) {
			this->head_node = NULL;
			this->tail_node = NULL;
			return;
		}
		this->head_node = new SingleNode<T>(s.head_node->element);
		SingleNode<T>* p = this->head_node, *q = s.head_node->next;
		while (q) {
			p->next = new SingleNode<T>(q->element);
			q = q->next;
			p = p->next;
		}
		tail_node = p;
	}
	SingleList& operator=(const SingleList<T>& s) {
		if (this == &s) {
			return *this;
		}
		delete this->head_node;
		this->length = s.length;
		if (s.length == 0) {
			this->head_node = NULL;
			this->tail_node = NULL;
			return *this;
		}
		this->head_node = new SingleNode<T>(s.head_node->element);
		SingleNode<T>* p = this->head_node, *q = s.head_node->next;
		while (q) {
			p->next = new SingleNode<T>(q->element);
			q = q->next;
			p = p->next;
		}
		tail_node = p;
		return *this;
	}
	~SingleList() {
		delete head_node;
	}
	/*返回数据在链表中的索引*/
	virtual int index_of(const T& data)const {
		SingleNode<T> *p = head_node;
		int i = 0;
		for (; p != NULL&&p->element != data; i++) {
			p = p->next;
		}
		if (p != NULL) {
			return i;
		}
		return -1;
	}
	/*得到索引index处的数据:不做任何检查*/
	T operator[](int index) const {
		SingleNode<T>* p = head_node;
		for (int j = 0; j < index; j++) {
			p = p->next;
		}
		return p->element;
	}
	/*得到索引index处的数据:不做任何检查*/
	T& operator[](int index) {
		SingleNode<T>* p = head_node;
		for (int j = 0; j < index; j++) {
			p = p->next;
		}
		return p->element;
	}
	/*设置索引index处的数据为data*/
	bool set(int index, const T& data) {
		if (index < 0 || index >= length) {
			return false;
		}
		SingleNode<T>* p = head_node;
		for (int j = 0; j < index; j++) {
			p = p->next;
		}
		p->element = data;
		return true;
	}
	/*在末尾添加数据*/
	void add_tail(const T &data) {
		length++;
		if (head_node == NULL) {
			head_node = new SingleNode<T>(data);
			tail_node = head_node;
			return;
		}
		tail_node->next = new SingleNode<T>(data);
		tail_node = tail_node->next;

	}
	/*移除指定元素*/
	bool remove(const T& data) {
		if (!this->head_node) {
			return false;
		}
		if (head_node->element == data) {
			SingleNode<T>* p = head_node->next;
			head_node->next = NULL;
			delete head_node;
			head_node = p;
			length--;
			return true;
		}
		else {
			SingleNode<T>* p = head_node, *q = NULL;
			while (p != NULL&& p->element != data) {
				q = p;
				p = p->next;
			}
			if (p == NULL) {
				return false;
			}
			q->next = p->next;
			p->next = NULL;
			delete p;
			length--;
			return true;
		}
	}
	/*移除所有元素*/
	void clear() {
		delete head_node;
		head_node = NULL;
		this->length = 0;
	}
};

#endif
