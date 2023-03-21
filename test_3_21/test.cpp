#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<array>
#include<unordered_map>
#include<map>
#include<set>
#include<queue>
#include<functional>
#include<cctype>

using namespace std;
int x[4] = { 0,-1,0,1 }, y[4] = { 1,0,-1,0 };
const int N = 100010;
int a[N];

class Date
{
public:
	bool operator< (const Date& d) const
	{
		return _year < d._year
			|| (_year == d._year && _month < d._month)
			|| (_year == d._year && _month == d._month && _day < d._day);
	}
private:
	int _year;
	int _month;
	int _day;
};

template<class T>
struct Less
{
	bool operator() (const T& x, const T& y)
	{
		return x < y;
	}
};

//偏特化
template<class T>
class Less<T*>
{
	bool operator() (const T* x, const T* y)
	{
		return *x < *y;
	}
};

//全特化 
template<>
struct Less<Date*>
{
	bool operator() (const Date* x, const Date* y) const
	{
		return *x < *y;
	}
};

template<class T1, class T2>
class Data
{
public:
	Data()
	{
		cout << "Data<T1,T2>" << endl;
	}
private:
	T1 _x;
	T2 _y;
};

template<>
class Data<int, char>
{
public:
	Data()
	{
		cout << "Data<int,char>" << endl;
	}
private:
	int _x = int();
	char _y = char();
};

template<class T>
class Data<T, int>
{
public:
	Data()
	{
		cout << "Data<T,int>" << endl;
	}
private:
	T _x = T();
	int _y = int();
};

int main()
{
	Data<int, double> s1;
	Data<int, char>s2;
	Data<char, int>s3;
	return 0;
}
