#include "vect2.hpp"
#include <iostream>
#include <cassert>

void original_tests()
{
    std::cout << "--- Original Tests ---" << std::endl;
    vect2 v1; // 0, 0
    vect2 v2(1, 2); // 1, 2
    const vect2 v3(v2); // 1, 2
    vect2 v4 = v2; // 1, 2

    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v1: " << "{" << v1[0] << ", " << v1[1] << "}" << std::endl;
    std::cout << "v2: " << v2 << std::endl;
    std::cout << "v3: " << v3 << std::endl;
    std::cout << "v4: " << v4 << std::endl;
    std::cout << std::endl;
    std::cout << "v4++ now: " << v4++ << "   | after: " << v4 << std::endl;
    std::cout << "++v4    : " << v4++ << std::endl;
    std::cout << "v4-- now: " << v4-- << "   | after: " << v4 << std::endl;
    std::cout << "--v4    : " << --v4 << std::endl; // 1, 2
    v2 += v3; // 2, 4
    v1 -= v2; // -2, -4
    std::cout << "v2: " << v2 << std::endl;
    std::cout << "v1: " << v1 << std::endl;
    v2 = v3 + v3 *2; // 3, 6
    std::cout << "\nv2: " << v2 << std::endl;
    v2 = 3 * v2; // 9, 18
    std::cout << "v2: " << v2 << std::endl;
    v2 += v2 += v3; // 20, 40
    v1 *= 42; // -84, -168
    v1 = v1 - v1 + v1;
    std::cout << "v2: " << v2 << std::endl;
    std::cout << "v1: " << v1 << std::endl;
    std::cout << "-v2: " << -v2 << std::endl;
    std::cout << "v1[1]: " << v1[1] << std::endl;
    v1[1] = 12;
    std::cout << "v1[1]: " << v1[1] << std::endl;
    std::cout << "v3[1]: " << v3[1] << std::endl;
    std::cout << "v1 == v3: " << (v1 == v3) << std::endl;
    std::cout << "v1 == v1: " << (v1 == v1) << std::endl;
    std::cout << "v1 != v3: " << (v1 != v3) << std::endl;
    std::cout << "v1 != v1: " << (v1 != v1) << std::endl;
    std::cout << "----------------------" << std::endl << std::endl;
}

void advanced_tests()
{
    std::cout << "--- Advanced Tests ---" << std::endl;

    // 1. Constructors & Assignment
    std::cout << "Testing Constructors & Assignment..." << std::endl;
    vect2 a; 
    assert(a.getX() == 0 && a.getY() == 0);
    
    vect2 b(10, 20);
    assert(b.getX() == 10 && b.getY() == 20);
    
    vect2 c(b);
    assert(c.getX() == 10 && c.getY() == 20);
    
    a = b;
    assert(a.getX() == 10 && a.getY() == 20);
    std::cout << "OK" << std::endl;

    // 2. Equality
    std::cout << "Testing Equality..." << std::endl;
    assert(a == b);
    assert(a != vect2(0,0));
    assert(!(a == vect2(0,0)));
    std::cout << "OK" << std::endl;

    // 3. Arithmetic
    std::cout << "Testing Arithmetic..." << std::endl;
    vect2 v(1, 2);
    vect2 sum = v + vect2(3, 4); // 4, 6
    assert(sum.getX() == 4 && sum.getY() == 6);
    
    vect2 diff = sum - v; // 3, 4
    assert(diff.getX() == 3 && diff.getY() == 4);
    
    vect2 scaled = v * 10; // 10, 20
    assert(scaled.getX() == 10 && scaled.getY() == 20);
    
    vect2 scaled2 = 5 * v; // 5, 10
    assert(scaled2.getX() == 5 && scaled2.getY() == 10);

    v += vect2(10, 10); // 11, 12
    assert(v.getX() == 11 && v.getY() == 12);
    
    v -= vect2(1, 2); // 10, 10
    assert(v.getX() == 10 && v.getY() == 10);
    
    v *= 2; // 20, 20
    assert(v.getX() == 20 && v.getY() == 20);

    vect2 neg = -v; // -20, -20
    assert(neg.getX() == -20 && neg.getY() == -20);
    std::cout << "OK" << std::endl;

    // 4. Increment/Decrement
    std::cout << "Testing Increment/Decrement..." << std::endl;
    vect2 inc(0, 0);
    
    // Post-increment
    vect2 old = inc++; // old should be 0,0, inc should be 1,1
    assert(old.getX() == 0 && old.getY() == 0);
    assert(inc.getX() == 1 && inc.getY() == 1);
    
    // Pre-increment
    vect2& ref = ++inc; // inc becomes 2,2, ref refers to inc
    assert(inc.getX() == 2 && inc.getY() == 2);
    assert(ref.getX() == 2 && ref.getY() == 2);
    assert(&ref == &inc);

    // Post-decrement
    old = inc--; // old 2,2, inc 1,1
    assert(old.getX() == 2 && old.getY() == 2);
    assert(inc.getX() == 1 && inc.getY() == 1);

    // Pre-decrement
    vect2& ref2 = --inc; // inc 0,0
    assert(inc.getX() == 0 && inc.getY() == 0);
    assert(ref2.getX() == 0 && ref2.getY() == 0);
    std::cout << "OK" << std::endl;

    // 5. Subscript
    std::cout << "Testing Subscript..." << std::endl;
    vect2 sub(5, 10);
    assert(sub[0] == 5);
    assert(sub[1] == 10);
    
    sub[0] = 50;
    sub[1] = 100;
    assert(sub.getX() == 50);
    assert(sub.getY() == 100);
    
    const vect2 csub(7, 14);
    assert(csub[0] == 7);
    assert(csub[1] == 14);
    
    // Test out of range
    try {
        sub[2] = 0;
        assert(false && "Should have thrown out_of_range");
    } catch (const std::exception& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
    std::cout << "OK" << std::endl;

    std::cout << "All Advanced Tests Passed!" << std::endl;
}

int main()
{
    original_tests();
    advanced_tests();
    return 0;
}
