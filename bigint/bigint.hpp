#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

class bigint {
	private:
		std::string num;
	public:
		bigint();
		bigint(std::string str);
		bigint(unsigned int number);
		bigint(const bigint &src);
		bigint& operator=(const bigint &src);
		~bigint();

		std::string getStr() const {return num;}

		bigint operator+(const bigint &src) const;
		bigint& operator+=(const bigint &src) ;

		bigint& operator++();
		bigint operator++(int) ;

		bigint operator>>(unsigned int n) const;
		bigint operator<<(unsigned int n) const;
		bigint& operator>>=(unsigned int n);
		bigint& operator<<=(unsigned int n);

		bigint operator>>(const bigint &src) const;
		bigint operator<<(const bigint &src) const;
		bigint& operator>>=(const bigint &src);
		bigint& operator<<=(const bigint &src);

		bool operator>(const bigint &src) const;
		bool operator<(const bigint &src) const;
		bool operator>=(const bigint &src) const;
		bool operator<=(const bigint &src) const;
		bool operator==(const bigint &src) const;
		bool operator!=(const bigint &src) const;
};

std::ostream& operator<<(std::ostream &os, const bigint &src);