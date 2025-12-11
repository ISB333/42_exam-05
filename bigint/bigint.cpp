#include "bigint.hpp"

using namespace std;

bigint::bigint() : num("0") {}
bigint::bigint(string str) : num(str) {}
bigint::bigint(unsigned int n) {
	stringstream ss;
	ss << n;
	num = ss.str();
}
bigint::bigint(const bigint &src) {*this = src;}
bigint& bigint::operator=(const bigint &src) {
	if (this != &src)
		num = src.num;
	return *this;
}
bigint::~bigint() {}

ostream& operator<<(ostream &os, const bigint &src) {
	os << src.getStr();
	return os;
}

bigint bigint::operator+(const bigint &src) const {
	string A = num;
	string B = src.getStr();
	string res;

	int carry = 0;
	int i = A.size() - 1;
	int j = B.size() - 1;
	while (i >= 0 || j >= 0 || carry > 0) {
		int digitA = 0;
		int digitB = 0;
		if  (i >= 0)
			digitA = A[i] - '0';
		if  (j >= 0)
			digitB = B[j] - '0';
		int sum = digitA + digitB + carry;
		int outDigit = sum % 10;
		carry = sum / 10;
		res.push_back(char(outDigit + '0'));
		i--;
		j--;
	}
	reverse(res.begin(), res.end());
	return bigint(res);
}

bigint& bigint::operator+=(const bigint &src) {
	*this = *this + src;
	return *this;
}

bigint& bigint::operator++() {
	*this = *this + bigint("1");
	return *this;
}

bigint bigint::operator++(int) {
	bigint tmp = *this;
	*this = *this + bigint("1");
	return tmp;
}

bigint bigint::operator<<(unsigned int n) const {
	bigint tmp = *this;
	while (n--)
		tmp.num.push_back('0');
	return tmp;	
}

bigint& bigint::operator<<=(unsigned int n) {
	while (n--)
		num.push_back('0');
	return *this;	
}

bigint bigint::operator>>(unsigned int n) const {
	bigint tmp = *this;
	while (n-- && !tmp.num.empty())
		tmp.num.erase(tmp.num.size() - 1, 1);
	return tmp;	
}

bigint& bigint::operator>>=(unsigned int n) {
	while (n-- && !num.empty())
		num.erase(num.size() - 1, 1);
	return *this;	
}

bigint bigint::operator<<(const bigint &src) const {
	stringstream ss(src.getStr());
	unsigned int n;
	ss >> n;
	bigint tmp = *this;
	while (n--)
		tmp.num.push_back('0');
	return tmp;	
}

bigint& bigint::operator<<=(const bigint &src) {
	stringstream ss(src.getStr());
	unsigned int n;
	ss >> n;
	while (n--)
		num.push_back('0');
	return *this;	
}

bigint bigint::operator>>(const bigint &src) const {
	stringstream ss(src.getStr());
	unsigned int n;
	ss >> n;
	bigint tmp = *this;
	while (n-- && !tmp.num.empty())
		tmp.num.erase(tmp.num.size() - 1, 1);
	return tmp;	
}

bigint& bigint::operator>>=(const bigint &src) {
	stringstream ss(src.getStr());
	unsigned int n;
	ss >> n;
	while (n-- && !num.empty())
		num.erase(num.size() - 1, 1);
	return *this;	
}

bool bigint::operator>(const bigint &src) const {
	if (num.size() != src.getStr().size())
		return num.size() > src.getStr().size();
	return num > src.getStr();
}

bool bigint::operator>=(const bigint &src) const {
	return (*this > src) || (*this == src);
}

bool bigint::operator<(const bigint &src) const {
	if (num.size() != src.getStr().size())
		return num.size() < src.getStr().size();
	return num < src.getStr();
}

bool bigint::operator<=(const bigint &src) const {
	return (*this < src) || (*this == src);
}

bool bigint::operator==(const bigint &src) const {
	return num == src.getStr();
}

bool bigint::operator!=(const bigint &src) const {
	return num != src.getStr();	
}
