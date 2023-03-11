#define _CRT_SECURE_NO_WARNINGS 1
#include"string.h"
int main()
{
	try
	{
		test2();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
	test3();
	return 0;
}