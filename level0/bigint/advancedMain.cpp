#include "bigint.hpp"
#include <iostream>
#include <cassert>

#define TEST(name) std::cout << "\n=== TEST: " << name << " ===" << std::endl
#define PASS() std::cout << "[PASS]" << std::endl
#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        std::cout << "[FAIL] " << msg << std::endl; \
        failures++; \
    } else { \
        std::cout << "[OK] " << msg << std::endl; \
    } \
} while(0)

int failures = 0;

int main()
{
    std::cout << "╔════════════════════════════════════════════╗" << std::endl;
    std::cout << "║     BIGINT STRESS TEST SUITE               ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════╝" << std::endl;

    // ============================================================
    TEST("CONSTRUCTORS & BASIC OPERATIONS");
    // ============================================================
    {
        bigint zero;
        bigint fromUint(4294967295U);  // Max unsigned int
        bigint fromStr("99999999999999999999999999999999999999999999999999");
        bigint copy(fromStr);
        bigint assigned;
        assigned = fromStr;

        CHECK(zero.getStr() == "0", "Default constructor creates 0");
        CHECK(fromUint.getStr() == "4294967295", "Max unsigned int construction");
        CHECK(copy.getStr() == fromStr.getStr(), "Copy constructor");
        CHECK(assigned.getStr() == fromStr.getStr(), "Assignment operator");

        // Self-assignment
        bigint self("12345");
        self = self;
        CHECK(self.getStr() == "12345", "Self-assignment");
    }

    // ============================================================
    TEST("ADDITION - BASIC");
    // ============================================================
    {
        CHECK((bigint("0") + bigint("0")).getStr() == "0", "0 + 0 = 0");
        CHECK((bigint("0") + bigint("42")).getStr() == "42", "0 + 42 = 42");
        CHECK((bigint("42") + bigint("0")).getStr() == "42", "42 + 0 = 42");
        CHECK((bigint("1") + bigint("1")).getStr() == "2", "1 + 1 = 2");
        CHECK((bigint("999") + bigint("1")).getStr() == "1000", "999 + 1 = 1000 (carry propagation)");
        CHECK((bigint("999999999") + bigint("1")).getStr() == "1000000000", "Many 9s + 1");
    }

    // ============================================================
    TEST("ADDITION - LARGE NUMBERS");
    // ============================================================
    {
        bigint huge1("99999999999999999999999999999999999999999999999999");
        bigint huge2("1");
        bigint result = huge1 + huge2;
        CHECK(result.getStr() == "100000000000000000000000000000000000000000000000000", 
              "50-digit carry propagation");

        bigint a("123456789012345678901234567890");
        bigint b("987654321098765432109876543210");
        CHECK((a + b).getStr() == "1111111110111111111011111111100", 
              "30-digit addition");

        // Adding two huge numbers of same size
        bigint x("99999999999999999999999999999999999999999999999999");
        bigint y("99999999999999999999999999999999999999999999999999");
        CHECK((x + y).getStr() == "199999999999999999999999999999999999999999999999998",
              "Large same-size addition");
    }

    // ============================================================
    TEST("ADDITION - DIFFERENT LENGTHS");
    // ============================================================
    {
        CHECK((bigint("1") + bigint("999999999999999999999")).getStr() == "1000000000000000000000",
              "Short + Long");
        CHECK((bigint("999999999999999999999") + bigint("1")).getStr() == "1000000000000000000000",
              "Long + Short");
    }

    // ============================================================
    TEST("COMPOUND ADDITION (+=)");
    // ============================================================
    {
        bigint a("100");
        a += bigint("50");
        CHECK(a.getStr() == "150", "+= basic");

        bigint b("999999999999999999999999999999");
        b += bigint("1");
        CHECK(b.getStr() == "1000000000000000000000000000000", "+= with carry");

        // Chained +=
        bigint c("1");
        c += bigint("2");
        c += bigint("3");
        c += bigint("4");
        CHECK(c.getStr() == "10", "Chained +=");
    }

    // ============================================================
    TEST("INCREMENT OPERATORS");
    // ============================================================
    {
        bigint a("99");
        CHECK((++a).getStr() == "100", "Pre-increment returns new value");
        CHECK(a.getStr() == "100", "Pre-increment modifies original");

        bigint b("99");
        CHECK((b++).getStr() == "99", "Post-increment returns old value");
        CHECK(b.getStr() == "100", "Post-increment modifies original");

        // Increment with massive carry
        bigint c("999999999999999999999999999999999999999999999999999");
        ++c;
        CHECK(c.getStr() == "1000000000000000000000000000000000000000000000000000",
              "Pre-increment massive carry");

        // Chained increments
        bigint d("0");
        ++++d;
        CHECK(d.getStr() == "2", "Chained pre-increment");
    }

    // ============================================================
    TEST("LEFT SHIFT OPERATOR (<<)");
    // ============================================================
    {
        CHECK((bigint("42") << 0).getStr() == "42", "Shift by 0");
        CHECK((bigint("42") << 1).getStr() == "420", "Shift by 1");
        CHECK((bigint("42") << 5).getStr() == "4200000", "Shift by 5");
        CHECK((bigint("1") << 100).getStr().size() == 101, "Shift by 100 (length check)");

        // Shift with bigint parameter
        CHECK((bigint("42") << bigint("3")).getStr() == "42000", "Shift by bigint(3)");

        // Zero shift
        CHECK((bigint("0") << 10).getStr() == "00000000000", "Zero shifted (edge case - may expose bug)");
    }

    // ============================================================
    TEST("LEFT SHIFT COMPOUND (<<=)");
    // ============================================================
    {
        bigint a("123");
        a <<= 4;
        CHECK(a.getStr() == "1230000", "<<= with uint");

        bigint b("456");
        b <<= bigint("3");
        CHECK(b.getStr() == "456000", "<<= with bigint");
    }

    // ============================================================
    TEST("RIGHT SHIFT OPERATOR (>>)");
    // ============================================================
    {
        CHECK((bigint("12345") >> 0).getStr() == "12345", ">> by 0");
        CHECK((bigint("12345") >> 2).getStr() == "123", ">> by 2");
        CHECK((bigint("12345") >> 5).getStr() == "", ">> by exact length (empty result)");
        CHECK((bigint("12345") >> 10).getStr() == "", ">> more than length");

        // With bigint parameter
        CHECK((bigint("9999999") >> bigint("4")).getStr() == "999", ">> with bigint param");
    }

    // ============================================================
    TEST("RIGHT SHIFT COMPOUND (>>=)");
    // ============================================================
    {
        bigint a("123456789");
        a >>= 3;
        CHECK(a.getStr() == "123456", ">>= with uint");

        bigint b("987654321");
        b >>= bigint("6");
        CHECK(b.getStr() == "987", ">>= with bigint");

        // Shift to nothing
        bigint c("123");
        c >>= 100;
        CHECK(c.getStr() == "", ">>= to empty");
    }

    // ============================================================
    TEST("COMPARISON OPERATORS - BASIC");
    // ============================================================
    {
        bigint a("100"), b("200"), c("100");

        CHECK(a < b, "100 < 200");
        CHECK(!(b < a), "!(200 < 100)");
        CHECK(!(a < c), "!(100 < 100)");

        CHECK(a <= b, "100 <= 200");
        CHECK(a <= c, "100 <= 100");
        CHECK(!(b <= a), "!(200 <= 100)");

        CHECK(b > a, "200 > 100");
        CHECK(!(a > b), "!(100 > 200)");
        CHECK(!(a > c), "!(100 > 100)");

        CHECK(b >= a, "200 >= 100");
        CHECK(a >= c, "100 >= 100");
        CHECK(!(a >= b), "!(100 >= 200)");

        CHECK(a == c, "100 == 100");
        CHECK(!(a == b), "!(100 == 200)");

        CHECK(a != b, "100 != 200");
        CHECK(!(a != c), "!(100 != 100)");
    }

    // ============================================================
    TEST("COMPARISON - DIFFERENT LENGTHS (CRITICAL)");
    // ============================================================
    {
        bigint small("9");
        bigint medium("99");
        bigint large("999");
        bigint huge("9999999999999999999999999999999999999999999999");

        CHECK(small < medium, "9 < 99 (length matters)");
        CHECK(small < large, "9 < 999");
        CHECK(medium < large, "99 < 999");
        CHECK(large < huge, "999 < huge");

        CHECK(!(medium < small), "!(99 < 9)");
        CHECK(!(huge < small), "!(huge < 9)");

        CHECK(huge > small, "huge > 9");
        CHECK(huge > medium, "huge > 99");
        CHECK(huge > large, "huge > 999");

        // The original bug case
        bigint fortyTwo("42");
        bigint bigNum("13370000");
        CHECK(bigNum > fortyTwo, "13370000 > 42 (THE BUG TEST)");
        CHECK(!(bigNum < fortyTwo), "!(13370000 < 42)");
        CHECK(bigNum >= fortyTwo, "13370000 >= 42");
        CHECK(!(bigNum <= fortyTwo), "!(13370000 <= 42)");
    }

    // ============================================================
    TEST("COMPARISON - SAME LENGTH, DIFFERENT VALUES");
    // ============================================================
    {
        CHECK(bigint("111") < bigint("222"), "111 < 222 (same length)");
        CHECK(bigint("199") < bigint("200"), "199 < 200");
        CHECK(bigint("100") < bigint("101"), "100 < 101");
        CHECK(bigint("109") < bigint("110"), "109 < 110");
        CHECK(bigint("919") < bigint("991"), "919 < 991");

        CHECK(bigint("999") > bigint("998"), "999 > 998");
        CHECK(bigint("500") > bigint("499"), "500 > 499");
    }

    // ============================================================
    TEST("COMPARISON - EDGE CASES");
    // ============================================================
    {
        bigint zero1("0");
        bigint zero2("0");
        CHECK(zero1 == zero2, "0 == 0");
        CHECK(!(zero1 < zero2), "!(0 < 0)");
        CHECK(!(zero1 > zero2), "!(0 > 0)");
        CHECK(zero1 <= zero2, "0 <= 0");
        CHECK(zero1 >= zero2, "0 >= 0");

        bigint one("1");
        CHECK(zero1 < one, "0 < 1");
        CHECK(one > zero1, "1 > 0");
    }

    // ============================================================
    TEST("CHAINED OPERATIONS");
    // ============================================================
    {
        bigint a("10");
        bigint result = ((a + bigint("5")) + bigint("3")) + bigint("2");
        CHECK(result.getStr() == "20", "Chained addition");

        bigint b("1");
        b += bigint("1");
        b += bigint("1");
        ++b;
        b++;
        CHECK(b.getStr() == "5", "Mixed increment operations");

        // Shift then add
        bigint c("5");
        c <<= 2;
        c += bigint("11");
        CHECK(c.getStr() == "511", "Shift then add");
    }

    // ============================================================
    TEST("VERY LARGE NUMBER STRESS TEST");
    // ============================================================
    {
        // Create a 1000-digit number
        std::string huge(1000, '9');
        bigint hugeNum(huge);
        CHECK(hugeNum.getStr().size() == 1000, "1000-digit number created");

        // Add 1 to it
        bigint result = hugeNum + bigint("1");
        CHECK(result.getStr().size() == 1001, "1000 nines + 1 = 1001 digits");
        CHECK(result.getStr()[0] == '1', "First digit is 1");
        for (size_t i = 1; i < result.getStr().size(); i++) {
            if (result.getStr()[i] != '0') {
                std::cout << "[FAIL] Digit at " << i << " is not 0" << std::endl;
                failures++;
                break;
            }
        }

        // Compare two huge numbers
        std::string huge1(500, '9');
        std::string huge2(501, '1');
        CHECK(bigint(huge1) < bigint(huge2), "500 nines < 501 ones (length comparison)");
    }

    // ============================================================
    TEST("REPEATED OPERATIONS STRESS");
    // ============================================================
    {
        bigint counter("0");
        for (int i = 0; i < 1000; i++) {
            ++counter;
        }
        CHECK(counter.getStr() == "1000", "1000 increments");

        bigint sum("0");
        for (int i = 0; i < 100; i++) {
            sum += bigint("123456789");
        }
        CHECK(sum.getStr() == "12345678900", "100 additions of 123456789");
    }

    // ============================================================
    TEST("SHIFT EDGE CASES");
    // ============================================================
    {
        bigint a("1");
        a <<= 50;
        CHECK(a.getStr().size() == 51, "1 shifted left 50 times");
        CHECK(a.getStr()[0] == '1', "First char is 1");

        bigint b = a >> 50;
        CHECK(b.getStr() == "1", "Shift right cancels shift left");

        // Empty after shift
        bigint c("123");
        c >>= 1000;
        CHECK(c.getStr().empty() || c.getStr() == "", "Massive right shift empties number");
    }

    // ============================================================
    TEST("OUTPUT STREAM OPERATOR");
    // ============================================================
    {
        bigint a("12345678901234567890");
        std::stringstream ss;
        ss << a;
        CHECK(ss.str() == "12345678901234567890", "Stream output operator");
    }

    // ============================================================
    TEST("POTENTIAL BUGS - LEADING ZEROS");
    // ============================================================
    {
        // These might expose bugs if your implementation doesn't handle leading zeros
        bigint a("007");  // Constructor with leading zeros
        std::cout << "bigint(\"007\") = " << a << " (check if leading zeros handled)" << std::endl;

        bigint zero_shifted("0");
        zero_shifted <<= 5;
        std::cout << "0 << 5 = \"" << zero_shifted << "\" (might be 000000, potential bug)" << std::endl;
    }

    // ============================================================
    // FINAL SUMMARY
    // ============================================================
    std::cout << "\n╔════════════════════════════════════════════╗" << std::endl;
    std::cout << "║            TEST SUMMARY                    ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════╝" << std::endl;
    
    if (failures == 0) {
        std::cout << "✓ ALL TESTS PASSED!" << std::endl;
    } else {
        std::cout << "✗ FAILURES: " << failures << std::endl;
    }

    return failures;
}
