#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;
#include"BSTree.h"
void Test1()
{
    BSTree<int> t1;
    int a[] = {8,3,1,10,6,4,7,14,13};
    for(auto e : a)
        t1.insert(e);
    t1.InOrder();
    cout<<endl;
//    for(auto e : a)
//    {
//        t1.erase(e);
//        t1.InOrder();
//        cout<<endl;
//    }
//    t1.erase(14);
//    t1.erase(13);
//    t1.erase(10);
//    t1.erase(8);
//    t1.InOrder();
//    cout<<endl;
}

void Test2()
{
    BSTree<int> t1;
    int a[] = {8,3,1,10,6,4,7,14,13};
    for(auto e : a)
        t1.insert(e);
    BSTree<int> t2(t1);
    t1.InOrder();
    cout<<endl;
    t2.InOrder();
}
int main()
{
    //Test1();
    Test2();
    return 0;
}