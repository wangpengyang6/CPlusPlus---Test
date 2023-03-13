#pragma once
namespace wpy
{
	template<class T,class Container = deque<T>>
	class list
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
		}

		void pop()
		{
			_con.pop_front();
		}

		const T& front()
		{
			return _con.front();
		}

		const T& back()
		{
			return _con.back();
		}

		size_t size()
		{
			return _con.size();
		}

		bool empty()
		{
			return _con.empty();
		}
	private:
		Container _con;
	};
}

void test1()
{
	wpy::list<int> l;
	l.push(1);
	l.push(2);
	l.push(3);
	l.push(4);
	cout << l.size() << endl;
	while(!l.empty())
	{
		cout << l.front()<<' ';
		l.pop();
	}
	cout << endl;
	cout << l.size() << endl;
}