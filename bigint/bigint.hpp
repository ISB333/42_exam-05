#pragma once

#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>

class bigint {
	private:
		std::string num;
	public:
		bigint();
		bigint(std::string str);
		bigint(unsigned int number);
		bigint(const bigint &other);
		bigint& operator=(const bigint &other);
		~bigint();

		std::string getStr() const {return num;}

		bigint operator+(const bigint &value1) const;
		bigint& operator+=(const bigint &value1) ;

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