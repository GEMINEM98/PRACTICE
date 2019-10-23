#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<stdlib.h>
#include<assert.h>
using namespace std;


namespace gly
{
	class string
	{
	public:
		typedef const char* const_iterator;
		typedef char* iterator;

		// 迭代器
		const_iterator begin() const
		{
			return _str;
		}
		const_iterator end() const 
		{
			return _str + _size;
		}
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}

		// 构造函数
		string(const char *str = "")
			:_str(new char[strlen(str)+1])
		{
			strcpy(_str, str);   // 字符串拷贝函数
			_size = strlen(str);
			_capacity = _size;   // _capacity不加1
		}

		// 析构函数
		~string()
		{
			delete[] _str;
			_str = nullptr; // 防止野指针
			_size = 0;
			_capacity = 0;
		}

		// 拷贝构造函数
		string(const string& s)
			:_str(new char[s._size + 1])
			,_size(s._size)
			,_capacity(s._size)
		{
			strcpy(_str, s._str);
		}

		// 赋值  s1=s2
		string& operator=(const string& s)
		{
			if (this != &s)
			{   // 直接新申请一块新空间，再拷贝
				delete[] _str;
				_str = new char[s._size + 1];
				strcpy(_str, s._str);
				_size = s._size;
				_capacity = s._capacity;
			}
			return *this;
		}

		// 返回一个指向正规C字符串的指针
		const char *c_str()
		{
			return _str;
		}

		// 运算符[]重载函数
		char& operator[](size_t pos)
		{
			// 判断pos是否合法
			assert(pos < _size);
			return _str[pos];
		}
		const char& operator[](size_t pos) const 
		{
			assert(pos < _size);
			return _str[pos];
		}

		// 返回string的长度
		size_t size()
		{
			return this->_size;
		}

		// 返回string的容量
		size_t capacity()
		{
			return this->_capacity;
		}

		// reserve --> 开空间
		void reserve(size_t n)
		{
			// 如果空间不足够，申请新空间
			if (n > _capacity) 
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str); // 字符串拷贝
				delete[] _str;     // 释放旧空间
				_str = tmp;
				_capacity = n;
			}
		}

		// 尾插字符
		void push_back(char ch)
		{
			//if (_size == _capacity)
			//{
			//	// 扩容开新的空间，拷贝数据 
			//	// 扩容不一定是增二倍的空间
			//	reserve(_capacity * 2);
			//}

			//_str[_size] = ch;
			//++_size;
			//_str[_size] = '\0';

			insert(_size, ch);
		}

		// 尾插字符串
		void append(const char* str)
		{
			//size_t len = strlen(str);
			//if (_size + len > _capacity)
			//{
			//	// 扩容
			//	reserve(_size + len);
			//}

			//strcpy(_str + _size, str);
			//_size += len;

			insert(_size, str);
		}

		// 运算符+=重载函数（加字符）
		const string& operator+=(char ch)
		{
			this->push_back(ch);
			return *this;
		}

		// 运算符+=重载函数（加字符串）
		const string& operator+=(const char *str)
		{
			this->append(str);
			return *this;
		}

		// 运算符+=重载函数（加string）
		const string& operator+=(const string& s)
		{
			this->append(s._str);
			return *this;
		}

		// 插入字符
		void insert(size_t pos, char ch)
		{
			assert(pos <= _size);
			if (_size == _capacity)
			{
				reserve(_capacity * 2); // 开空间
			}

			int end = _size;  // 循环将元素都往后挪
			while (end >= (int)pos)
			{
				_str[end + 1] = _str[end];
				--end;
			}

			_str[pos] = ch;
			++_size;// 注意在调用一次insert后需要将size更新，不然\n会被覆盖掉了，从而出现越界情况

		}
		// 插入字符串
		void insert(size_t pos, const char* str)
		{
			//先判断现有空间是否足够
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			int end = _size;
			while (end >= (int)pos)
			{
				_str[len + end] = _str[len];
				--end;
			}
			// 把字符串循环放进_str中
			while (*str != '\0')
			{
				_str[pos] = *str++;
				++pos;
			}
			_size += len; // 更新size
		}

		// 运算符>重载函数
		//s1 > s2
		bool operator>(const string& s)const
		{
			const char* str1 = _str;
			const char* str2 = s._str;

			while (*str1 && *str2)
			{
				// 循环比较*str1和*str2的ASCII码，ASCII码大的字符串大
				if (*str1 > *str2)
				{
					return true;
				}
				else if (*str1 < *str2)
				{
					return false;
				}
				else
				{
					++str1;
					++str2;
				}
			}
			// 前面全部相等
			if (*str1 != '\0')
				return true;
			else return false;
		}

		// 运算符==重载函数
		// s1==s2
		bool operator==(const string s)const
		{
			// 循环判断
			int j = 0;
			for (j = 0; j < _size; ++j)
			{
				if (_str[j] != s._str[j])
					break;
			}

			if (j == _size && s._str[j] == '\0')
			{
				return true;
			}
			else return false;
		}

		// 运算符>=重载函数  
		// s1>=s2
		bool operator>=(const string& s)const
		{
			return (*this > s) || (*this == s);
		}

		// 运算符<重载函数
		// s1 < s2
		bool operator<(const string& s)const
		{
			return !(*this >= s);

			//const char* str1 = _str;
			//const char* str2 = s._str;

			//while (*str1 && *str2)
			//{
			//	if (*str1 < *str2)
			//	{
			//		return true;
			//	}
			//	else if (*str1 > *str2)
			//	{
			//		return false;
			//	}
			//	else
			//	{
			//		++str1;
			//		++str2;
			//	}
			//}
			//// 前面全部相等
			//if (*str1 != '\0')
			//	return true;
			//else return false;

		}

		// 运算符<=重载函数
		// s1 <= s2
		bool operator<=(const string& s)const
		{
			//return (*this < s) || (*this == s);
			return !(*this > s);
		}

		// 查找字符ch
		size_t find(char ch)
		{
			// 循环查找
			for (int i = 0; i < _size; ++i)
			{
				if (_str[i] == ch)
					return i;
			}
			return -1;
		}

		// 查找字符串
		size_t find(const char* str, size_t pos)const
		{
			// strstr(s1,s2)函数返回s2第一次在s1中的位置，如果没有找到，返回NULL
			char* tmp = strstr(_str + pos, str);
			if (!tmp)
			{   // 没有找到
				return -1;
			}
			return tmp - _str;
		}

		// 运算符+重载函数 （加字符）
		// s1+ch
		string operator+ (char ch)const
		{
			string tmp(*this);
			tmp += ch;
			return tmp;
		}

		// 运算符+重载函数 （加字符串）
		// s1+ *str
		string operator+(const char* str)const
		{
			string tmp(*this);
			tmp += str; // 上面有重载的+=函数
			return tmp;
		}
		/*string operator+(char* str)
		{
			string tmp(*this);
			tmp.append(str);
			return tmp;
		}*/



		friend ostream& operator<<(ostream& _cout, const string& s);
		friend istream& operator>>(istream& _cin, string& s);
		//friend istream& getline(istream& _cin, string& str, char ch);


	private:
		char* _str;
		size_t _size;
		size_t _capacity;

	};


	// 重载 >>、<< 运算符函数
	ostream& operator<<(ostream& _cout, const string& s)
	{
		for (size_t i = 0; i < s._size; ++i)
		{
			_cout << s[i];
		}
		_cout << endl;
		return _cout;
	}
	istream& operator>>(istream& _cin, string& s)
	{
		_cin >> s._size;
		return _cin;
	}


	//istream& getline(istream& _cin, string& str)
	//{
	//	char ch;
	//	for (int i = 0; i < str.size(); ++i)
	//	{
	//		if ((ch = getchar()) != EOF)
	//		{
	//			str[i] = ch;
	//		}
	//		if (ch == EOF)
	//		{
	//			break;
	//		}
	//	}
	//	
	//	return _cin;
	//}

}

void test()
{
	gly::string s1("zhello");
	cout << s1.capacity() << endl;
	s1 += "world";
	cout << s1.capacity() << endl;
	s1 += '!';
	cout << s1.capacity() << endl;

	gly::string s2("helloworld!");
	s2.insert(5, ' ');
	cout << s2.c_str() << endl;
	s2.insert(0, '*');
	cout << s2.c_str() << endl;

	cout << s1 << endl;
	cout << s2 << endl;
	cout << (s1 > s2) << endl;
	cout << (s1 == s2) << endl;
	cout << (s1 < s2) << endl;
	cout << (s1 <= s2) << endl;	

	//gly::string s3;
	//getline(cin, s3);
	//cout << "****************" << endl;
	//cout << s3 << endl;
	//cout << "****************" << endl;

	
}

int main()
{
	test();
	system("pause");
	return 0;
}
