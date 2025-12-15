#pragma once

#include "subject/subject/searchable_bag.hpp"

class set {
	private:
		searchable_bag *bag;
	public:
		set(searchable_bag &b);
		set(const set &src);
		set& operator=(const set &src);
		~set();

		searchable_bag& get_bag() const {return *bag;}

		virtual bool has(int value) const;

		void insert(int item) const;
		void insert(int *items, int size);
		void print() const;
		void clear() const;
};
