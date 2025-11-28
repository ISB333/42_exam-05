#include <iostream>
#include <cstdlib>
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"
#include "set.hpp"

// Original main logic wrapped in a function
void original_main_test(int argc, char **argv) {
    std::cout << "=== Original Main Test ===" << std::endl;
    if (argc == 1) {
        std::cout << "No arguments provided for original main test." << std::endl;
        return;
    }
    searchable_bag *t = new searchable_tree_bag;
    searchable_bag *a = new searchable_array_bag;

    for (int i = 1; i < argc; i++) {
        t->insert(atoi(argv[i]));
        a->insert(atoi(argv[i]));
    }
    t->print();
    a->print();

    for (int i = 1; i < argc; i++) {
        std::cout << t->has(atoi(argv[i])) << std::endl;
        std::cout << a->has(atoi(argv[i])) << std::endl;
        std::cout << t->has(atoi(argv[i]) - 1) << std::endl;
        std::cout << a->has(atoi(argv[i]) - 1) << std::endl;
    }

    t->clear();
    a->clear();

    // Note: static_cast might fail if virtual inheritance is used without proper casting support or if the object isn't actually that type.
    // But since we created 'a' as searchable_array_bag, it should be fine if the hierarchy allows.
    // We changed virtual inheritance to normal inheritance in previous steps to make this work.
    const searchable_array_bag tmp(static_cast<searchable_array_bag &>(*a));
    tmp.print();
    tmp.has(1);

    set sa(*a);
    set st(*t);
    for (int i = 1; i < argc; i++) {
        st.insert(atoi(argv[i]));
        sa.insert(atoi(argv[i]));

        sa.has(atoi(argv[i]));
        sa.print();
        sa.get_bag().print();
        st.print();
        sa.clear();
        int arr[] = {1, 2, 3, 4};
        sa.insert(arr, 4);
        std::cout << std::endl;
    }
    
    // Cleanup to avoid leaks in this test function
    // Cast to concrete types because base destructor is not virtual
    delete static_cast<searchable_tree_bag *>(t);
    delete static_cast<searchable_array_bag *>(a);
}

void test_searchable_array_bag() {
    std::cout << "\n=== Searchable Array Bag Test ===" << std::endl;
    searchable_array_bag bag;
    
    bag.insert(10);
    bag.insert(20);
    bag.insert(30);
    
    std::cout << "Bag content: ";
    bag.print();
    
    std::cout << "Has 10? " << bag.has(10) << " (Expected 1)" << std::endl;
    std::cout << "Has 99? " << bag.has(99) << " (Expected 0)" << std::endl;
    
    // Test Copy Constructor
    searchable_array_bag bag2(bag);
    std::cout << "Copy constructed bag content: ";
    bag2.print();
    
    // Test Assignment Operator
    searchable_array_bag bag3;
    bag3 = bag;
    std::cout << "Assigned bag content: ";
    bag3.print();
    
    // Modify original, ensure copies are deep
    bag.clear();
    std::cout << "Original cleared." << std::endl;
    std::cout << "Copy content (should be intact): ";
    bag2.print();
}

void test_searchable_tree_bag() {
    std::cout << "\n=== Searchable Tree Bag Test ===" << std::endl;
    searchable_tree_bag bag;
    
    bag.insert(50);
    bag.insert(30);
    bag.insert(70);
    
    std::cout << "Tree content: ";
    bag.print();
    
    std::cout << "Has 50? " << bag.has(50) << " (Expected 1)" << std::endl;
    std::cout << "Has 99? " << bag.has(99) << " (Expected 0)" << std::endl;
    
    // Test Copy Constructor
    searchable_tree_bag bag2(bag);
    std::cout << "Copy constructed tree content: ";
    bag2.print();
    
    // Test Assignment Operator
    searchable_tree_bag bag3;
    bag3 = bag;
    std::cout << "Assigned tree content: ";
    bag3.print();
    
    // Modify original
    bag.clear();
    std::cout << "Original cleared." << std::endl;
    std::cout << "Copy content (should be intact): ";
    bag2.print();
}

void test_set() {
    std::cout << "\n=== Set Test ===" << std::endl;
    searchable_array_bag bag_impl;
    set s(bag_impl);
    
    s.insert(10);
    s.insert(10); // Duplicate
    s.insert(20);
    
    std::cout << "Set content (should be 10 20): ";
    s.print();
    
    std::cout << "Has 10? " << s.has(10) << " (Expected 1)" << std::endl;
    
    // Test with Tree Bag implementation
    searchable_tree_bag tree_impl;
    set s_tree(tree_impl);
    s_tree.insert(5);
    s_tree.insert(5);
    s_tree.insert(15);
    
    std::cout << "Tree Set content (should be 5 15): ";
    s_tree.print();
}

int main(int argc, char **argv) {
    // Run original main logic
    original_main_test(argc, argv);
    
    // Run additional tests
    test_searchable_array_bag();
    test_searchable_tree_bag();
    test_set();
    
    return 0;
}
