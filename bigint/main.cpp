#include "bigint.hpp"

int main()
{
    const bigint a(47);
    bigint b(25);
    bigint c;
    bigint d(1337);
    bigint e(d);

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;

    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "(c += a) = " << (c += a) << std::endl;
    std::cout << "c = " << c << std::endl;

    std::cout << "\n----------------------------" << std::endl;

    std::cout << "b = " << b << std::endl;
    std::cout << "++b = " << ++b << std::endl;
    std::cout << "b++ = " << b++ << std::endl;
    std::cout << "b = " << b << std::endl;

    std::cout << "\n----------------------------" << std::endl;

    std::cout << "(b << 10) + 42 = " << ((b << 10) + 42) << std::endl;
    std::cout << "(b << 10) + 42 = " << ((b >> 4)) << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "\n(d <<= 4) = " << (d <<= 4) << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "(d <<= 4) = " << (d >>= 2) << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "(d <<= 2) = " << (d <<= (const bigint)2) << std::endl;
    std::cout << "(d >>= 2) = " << (d >>= (const bigint)6) << std::endl;
    std::cout << "d = " << d << std::endl;

    std::cout << "\n----------------------------" << std::endl;

    std::cout << "a =" << a << std::endl;
    std::cout << "d =" << d << std::endl;

    std::cout << "(d < a) = " << (d < a) << std::endl;
    std::cout << "(d <= a) = " << (d <= a) << std::endl;
    std::cout << "(d > a) = " << (d > a) << std::endl;
    std::cout << "(d >= a) = " << (d >= a) << std::endl;
    std::cout << "(d == a) = " << (d == a) << std::endl;
    std::cout << "(d != a) = " << (d != a) << std::endl;
}

