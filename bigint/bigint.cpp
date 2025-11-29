#include "bigint.hpp"

bigint::bigint() : num("") {}
bigint::bigint(std::string str) : num(str) {}
bigint::bigint(unsigned int number) {
    std::stringstream ss;
    ss << number;
    num = ss.str();
}
bigint::bigint(const bigint &src) { *this = src; }
bigint& bigint::operator=(const bigint &src) {
    if (this != &src)
        num = src.num;
    return *this;
}
bigint::~bigint() {}

std::ostream& operator<<(std::ostream &os, const bigint &src) {
    os << src.getStr();
    return os;
}

bigint bigint::operator+(const bigint &src) const {
   const std::string &A = num; 
   const std::string &B = src.getStr(); 

    std::string res;

    int i = (int)A.size() - 1;
    int j = (int)B.size() - 1;
    int carry = 0;

    while (i >= 0 || j >= 0 || carry > 0)
    {
        int digitA = 0;
        if (i >= 0)
            digitA = A[i] - '0';

        int digitB = 0;
        if (j >= 0)
            digitB = B[j] - '0';

        int sum = digitA + digitB + carry;
        int out_digit = sum % 10;
        carry = sum / 10;

        res.push_back(char('0' + out_digit));

        i--;
        j--;
    }
    std::reverse(res.begin(), res.end());

    return bigint(res);
}

bigint& bigint::operator+=(const bigint &src) {
    *this = *this + src;
    return *this;
}

bigint& bigint::operator++() {
    *this += bigint("1");
    return *this;
}

bigint bigint::operator++(int) {
    bigint tmp = *this;
    *this += bigint("1");
    return tmp;
}

bigint bigint::operator<<(unsigned int n) const {
    bigint res = *this;
    while (n--)
        res.num.push_back('0');
    return (res);
}

bigint bigint::operator>>(unsigned int n) const {
    bigint res = *this;
    while (n-- && !res.num.empty())
        res.num.erase(res.num.size() - 1, 1);
    return (res);
}

bigint& bigint::operator<<=(unsigned int n) {
    *this = *this << n;
    return *this;
}

bigint& bigint::operator>>=(unsigned int n) {
    *this = *this >> n;
    return *this;
}

bigint bigint::operator<<(const bigint &src) const {
    std::stringstream ss(src.num);
    unsigned int n;
    ss >> n;
    bigint res = *this;
    while (n--)
        res.num.push_back('0');
    return (res);
}

bigint bigint::operator>>(const bigint &src) const {
    std::stringstream ss(src.num);
    unsigned int n;
    ss >> n;
    bigint res = *this;
    while (n-- && !res.num.empty())
        res.num.erase(res.num.size() - 1, 1);
    return (res);
}

bigint& bigint::operator<<=(const bigint &src) {
    *this = *this << src.num;
    return *this;
}

bigint& bigint::operator>>=(const bigint &src) {
    *this = *this >> src.num;
    return *this;
}

bool bigint::operator>(const bigint &src) const {
    return this->num > src.num;
}

bool bigint::operator<(const bigint &src) const {
    return this->num < src.num;
}

bool bigint::operator>=(const bigint &src) const {
    return this->num >= src.num;
}

bool bigint::operator<=(const bigint &src) const {
    return this->num <= src.num;
}

bool bigint::operator==(const bigint &src) const {
    return this->num == src.num;
}

bool bigint::operator!=(const bigint &src) const {
    return this->num != src.num;
}
