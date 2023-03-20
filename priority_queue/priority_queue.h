#pragma once
namespace wpy
{
	template<class T>
	struct greater
	{
		bool operator()(const T& x,const T& y)
		{
			return x > y;
		}
	};
	
	template<class T>
	struct less
	{
		bool operator()(const T& x, const T& y)
		{
			return x < y;
		}
	};

	template<class T,class Container = vector<T>,class compare = less<T>>
	class priority_queue
	{
	public:
		compare com;
		void adjust_up(int child)//向上调整
		{
			int parent = (child-1)/2;
			while (child > 0)
			{
				//if (_con[child] > _con[parent])
				if (com(_con[parent], _con[child]))
				{
					swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
					break;
			}

		}
		void adjust_down(int parent)//向下调整
		{
			int child = parent * 2 + 1;
			while (child < size())
			{
				if(child + 1 < size() && com(_con[child],_con[child + 1]))
					child++;
				if (com(_con[parent], _con[child]))
				{
					swap(_con[child], _con[parent]);	
					parent = child;
					child = parent * 2 + 1;
				}
				else
					break;
			}
		}
		void push(const T& x)
		{
			_con.push_back(x);
			adjust_up(size()-1);
		}
		void pop()
		{
			swap(_con[0],_con[size()-1]);
			_con.pop_back();
			adjust_down(0);
		}
		const T& top()
		{
			return _con[0];
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

void test()
{
	//wpy::priority_queue<int> q;
	//q.push(1);
	//q.push(0);
	//q.push(2);
	//q.push(5);
	//q.push(5);
	//q.push(7);
	//while (!q.empty())
	//{
	//	cout << q.top() <<' ';
	//	q.pop();
	//}

	wpy::priority_queue<int,vector<int>,greater<int>> q;
	q.push(1);
	q.push(0);
	q.push(2);
	q.push(5);
	q.push(5);
	q.push(7);
	while (!q.empty())
	{
		cout << q.top() << ' ';
		q.pop();
	}
}