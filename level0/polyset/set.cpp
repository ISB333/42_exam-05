#include "set.hpp"

set::set(searchable_bag &b) {
	bag = &b;
}
set::set(const set &src) {*this = src;}
set& set::operator=(const set &src) {
	if (this != &src)
		bag = src.bag;
	return *this;
}
set::~set() {}

bool set::has(int value) const {
	return bag->has(value);
}

void set::insert(int item) const {
	if (!bag->has(item))
		bag->insert(item);
}

void set::insert(int *items, int size) {
	for (int i = 0; i < size; i++)
		if (!bag->has(items[i]))
			bag->insert(items[i]);
}

void set::print() const {
	bag->print();
}

void set::clear() const {
	bag->clear();
}
