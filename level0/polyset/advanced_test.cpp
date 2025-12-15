#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"
#include "set.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <climits>

// Helper to print test results
void print_result(const std::string& test_name, bool passed) {
    std::cout << test_name << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
}

void test_array_bag_basic() {
    std::cout << "--- Test Array Bag Basic ---" << std::endl;
    searchable_array_bag bag;
    bag.insert(10);
    bag.insert(5);
    bag.insert(10); // Duplicate

    bool passed = true;
    if (!bag.has(10)) { std::cout << "Failed to find 10" << std::endl; passed = false; }
    if (!bag.has(5)) { std::cout << "Failed to find 5" << std::endl; passed = false; }
    if (bag.has(1)) { std::cout << "Found 1 unexpectedly" << std::endl; passed = false; }
    
    print_result("Array Bag Basic", passed);
}

void test_tree_bag_basic() {
    std::cout << "--- Test Tree Bag Basic ---" << std::endl;
    searchable_tree_bag bag;
    bag.insert(10);
    bag.insert(5);
    bag.insert(15);
    bag.insert(10); // Duplicate

    bool passed = true;
    if (!bag.has(10)) { std::cout << "Failed to find 10" << std::endl; passed = false; }
    if (!bag.has(5)) { std::cout << "Failed to find 5" << std::endl; passed = false; }
    if (!bag.has(15)) { std::cout << "Failed to find 15" << std::endl; passed = false; }
    if (bag.has(1)) { std::cout << "Found 1 unexpectedly" << std::endl; passed = false; }

    print_result("Tree Bag Basic", passed);
}

void test_set_behavior() {
    std::cout << "--- Test Set Behavior ---" << std::endl;
    searchable_array_bag bag;
    set s(bag);

    s.insert(10);
    s.insert(5);
    s.insert(10); // Should be ignored

    bool passed = true;
    if (!s.has(10)) passed = false;
    if (!s.has(5)) passed = false;
    
    print_result("Set Behavior", passed);
}

void test_set_sharing() {
    std::cout << "--- Test Set Sharing ---" << std::endl;
    searchable_array_bag bag;
    set s1(bag);
    set s2(bag); // s2 wraps the same bag

    s1.insert(100);
    
    bool passed = s2.has(100); // s2 should see what s1 inserted
    print_result("Set Sharing", passed);
}

void test_set_copy() {
    std::cout << "--- Test Set Copy ---" << std::endl;
    searchable_array_bag bag;
    set s1(bag);
    s1.insert(200);
    
    set s2(s1); // Copy constructor
    bool passed = s2.has(200);
    
    s2.insert(300);
    if (!s1.has(300)) passed = false; // Shallow copy, s1 should see 300
    
    print_result("Set Copy (Shallow)", passed);
}

void test_tree_bag_assignment_bug() {
    std::cout << "--- Test Tree Bag Assignment Bug ---" << std::endl;
    searchable_tree_bag b1;
    searchable_tree_bag b2;
    
    b1.insert(1);
    
    // If operator= returns by value, (b2 = b1) returns a temporary.
    // Inserting into it won't affect b2.
    (b2 = b1).insert(2);
    
    bool passed = true;
    if (!b2.has(1)) {
        std::cout << "b2 missing 1 after assignment" << std::endl;
        passed = false; 
    }
    
    if (!b2.has(2)) {
        std::cout << "b2 missing 2 after chained insert (operator= returns value?)" << std::endl;
        // This is technically a failure of the canonical form expectation
        passed = false;
    }
    
    print_result("Tree Bag Assignment", passed);
}

void test_stress() {
    std::cout << "--- Stress Test ---" << std::endl;
    searchable_tree_bag tbag;
    searchable_array_bag abag;
    
    int N = 1000;
    for(int i=0; i<N; ++i) {
        tbag.insert(i);
        abag.insert(i);
    }
    
    bool passed = true;
    for(int i=0; i<N; ++i) {
        if (!tbag.has(i)) passed = false;
        if (!abag.has(i)) passed = false;
    }
    
    if (tbag.has(-1)) passed = false;
    if (abag.has(N)) passed = false;
    
    print_result("Stress Test", passed);
}

void test_const_correctness() {
    // Check if we can call has() on const objects
    searchable_array_bag abag;
    abag.insert(42);
    const searchable_array_bag& cabag = abag;
    cabag.has(42); // Should compile
    
    searchable_tree_bag tbag;
    tbag.insert(42);
    const searchable_tree_bag& ctbag = tbag;
    ctbag.has(42); // Should compile
    
    std::cout << "Const Correctness: PASSED (compiled)" << std::endl;
}

void test_polymorphism() {
    std::cout << "--- Test Polymorphism ---" << std::endl;
    searchable_array_bag ab;
    searchable_tree_bag tb;
    
    searchable_bag* bags[2];
    bags[0] = &ab;
    bags[1] = &tb;
    
    bags[0]->insert(123);
    bags[1]->insert(456);
    
    bool passed = true;
    if (!bags[0]->has(123)) passed = false;
    if (!bags[1]->has(456)) passed = false;
    
    print_result("Polymorphism", passed);
}

int main() {
    test_array_bag_basic();
    test_tree_bag_basic();
    test_set_behavior();
    test_set_sharing();
    test_set_copy();
    test_tree_bag_assignment_bug();
    test_stress();
    test_const_correctness();
    test_polymorphism();
    return 0;
}
