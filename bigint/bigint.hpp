#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;

class bigint {
	private:
		string num;
	public:
		bigint();
		bigint(unsigned int n);
		bigint(string str);
		bigint(const bigint &src);
		bigint& operator=(const bigint &src);
		~bigint();

		string getStr() const {return num;}

		bigint operator+(const bigint &src) const;
		bigint& operator+=(const bigint &src);

		bigint& operator++();
		bigint operator++(int);

		bigint operator<<(unsigned int n) const;
		bigint& operator<<=(unsigned int n);
		bigint operator>>(unsigned int n) const;
		bigint& operator>>=(unsigned int n);

		bigint operator<<(const bigint &src) const;
		bigint& operator<<=(const bigint &src);
		bigint operator>>(const bigint &src) const;
		bigint& operator>>=(const bigint &src);

		bool operator<(const bigint &src) const;
		bool operator<=(const bigint &src) const;
		bool operator>(const bigint &src) const;
		bool operator>=(const bigint &src) const;
		bool operator==(const bigint &src) const;
		bool operator!=(const bigint &src) const;
};

ostream& operator<<(ostream &os, const bigint &src);
