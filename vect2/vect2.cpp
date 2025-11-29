#include "vect2.hpp"

vect2::vect2() : x(0), y(0) {}
vect2::vect2(int xValue, int yValue) : x(xValue), y(yValue) {}
vect2::vect2(const vect2 &src) {*this = src;}
vect2& vect2::operator=(const vect2 &src) {
    if (this != &src) {
        this->x = src.x;
        this->y = src.y;
    }
    return *this;
}
vect2::~vect2() {}

std::ostream& operator<<(std::ostream &os, const vect2& src) {
    os << src.getX() << "," << src.getY();
    return os;
}

int& vect2::operator[](int index) {
    if (index == 0)
        return x;
    if (index == 1)
        return y;
    throw std::out_of_range("vect2 index out_of_range");
}

int vect2::operator[](int index) const {
    if (index == 0) 
        return x;
    if (index == 1)
        return y;
    throw std::out_of_range("vect2 index out_of_range");
}

vect2& vect2::operator++() {
    this->y++;
    this->x++;
    return *this;    
}

vect2 vect2::operator++(int) {
    vect2 tmp = *this;
    this->y++;
    this->x++;
    return tmp;    
}

vect2& vect2::operator--() {
    this->y--;
    this->x--;
    return *this;    
}

vect2 vect2::operator--(int) {
    vect2 tmp = *this;
    this->y--;
    this->x--;
    return tmp;    
}

vect2& vect2::operator+=(const vect2 &src) {
    this->x += src.x;
    this->y += src.y;
    return *this;
}

vect2& vect2::operator-=(const vect2 &src) {
    this->x -= src.x;
    this->y -= src.y;
    return *this;
}

vect2 vect2::operator-(const vect2 &src) const {
    vect2 tmp = *this;
    tmp.x -= src.x;
    tmp.y -= src.y;
    return tmp;
}

vect2 vect2::operator+(const vect2 &src) const {
    vect2 tmp = *this;
    tmp.x += src.x;
    tmp.y += src.y;
    return tmp;
}

vect2 vect2::operator*(int scalar) const {
    return vect2(x * scalar, y * scalar);
}

vect2 operator*(int scalar, const vect2& v) {
    return vect2(v.x * scalar, v.y * scalar);
}

vect2 vect2::operator*=(int scalar) {
    *this = *this * scalar;
    return *this;
}

vect2 vect2::operator-() const {
    return vect2(-x, -y);
}

bool vect2::operator==(const vect2 &src) {
    return x == src.x && y == src.y;
}

bool vect2::operator!=(const vect2 &src) {
    return x != src.x && y != src.y;
}