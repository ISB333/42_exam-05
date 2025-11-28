#include "set.hpp"

set::set(searchable_bag &b) {
    bag = &b;
}

set::set(const set &other) {
    *this = other;
}

set& set::operator=(const set &other) {
    if (this != &other) {
        bag = other.bag;
    }
    return *this;
}

set::~set() {}

void set::insert(int value) {
    if (!bag->has(value)) {
        bag->insert(value);
    }
}

void set::insert(int *items, int count) {
    for (int i = 0; i < count; i++) {
        insert(items[i]);
    }
}

bool set::has(int value) const {
    return bag->has(value);
}

void set::print() const {
    bag->print();
}

void set::clear() {
    bag->clear();
}

searchable_bag &set::get_bag() {
    return *bag;
}

const searchable_bag &set::get_bag() const {
    return *bag;
}
