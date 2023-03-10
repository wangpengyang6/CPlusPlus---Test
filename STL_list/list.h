#pragma once
#include <iostream>
#include <cassert>
using std::cout;
using std::cin;
using std::endl;
using std::pair;

namespace wpy
{
	template<class T>
	struct list_node  //一个结点
	{
		list_node<T>* _next;
		list_node<T>* _prev;
		T _data;
		list_node(const T& x = T())
			:_next(nullptr)
			, _prev(nullptr)
			, _data(x)
		{}
	};

	//1、迭代器要么就是原生指针
	//2、迭代器要么就是自定义类型对原生指针的封装，模拟指针的行为
	template<class T,class Ref,class Ptr> 
	struct list_iterator  //对结点迭代器进行自定义类
	{
		typedef list_node<T> node;
		typedef list_iterator<T, Ref, Ptr> Self;
		node* _node;
		list_iterator(node* n)
			:_node(n)
		{}

		Ref operator*()
		{
			return _node->_data;
		}
		Ptr operator->()
		{
			return &_node->_data;
		}
		Self& operator++() //前置++
		{
			_node = _node->_next;
			return *this;
		}
		Self operator++(int) //后置++
		{
			Self tmp(*this);
			_node = _node->_next;
			return tmp;
		}
		Self& operator--()//前置--
		{
			_node = _node->_prev;
			return *this;
		}
		Self operator--(int)
		{
			Self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}
		bool operator!= (const Self& it)
		{
			return _node != it._node;
		}
		bool operator== (const Self& it)
		{
			return _node == it._node;
		}
	};

	template<class T>
	class list 
	{
		typedef list_node<T> node;

	public:
		typedef list_iterator<T, T&, T*> iterator;
		typedef list_iterator<T, const T&, const T*> const_iterator;

		list()
		{
			_head = new node;
			_head->_next = _head;
			_head->_prev = _head;
		}
		~list()
		{
			clear();
			delete _head;
		}
		list(const list<int>& l)
		{
			empty_init();

			list<int> tmp (l.begin(), l.end());
			swap(tmp);
		}
		void swap(list<int>& l)
		{
			std::swap(_head,l._head);
		}
		list<int>& operator=(list<int> t)
		{
			swap(t);
			return *this;
		}
		iterator begin()
		{
			return iterator(_head->_next);
		}
		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}
		iterator end()
		{
			return iterator(_head);
		}
		const_iterator end() const
		{
			return const_iterator(_head);
		}
		void empty_init()
		{
			_head = new node;
			_head->_next = _head;
			_head->_prev = _head;
		}

		template<class InputIterator>
		list(InputIterator first, InputIterator end) //迭代器区间初始化
		{
			empty_init();
			while (first != end)
			{
				push_back(*first);
				++first;
			}
		}
		void push_back(const T& x)
		{
			//node* newnode = new node(x);
			//node* tail = _head->_prev;
			//newnode->_prev = tail;
			//tail->_next = newnode;
			//newnode->_next = _head;
			//_head->_prev = newnode;
			insert(iterator(_head), x);
		}
		void push_front(const T& x)
		{
			insert(iterator(_head->_next),x);
		}
		void pop_back()
		{
			erase(iterator(_head->_prev));
		}
		void pop_front()
		{
			erase(iterator(_head->_next));
		}
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				erase(it++);
			}
		}
		void insert(iterator pos, const T& x)
		{
			node* cur = pos._node;

			node* newnode = new node(x);

			node* prev = cur->_prev;
			newnode->_prev = prev;
			newnode->_next = cur;
			prev->_next = newnode;
			cur->_prev = newnode;
		}
		void erase(iterator pos)
		{
			assert(pos != end());
			node* cur = pos._node;
			node* prev = cur->_prev;
			node* next = cur->_next;
			prev->_next = next;
			next->_prev = prev;
			delete pos._node;
		}
	private:
		node* _head;
	};

}



//void test1()
//{
//	wpy::list<int> l1;
//	l1.push_back(1);
//	l1.push_back(2);
//	l1.push_back(3);
//	l1.push_back(4);
//	wpy::list<int>::iterator it = l1.begin();
//	while (it != l1.end())
//	{
//		cout << *it << ' ';
//		it++;
//	}
//}

//void test2()
//{
//	wpy::list<pair<int, int>> l;
//	l.push_back({ 1,1 });
//	l.push_back({ 2,2 });
//	l.push_back({ 3,3 });
//	wpy::list<pair<int, int>>::iterator it = l.begin();
//	while (it != l.end())
//	{
//		cout << it->first << ' ' << it->second<<endl;//it->first有编译器优化 省略了一个-> 原版：it->->first
//		it++;
//	}
//}

//void test3()
//{
//	wpy::list<int> l;
//	l.push_back(3);
//	l.push_back(4);
//	l.push_front(2);
//	l.push_front(1);
//	for (auto e : l)
//	{
//		cout << e << ' ';
//	}
//	cout << endl;
//	l.pop_back();
//	l.pop_back();
//	l.pop_front();
//	for (auto e : l)
//	{
//		cout << e << ' ';
//	}
//	cout << endl;
//	auto pos = l.begin();
//	pos++;
//	l.insert(pos, 20);
//	for (auto e : l)
//	{
//		cout << e << ' ';
//	}
//	cout << endl;
//
//	l.clear();
//	for (auto e : l)
//	{
//		cout << e << ' ';
//	}
//	cout << endl;
//}

void test4()
{
	wpy::list<int> l;
	l.push_back(3);
	l.push_back(4);
	l.push_front(2);
	l.push_front(1);
	for (auto e : l)
	{
		cout << e << ' ';
	}
	cout << endl;
	
	wpy::list<int> l1;
	l1 = l;
	l.clear();
	for (auto e : l)
	{
		cout << e << ' ';
	}
	cout << endl;
	cout << "---------- " << endl;
	for (auto e : l1)
	{
		cout << e << ' ';
	}
	cout << endl;
}