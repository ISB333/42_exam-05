#pragma once

#include <ostream>

class vect2 {
	private:
		int x;
		int y;
	public:
		vect2();
		vect2(int xValue, int yValue);
		vect2(const vect2 &src);
		vect2& operator=(const vect2 &src);
		~vect2();

		int getX() const {return x;}
		int getY() const {return y;}

		int& operator[](int index);
		int operator[](int index) const;

		vect2& operator++();
		vect2 operator++(int);
		vect2& operator--();
		vect2 operator--(int);

		vect2 operator+(const vect2 &src) const;
		vect2& operator+=(const vect2 &src);
		vect2 operator-(const vect2 &src) const;
		vect2& operator-=(const vect2 &src);

		vect2 operator*(int n) const;
		friend vect2 operator*(int scalar, const vect2& v);
		vect2 operator*=(int n) ;

		vect2 operator-() const;

		bool operator==(const vect2 &src);
		bool operator!=(const vect2 &src);
};

std::ostream& operator<<(std::ostream &os, const vect2& src);
