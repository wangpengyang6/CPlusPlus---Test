#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<cassert>
#include<string>
#include<cstdlib>
using std::cout;
using std::cin;
using std::endl;
namespace wpy
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		vector()
			:_start(nullptr),
			_finish(nullptr),
			_end_of_storage(nullptr)
		{}
		vector(size_t n,const T& val = T())
		{
			reserve(n);
			for (int i = 0; i < n; i++)
			{
				push_back(val);
			}
		}
		vector(int n, const T& val = T())
		{
			reserve(n);
			for (int i = 0; i < n; i++)
			{
				push_back(val);
			}
		}

		vector(const vector<T>& v)
		{
			vector<T> tmp(v.begin(),v.end());
			swap(tmp);
		}

		//vector(vector<T>& v)//注意深拷贝问题
		//{
		//	_start = new T[v.capacity()];
		//	for (size_t i = 0; i < v.size(); i++)
		//	{
		//		_start[i] = v._start[i];
		//	}
		//	_finish = _start + v.size();
		//	_end_of_storage = _start + v.capacity();
		//}

		//vector(const vector<T>& v)
		//{
		//	_start = new T[v.capacity()];
		//	//memcpy(_start, v._start, sizeof(T)*v.size());
		//	for (size_t i = 0; i < v.size(); ++i)
		//	{
		//		_start[i] = v._start[i];
		//	}

		//	_finish = _start + v.size();
		//	_end_of_storage = _start + v.capacity();
		//}

		~vector()
		{
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}
		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator begin() const
		{
			return _start;
		}
		const_iterator end() const
		{
			return _finish;
		}

		void resize(size_t n, T val = T())
		{
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				if (n > capacity())
					reserve(n);
				while (_finish != _start + n)
				{
					_finish = val;
					_finish++;
				}
			}
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t sz = size();
				T* tmp = new T[n];
				if (_start)
				{
					//memcpy(tmp, _start, size() * sizeof(T));//造成浅拷贝问题
					for (size_t i  = 0; i < size(); i++)
					{
						tmp[i] = _start[i];
					}
					delete[] _start;
					_start = tmp;
				}
				_start = tmp;
				_finish = _start + sz;
				_end_of_storage = _start + n;
			}
		}
		void erase(iterator pos)
		{
			assert(pos >= _start);
			assert(pos <= _finish);
			while (pos != _finish)
			{
				*pos = *(pos + 1);
				pos++;
			}
			--_finish;
		}
		iterator insert(iterator pos, const T& val)
		{
			assert(pos >= _start);
			assert(pos <= _finish);
			if (size() == capacity())
			{
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2); //开内存是异地开，这样会导致迭代器失效(野指针问题)
				pos = _start + len;
			}
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *(end);
				end--;
			}
			*pos = val;
			_finish++;
			return pos;
		}

		void swap(vector<T>& v)
		{
			std::swap(_start,v._start);
			std::swap(_finish,v._finish);
			std::swap(_end_of_storage,v._end_of_storage);
		}
		void push_back(const T& n)
		{
			if (size() == capacity())
			{
				reserve(capacity() == 0 ? 4 : capacity() * 2);
			}

			*_finish = n;
			_finish++;
		}
		void pop_back()
		{
			assert(!empty());
			--_finish;
		}
		bool empty()
		{
			return _start == _finish;
		}
		size_t size()
		{
			return _finish - _start;
		}
		size_t capacity()
		{
			return _end_of_storage - _start;
		}
		T& operator[] (size_t pos)
		{
			assert(pos < size());
			return _start[pos];
		}
		const T& operator[] (size_t pos) const
		{
			assert(pos < size());
			return _start[pos];
		}
		T& front()
		{
			assert(size() > 0);
			return *_start;
		}
		T& back()
		{
			assert(size()>0);
			return *(_finish - 1);
		}
	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;
		iterator _end_of_storage = nullptr;
	};
}


void test1()
{
	wpy::vector<int> v1;
	wpy::vector<std::string> v3(3, "111111111111111111111");
	for (auto e : v3)
	{
		cout << e << endl;
	}
	cout << endl;
	wpy::vector<std::string> v4(v3);
	for (auto e : v3)
	{
		cout << e << endl;
	}
	cout << endl;
}