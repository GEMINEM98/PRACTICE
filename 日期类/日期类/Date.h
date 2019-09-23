#pragma once

#include<iostream>
using namespace std;

class Date
{
public:
	int GetMonthDay(int year, int month)  // 获取当前日期月份的天数
	{
		static int monthDays[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0 )))
		{
			return 29;
		}
		else
		{
			return monthDays[month];
		}
	}

	// Date d1(2018, 2, 29);
	Date(int year = 1900, int month = 1, int day = 1)  // 构造函数
	{
		_year = year;
		_month = month;
		_day = day;

		if (year < 0
			|| month < 1 || month > 12
			|| day < 1 || day > GetMonthDay(year, month))
		{
			printf("日期非法！\n");
		}
	}

	Date(const Date& d)  // 拷贝构造函数
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	Date& operator=(const Date& d)  // 重载赋值运算符
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}

	~Date()  // 析构函数
	{}

	bool operator<(const Date& d)     // 重载<运算符
	{
		if (this->_year == d._year)
		{
			if (this->_month == d._month)
			{
				if (this->_day < d._day)
				{
					return true;
				}
				else return false;
			}
			else if (this->_month < d._month)
			{
				return true;
			}
			else return false;
		}
		else if (this->_year < d._year)
		{
			return true;
		}
		else return false;
	}

	bool operator>(const Date& d)    // 重载>运算符
	{
		if (this->_year == d._year)
		{
			if (this->_month == d._month)
			{
				if (this->_day > d._day)
				{
					return true;
				}
				else return false;
			}
			else if (this->_month > d._month)
			{
				return true;
			}
			else return false;
		}
		else if (this->_year > d._year)
		{
			return true;
		}
		else return false;
	}

	bool operator<=(const Date& d)    // 重载<=运算符
	{
		if (this->_year == d._year)
		{
			if (this->_month == d._month)
			{
				if (this->_day <= d._day)
				{
					return true;
				}
				else return false;
			}
			else if (this->_month <= d._month)
			{
				return true;
			}
			else return false;
		}
		else if (this->_year <= d._year)
		{
			return true;
		}
		else return false;
	}

	bool operator>=(const Date& d)    // 重载>=运算符
	{
		if (this->_year == d._year)
		{
			if (this->_month == d._month)
			{
				if (this->_day >= d._day)
				{
					return true;
				}
				else return false;
			}
			else if (this->_month >= d._month)
			{
				return true;
			}
			else return false;
		}
		else if (this->_year >= d._year)
		{
			return true;
		}
		else return false;
	}

	bool operator==(const Date& d)    // 重载==运算符
	{
		if (this->_year == d._year && this->_month == d._month && this->_day == d._day)
		{
			return true;
		}
		else return false;
	}

	bool operator!=(const Date& d)    // 重载!=运算符
	{
		if (this->_year != d._year || this->_month != d._month || this->_day != d._day)
		{
			return true;
		}
		else return false;
	}


	Date operator+(int day)    // 重载+运算符（只加一个天数，而原来的*this指针的值并没有变）
	{
		Date tmp(*this);
		if (day < 0)
		{
			tmp = tmp - (0 - day);
		}
		else
		{
			tmp._day += day;
			while (tmp._day > GetMonthDay(tmp._year, tmp._month))
			{
				tmp._day -= GetMonthDay(tmp._year, tmp._month);
				++tmp._month;

				if (tmp._month == 13)
				{
					++tmp._year;
					tmp._month = 1;
				}
			}
		}
		return tmp;
	}

	Date operator-(int day)    // 重载-运算符（只减一个天数，而原来的*this指针的值并没有变）
	{
		Date tmp(*this);
		if (day < 0)
		{
			tmp = tmp + (0 - day);
		}
		else
		{
			tmp._day -= day;
			while (tmp._day <= 0)
			{
				if (tmp._month > 0 && tmp._month < 13)
				{
					--tmp._month;
					if (tmp._month == 0)
					{
						--tmp._year;
						tmp._month = 12;
					}
					tmp._day += GetMonthDay(tmp._year, tmp._month);
				}
			}
		}
		return tmp;
	}


	Date operator+=(int day)    // 重载+=运算符（加一个天数，原来的*this指针的值改变）
	{
		*this = *this + day;
		return *this;
	}

	Date operator-=(int day)    // 重载-=运算符（减一个天数，原来的*this指针的值改变）
	{
		*this = *this - day;
		return *this;
	}


	int operator-(const Date& d)// 重载-运算符（减一个日期）
	{
		Date max = d;
		Date min = *this;
		int count = 0;

		(*this > d) ? (max = *this, min = d) : (max = d, min = *this);

		while (min != max)
		{
			min += 1;
			++count;
		}
		return count;
	}


	// ++d d.operator++(&d)
	Date operator++()
	{
		*this += 1;
		return *this;
	}

	// d++ d.operator++(&d, 0)
	Date operator++(int)
	{
		Date tmp(*this);
		*this += 1;
		return tmp;
	}

	// --d d.operator--(&d)
	Date operator--()
	{
		*this -= 1;
		return *this;
	}

	// d-- d.operator--(&d, 0)
	Date operator--(int)
	{
		Date tmp(*this);
		*this -= 1;
		return tmp;
	}

	void print()
	{
		cout << this->_year << "/" << this->_month << "/" << this->_day << endl;
	}

private:
	int _year;
	int _month;
	int _day;
};

void test()
{
	Date d1(2019, 9, 22);
	Date d2;
	d2 = d1;
	d2.print();

	Date d3(2018, 9, 22);
	printf("%d\n", d3.operator>(d2));
	printf("%d\n", d3.operator>=(d2));
	printf("%d\n", d3.operator<(d2));
	printf("%d\n", d3.operator<=(d2));
	printf("%d\n", d3.operator==(d2));
	printf("%d\n", d3.operator!=(d2));

	d3.print();

	d3 + 70;
	d3.print();

	d3 += 70;
	d3.print();

	d3 - 70;
	d3.print();

	d3 -= 70;
	d3.print();

	Date d4(2019, 12, 30);
	Date d5(1920, 2, 28);
	printf("%d\n", d4 - d5);

	Date d6(1966, 4, 30);
	(d6++).print();
	d6.print();
	(++d6).print();

	Date d7(2012, 8, 8);
	(d7--).print();
	d7.print();
	(--d7).print();

}