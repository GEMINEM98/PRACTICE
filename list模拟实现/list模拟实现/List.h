#pragma once

#include<iostream>
#include<list>
#include<assert.h>
#include<algorithm>
#include<stdlib.h>

using namespace std;

namespace gly
{
	template<class T>

	struct __list_node
	{
		__list_node<T>* _next;
		__list_node<T>* _prev;
		T _data;

		__list_node(const T& x = T())  // 构造函数 （一个结点）
			:_data(x)
			, _next(nullptr)
			, _prev(nullptr)
		{ }
	};

	template<class T, class Ref, class Ptr>
	struct __list_iterator
	{
		typedef __list_node<T> node;
		typedef __list_iterator<T, Ref, Ptr> Self;

		node* _node;

		__list_iterator(node* node) // 用结点指针构造迭代器
			:_node(node)
		{}

		Ref& operator*()           // 内置类型
		{                          // 不传引用就会多一层拷贝，引用返回不仅能够提高效率，还能修改这个值
			return _node->_data;
		}

		Ptr operator->()           // 自定义类型
		{                          // 用cout << it->_year << "-" << it->_month << "-" << it->_day << endl 输出
			return &_node->_data;  // return返回的是Date*  相当于 it->->_year(it->是Date*，Date*->_year是值)
		}                          //                      编译器在此处做了特殊处理，省掉了一个箭头 it->_year


		Self& operator++()         // 前置++
		{
			_node = _node->_next;
			return *this;
		}
		Self operator++(int)       // 后置++
		{
			__list_iterator<T> tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		Self& operator--()         // 前置--
		{
			_node = _node->_prev;
			return *this;
		}
		Self operator--(int)       // 后置--
		{
			__list_iterator<T> tmp(*this);
			_node = _node->_prev;
			return tmp;
		}

		// it1 != it2
		bool operator!=(const Self& it)   // 比较结点的指针即可
		{
			return _node != it._node;     // 两个指针不同，这两个结点就不同
 		}
		// it1 == it2
		bool operator==(const Self& it)   // _node 表示指向结点的指针，若两个节点的指针相同，则这两个节点就相同
		{
			return _node == it._node;
		}

	};

	template<class T>
	class list
	{
		typedef __list_node<T> node;

	public:

		// 迭代器对于string和vector是指针；对于list不是指针，因为list空间不是连续的

		typedef __list_iterator<T, T&, T*> iterator; // 普通迭代器
		typedef __list_iterator<T, const T&, const T*> const_iterator;// const迭代器

		// 普通对象调用普通迭代器
		iterator begin()
		{
			return iterator(_head->_next);
		}
		iterator end()
		{
			return iterator(_head);
		}
		// const对象调用const迭代器
		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}
		const_iterator end() const
		{
			return const_iterator(_head);
		}

		// 拷贝构造函数
		list(const list<T>& l)
		{
			// 先创建一个头结点，自己指向自己
			_head = new node();  
			_head->_next = _head;
			_head->_prev = _head;
			// 然后用迭代器尾插值
			const_iterator it = l.begin();
			while (it != l.end())
			{
				push_back(*it);
				++it;
			}
		}
		// 拷贝构造函数----赋值  l2=l1   
		/*list<T>& operator=(const list<T>& l)
		{
			this->clear();
			auto it = l.begin();
			while (it != end())
			{
				push_back(*it);
				++it;
			}
		}*/
		list<T>& operator=(list<T>& l)  // 所有的深拷贝都可以这样写
		{
			swap(_head, l._head);
			return *this;
		}

		// 构造函数
		list()
		{	// 带头结点
			_head = new node(T()); // 不知道T是什么类型，所以传T的匿名对象
			_head->_next = _head;
			_head->_prev = _head;
		}

		// 析构函数
		~list()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);
			}
			delete _head;
			_head = nullptr;
		}

		// 清空所有数据
		void clear()
		{
			clear(); // 清掉所有数据
			delete _head;
			_head = nullptr;
		}

		//void push_back(const T& x) // 尾插
		//{
		//	node* tail = _head->_prev;
		//	node* newnode = new node(x);

		//	// head...tail newnode
		//	tail->_next = newnode;
		//	newnode->_prev = tail;
		//	newnode->_next = _head;
		//	_head->_prev = newnode;
		//}
		void push_back(const T& x)   // 尾插
		{
			insert(end(), x);
		}
		void push_front(const T& x)  // 头插
		{
			insert(begin(), x);
		}
		void pop_back()              // 尾删
		{
			erase(--end());
		}
		void pop_front()             // 头删
		{
			erase(begin());
		}

		// 在pos位置插入x
		void insert(iterator pos, const T& x)
		{
			node* cur = pos._node;   // 直接就可以获取指向该位置的指针
			node* prev = cur->_prev;
			node* newnode = new node(x);

			prev->_next = newnode;
			newnode->_prev = prev;
			cur->_prev = newnode;
			newnode->_next = cur;
		}

		// 删除pos位置的值
		iterator erase(iterator pos)
		{
			node* cur = pos._node;    // 先用指针cur指向pos位置
			assert(cur != _head);

			node* prev = cur->_prev;  
			node* next = cur->_next;  
			delete cur;               // 利用完cur后，销毁该指针

			prev->_next = next;
			next->_prev = prev;

			return iterator(next);
		}

	private:
		node* _head; // 指向头结点的指针
	};

	// 打印list
	void print_list(const list<int>& l)  // const对象调const函数，所以begin/end为const
	{
		list<int>::const_iterator it = l.begin();
		while (it != l.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}

	void test()
	{
		list<int> l;
		l.push_back(1);		
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);
		print_list(l);

		// 删除掉list中的所有偶数
		list<int>::iterator it = l.begin();
		while (it != l.end())
		{
			if (*it % 2 == 0)
				it = l.erase(it);
			else
				++it;
		}
		print_list(l);
	}

	struct Date  // 相当于一个类
	{
		int _year = 1900;
		int _month = 1;
		int _day = 1;
	};
	void test1()
	{
		list<Date> l;
		l.push_back(Date());
		l.push_back(Date());

		list<Date>::iterator it = l.begin(); // 等价于 auto it = l.begin();
		while (it != l.end())
		{
			//cout << *it << endl; // 这里不支持直接输出
			cout << it->_year << "-" << it->_month << "-" << it->_day << endl;  // 此时需要重载 operator->
			++it;
		}
		cout << endl;
	}

	void test2()
	{
		list<int> l;
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);
		print_list(l);

		// 赋值或拷贝
		list<int> copy = l;
		l.push_back(5);
		print_list(copy);
		print_list(l);
	}
}