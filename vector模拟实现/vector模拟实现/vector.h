#pragma once

#include<iostream>
#include<stdlib.h>
#include<vector>
#include<assert.h>

using namespace std;


namespace gly
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;

		// 构造函数
		vector()
			:_start(nullptr)
			,_finish(nullptr)
			,_end_of_storage(nullptr)
		{}


		// 拷贝构造函数
		vector(const vector<T>& v)
		{
			_start = new T[v.size()];
			memcpy(_start, v._start, sizeof(T)*v.size());
			_finish = _start + v.size();
			_end_of_storage = _start + v.size();
		}


		// 交换函数
		// v1.swap(v2);  直接交换三个指针
		void swap(vector<T>& v)
		{
			swap(_start, v._start);
			swap(_finish, v._finish);
			swap(_end_of_storage, v._end_of_storage);
		}


		// 赋值函数
		// v1=v2
		vector<T>& operator=(vector<T> v)
		{
			//swap(_start, v._start);
			//swap(_finish, v._finish);
			//swap(_end_of_storage, v._end_of_storage);

			swap(v);
			return *this;
		}


		// 析构函数
		~vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = nullptr;
				_finish = nullptr;
				_end_of_storage = nullptr;
			}
		}


		// 迭代器
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}


		// reserve --> 开空间
		void reserve(size_t n) 
		{
			if (n > capacity())
			{
				size_t sz = size(); // 先保存原始空间大小
				T* tmp = new T[n];  // 开辟新空间
				if (_start)
				{                   // 拷贝数据
					memcpy(tmp, _start, sizeof(T)*sz);
					delete[] _start;
				}

				// 更新指针位置
				_start = tmp;
				_finish = _start + sz;
				_end_of_storage = _start + n;

			}
		}

		// resize --> 开空间 + 初始化
		void resize(size_t n, const T& val = T()) 
		{
			if (n < size())         // 有足够空间
			{
				_finish = _start + n;
				return;
			}
			if (n > capacity)       // 重新开辟新空间
				reserve(n);

			// 此时空间已经足够，进行初始化
			while (_finish != _start + n) 
			{
				*_finish = val;
				++_finish;
			}
		}


		// 在pos位置插入
		void insert(iterator pos, const T& x)
		{
			// 判断pos是否合法
			assert(pos >= _start && pos <= _finish);
			
			// 如果申请的空间已满，就要增容
			if (_finish == _end_of_storage)
			{   // 画图理解
				size_t n = pos - _start;   // 记录插入位置
				size_t newcapacity = capacity() == 0 ? 2 : (capacity() * 2);
				reserve(newcapacity); // 开空间
				pos = _start + n;     // 更新插入位置
			}

			//此时空间足够
			iterator end = _finish - 1; // end指向移位元素
			while (end >= pos)   // 挪动数据
			{
				*(end + 1) = *end;
				--end;
			}

			*pos = x;  // 插入x
			++_finish; // 不能忘记更新_finish
		}
	

		// 尾插
		void push_back(const T& x)
		{
			////如果空间不足，开新空间
			//if (_finish == _end_of_storage)
			//{
			//	size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
			//	reserve(newcapacity);// 开空间，不初始化
			//}
			//
			////此时空间足够
			//*_finish = x;
			//++_finish;

			insert(end(), x);
		}


		// 尾删
		void pop_back()
		{
			assert(_finish > _start);
			--_finish;


		}


		// 删除pos位置元素
		void erase(iterator pos)
		{
			// 判断pos是否合法
			assert(pos < _finish&&pos >= _start);
			// 将pos位置后面的数往前挪动一位
			iterator begin = pos + 1;
			while (begin < _finish)
			{
				*(begin - 1) = *begin;
				++begin;
			}
			--_finish; // 最后还要更新_finish
		}

		// 有效元素的长度
		size_t size()const
		{
			return _finish - _start;
		}

		// 申请的容量
		size_t capacity()const
		{
			return _end_of_storage - _start;
		}

		// 运算符[]重载函数
		T& operator[](size_t pos)
		{
			return _start[pos];
		}

		const T& operator[](size_t pos)const
		{
			return _start[pos];
		}


	private:
		/*T* _a;
		size_t _size;
		size_t _capacity;*/

		iterator _start;
		iterator _finish;
		iterator _end_of_storage;

	};

	template<class T>
	void print(const vector<T>& v)
	{
		for (size_t i = 0; i < v.size(); ++i)
		{
			cout << v[i] << " ";
		}
		cout << endl;
	}


	void test()
	{
		vector<int> v;

		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		print(v);

		v.pop_back();
		print(v);

		v.erase(&v[2]);
		print(v);

		v.insert(&v[0], 0);
		print(v);

	}

}