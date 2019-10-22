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

		vector()
			:_start(nullptr)
			,_finish(nullptr)
			,_end_of_storage(nullptr)
		{}

		vector(const vector<T>& v)  // 拷贝构造
		{
			_start = new T[v.size()];
			memcpy(_start, v._start, sizeof(T)*v.size());
			_finish = _start + v.size();
			_end_of_storage = _start + v.size();
		}

		// v1=v2
		vector<T>& operator=(vector<T> v)
		{
			//swap(_start, v._start);
			//swap(_finish, v._finish);
			//swap(_end_of_storage, v._end_of_storage);

			this->swap(v);
			swap(v);
			return *this;
		}



		~vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _finish = _end_of_storage = nullptr;
			}
		}

		// v1.swap(v2);  直接交换三个指针
		void swap(vector<T>& v)
		{
			swap(_start, v._start);
			swap(_finish, v._finish);
			swap(_end_of_storage, v._end_of_storage);

		}



		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}


		void resize(size_t n, const T& val = T()) // 开空间 初始化
		{
			if (n < size())
			{
				_finish = _start + n;
				return;
			}
			if (n > capacity)
			{
				reserve(n);
			}
			// 此时空间已经足够
			while (_finish != _start + n)
			{
				*_finish = val;
				++_finish;
			}
			
		}

		void reserve(size_t n) // 开空间
		{
			if (n > capacity())
			{
				size_t sz = size();
				T* tmp = new T[n];
				if (_start)
				{
					memcpy(tmp, _start, sizeof(T)*sz);
					delete[] _start;
				}


				_start = tmp;
				_finish = _start + sz;
				_end_of_storage = _start + n;

			}
		}


		void push_back(const T& x)
		{
			//if (_finish == _end_of_storage)
			//{
			//	size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
			//	reserve(newcapacity);// 只开空间，不初始化
			//}

			////此时空间足够
			//*_finish = x;
			//++_finish;

			insert(end(), x);

		}
		void pop_back()
		{
			/*assert(_finish > _start);
			--_finish;*/

			erase(--end());
		}

		void insert(iterator pos, const T& x)
		{
			assert(pos >= _start && pos <= _finish);
			if (_finish == _end_of_storage)
			{
				size_t n = pos - _start;   // 画图理解
				size_t newcapacity = capacity() == 0 ? 2 : (capacity() * 2);
				reserve(newcapacity);
				pos = _start + n;
			}

			//此时空间足够
			iterator end = _finish - 1;
			while (end >= pos)   // 挪动数据
			{
				*(end + 1) = *end;
				--end;
			}

			*pos = x;
			++_finish;
		}

		void erase(iterator pos)
		{
			assert(pos < _finish&&pos >= _start);
			iterator begin = pos + 1;
			while (begin < _finish)
			{
				*(begin - 1) = *begin;
				++begin;
			}
			--_finish;
		}

		size_t size()const
		{
			return _finish - _start;
		}

		size_t capacity()const
		{
			return _end_of_storage - _start;
		}

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


	void test_vector1()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		auto it = v.begin();
		v.insert(it, 0);

		for (size_t i = 0; i < v.size(); ++i)
		{
			cout << v[i] << " ";
		}
		cout << endl;

		it = v.begin();
		v.erase(it);

		for (size_t i = 0; i < v.size(); ++i)
		{
			cout << v[i] << " ";
		}
		cout << endl;

		vector<int>::iterator iter = v.begin();
		while (iter != v.end())
		{
			cout << *iter << " ";
			++iter;
		}
		cout << endl;

		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;
	}


	void test_vector2()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
	
		vector<int> copy(v);
		for (auto e : copy)
		{
			cout << e << " ";
		}
		cout << endl;
	
	
	}
}