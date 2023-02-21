#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
using namespace std;

class Date
{
    friend ostream& operator<< (ostream& out, const Date& A);
    friend istream& operator>> (istream& in,  Date& A);
public:
    Date(int year = 0,int month = 0,int day = 0)
        :_year(year),_month(month),_day(day)
    {
    }
private:
    int _year;
    int _month;
    int _day;
};

ostream& operator<< (ostream& out, const Date& A)
{
    out << A._year << '.' << A._month << '.' << A._day << endl;
    return out;
}
istream& operator>> (istream& in, Date& A)
{
    in >> A._year >> A._month >> A._day;
    return in;
}

void Fun1(const string s1) //const ������
{
    string::const_iterator cit = s1.begin();
    //string::const_reverse_iterator crit = s1.rbegin();   const ���������
    while (cit != s1.end())
    {
        cout << *cit;
        cit++;
    }
}

void Test1()
{
    string s1("Hello World");
    //���������
    string::iterator it = s1.begin();
    while (it != s1.end())
    {
        cout << *it;
        it++;
    }
    cout << endl;
    //���������
    string::reverse_iterator rit = s1.rbegin();
    while (rit != s1.rend())
    {
        cout << *rit;
        rit++;
    }
    cout << endl;
    //Fun1(s1);
    try
    {
        s1.at(100);
    }
    catch(const exception& e)
    {
        cout << e.what() << endl;
    }
}

void Test2()
{
    string s1("World");
    try
    {
        s1.erase(2,100); //���쳣
    }
    catch(const exception& e) //�������쳣״̬
    {
        cout << e.what() << endl;
    }
    cout << s1 << endl;
    cout << s1.c_str() << endl;
}

int main()
{
    Date d1(2023, 2, 21);
    Date d2;
    cout << d1 << endl;
    string s1("Hello World");
    auto pos = s1.find_first_of("lo");
    while (pos != string::npos)
    {
        s1[pos] = '*';
        pos = s1.find_first_of("lo");
    }
    cout << s1 << endl;
    auto s2 = s1.substr(5,2);
    cout << s2 << endl;
    cin >> d2;
    cout << d2 << endl;

    return 0;
}