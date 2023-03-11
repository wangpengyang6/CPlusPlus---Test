#pragma once

namespace wpy
{
	template<class T,class Container = deque<T>>
	class stack
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
		}
		bool empty()
		{
			return _con.empty();
		}
		const T& top()
		{
			return _con.back();
		}
		void pop()
		{
			_con.pop_back();
		}
		size_t size()
		{
			return _con.size();
		}
	private:
		Container _con;
	};
}

void test1()
{
	wpy::stack<int> k;
	k.push(1);
	k.push(2);
	k.push(3);
	k.push(4);
	while (!k.empty())
	{
		cout << k.top() << ' ';
		k.pop();
	}
}