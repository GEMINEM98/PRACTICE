#define _CRT_SECURE_NO_WARNINGS 1

#include"List.h"

using namespace std;

void test_list1()
{
	list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(2);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(2);
	l.push_back(0);

	l.sort();   // 要去重的话，最好先排序，再去重！
	l.unique(); // 去掉重复元素，但相同元素必须是连续的

	// 去重算法：
	//           开空间：
	//           先排序，定义两个指针，再开一块空间，两个指针一前一后一起走，
	//           检验两个指针所指向的内容是否相等，相等就往后挪，不相等就放进新空间。
	//
	//           不开空间：
	//           先排序，定义三个指针，两个指针一前一后一起走，另一个指针不走，
	//           两个指针如果不相等，则前面的指针指向的元素放进第三个指针指向的位置，两个指针往后挪
	//           两个指针如果相等，就继续往后挪，第三个指针不变。
	           
	list<int>::iterator it = l.begin();
	while (it != l.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

void test_list2()
{
	list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);

	list<int>::iterator pos = find(l.begin(), l.end(), 3);

	//l.insert(pos, 30); // insert在string和vector中失效；在list中不失效
	//*pos = 300;
	//cout << *pos << endl;

	//l.erase(pos);  // erase在string、vector、list中都失效
	//*pos = 300;

	for (auto e : l)
	{
		cout << e << " ";
	}
	cout << endl;
}

int main()
{
	//test_list2();
	//gly::test();
	//gly::test1();
	gly::test2();

	system("pause");
	return  0;
}