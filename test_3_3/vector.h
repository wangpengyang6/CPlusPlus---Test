#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<cassert>
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
			__end_of_storage(nullptr)
		{}
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
				if(_start)
				{
					memcpy(tmp, _start, size() * sizeof(T));
					delete[] _start;
					_start = tmp;
				}
				_start = tmp;
				_finish = _start + sz;
				__end_of_storage = _start+n;
			}
		}
		void erase(iterator pos)
		{
			assert(pos >= _start);
			assert(pos <= _finish);
			while (pos != _finish)
			{
				*pos = *(pos+1);
				pos++;
			}
			--_finish;
		}
		iterator insert(iterator pos,const T& val)
		{
			assert(pos >= _start);
			assert(pos <= _finish);
			if (size() == capacity())
			{
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity()*2); //开内存是异地开，这样会导致迭代器失效(野指针问题)
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

		void push_back(const T& n)
		{
			if (size() == capacity())
			{
				reserve(capacity() == 0 ? 4 : capacity()*2);
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
			return __end_of_storage - _start;
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
	private:
		iterator _start;
		iterator _finish;
		iterator __end_of_storage;
	};
}

void test1()
{
	wpy::vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.insert(v1.begin(),666);
	v1.insert(v1.end(),777);
	v1.erase(v1.begin());
	v1.erase(v1.end());
	v1.erase(v1.begin()+2);
	for (int i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << " ";
	}
}