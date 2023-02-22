#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<iostream>
#include<cstring>
#include<cassert>
using std::cout;
using std::endl;
using std::cin;
using std::ostream;
using std::istream;

namespace wpy
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		//string()
		//	:_str(new char[1])
		//	,_capacity(0)
		//	,_size(0)
		//{
		//	_str[0] = '\0';
		//}
		string(const char* str = "") //缺省参数需要用常量字符串，不能用单个字符'\0'-> nullptr
			:_size(strlen(str))
		{//构造函数
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);

		}
		string(const string& s)
			:_size(s._size)
			,_capacity(s._capacity)
		{//拷贝构造函数
			_str = new char[_capacity + 1];
			strcpy(_str,s._str);
		}
		~string()
		{//析构函数
			delete[] _str;
			_str = nullptr;
			_capacity = _size = 0;
		}
		string& operator=(const string& s)
		{
			if (this != &s)
			{
				//方法1
				//delete[] _str;
				//_str = new char[s._capacity + 1];
				//_size = s._size;
				//_capacity = s._capacity;
				//strcpy(_str, s._str);

				//更好的方法2(防止new失败)
				char* tmp = new char[s._capacity + 1];
				strcpy(tmp, s._str);

				delete[] _str;
				_str = tmp;
				_size = s._size;
				_capacity = s._capacity;
			}

			return *this;
		}
		const char& operator[] (size_t pos) const
		{
			assert(pos < _size);
			return _str[pos];
		}
		char& operator[] (size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}
		bool operator> (const string& s) const
		{
			return strcmp(_str, s._str) > 0;
		}
		bool operator== (const string& s) const
		{
			return strcmp(_str, s._str) == 0;
		}
		bool operator< (const string& s) const
		{
			return !(*this >= s);
		}
		bool operator>= (const string& s) const
		{
			return *this > s || *this == s;
		}
		bool operator<= (const string& s) const
		{
			return !(*this>s);
		}
		bool operator!= (const string& s) const
		{
			return !(*this == s);
		}
		void reverse(size_t n) //不能缩容
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;
				_str = tmp;
				_capacity = n;
			}

		}
		void push_back(char x)
		{
			if (_size == _capacity)
			{
				reverse(_capacity * 2);
			}
			_str[_size] = x;
			_size++;

			_str[_size] = '\0';
		}
		string& append(const char* str)
		{
			int len = strlen(str);
			if (_size + len > _capacity)
			{
				reverse(_size+len);
			}
			//for (int i = 0; i < len; i++)
			//{
			//	_str[_size + i] = *(str++);
			//}
			strcpy(_str+_size,str);
			_size = _size + len;
			return *this;
		}
		string& insert(size_t pos, const char ch)
		{
			assert(pos <= _size);
			if (_size + 1 > _capacity)
			{
				reverse(_size+1);
			}
			size_t end = _size+1;
			while (end > pos)
			{
				_str[end] = _str[end-1];
				end--;
			}
			_str[pos] = ch;
			_size += 1;
			return *this;
		}
		string& insert(size_t pos, const char* str)
		{
			assert(pos <= _size);

			size_t len = strlen(str);
			// 挪动数据
			if (_size + len > _capacity)
			{
				reverse(_size+len);
			}
			size_t end = _size + len;
			while (end > pos + len -1)
			{
				_str[end] = _str[end-len];
				end--;
			}
			// 拷贝插入
			strncpy(_str+pos,str,len);
			_size += len;
			return *this;
		}

		string& operator+= (char ch)
		{
			push_back(ch);
			return *this;
		}
		string& operator+= (const char* str)
		{
			append(str);
			return *this;
		}
		const char* c_str() const
		{
			return _str;
		}
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		const_iterator begin() const
		{
			return _str;
		}
		const_iterator end() const
		{
			return _str + _size;
		}
		size_t size() const
		{
			return _size;
		}
		void erase(size_t pos, size_t len = npos)
		{
			assert(pos <= _size);
			if (_size + pos > _capacity || len == npos)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				strcpy(_str + pos, _str + pos + len);
			}
		}

		void clean()
		{
			_str[0] = '\0';
			_size = 0;
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		static const size_t npos = -1;

	};
	ostream& operator<< (ostream& out, string& s)
	{
		for (auto ch : s)
		{
			out << ch;
		}
		return out;
	}
	istream& operator>> (istream& in, string& s)
	{
		s.clean();
		char ch;
		ch = in.get();
		while (ch != ' ' && ch != '\n')
		{
			s += ch;
			ch = in.get();
		}
		return in;
	}
}
void test1()
{
	wpy::string s1;
	wpy::string s2("Hello World");
	wpy::string s3(s2);
	s2[0]++;
	cout << s1.c_str() << endl;
	cout << s2.c_str() << endl;
	cout << s3.c_str() << endl;

	cout << "-------------" << endl;
	s3 = s2 = s1 = s3;
	
	cout << s1.c_str() << endl;
	cout << s2.c_str() << endl;
	cout << s3.c_str() << endl;
	cout << "-------------" << endl;
	wpy::string::iterator it = s3.begin();
	while (it != s3.end())
	{
		cout << *it;
		it++;
	}
	cout << endl;
}
void test2()
{
	wpy::string s1("xxxxx");
	wpy::string s2(s1);
	s2.insert(0,'w');
	s1.insert(0, "yyy");
	//cout << s1.c_str() << endl;
	//cout << s2.c_str() << endl;

}

void test3()
{
	wpy::string s1;
	std::string s2;
	wpy::string s3("Hhh");
	std::string s4("hhh");
	cout << sizeof(s1) << endl;
	cout << sizeof(s2) << endl;
	cout << sizeof(s3) << endl;
	cout << sizeof(s4) << endl;
}