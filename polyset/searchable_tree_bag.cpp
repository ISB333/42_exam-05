#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() : tree_bag() {}
searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag &src) : tree_bag(src) {}
searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag &src) {
	tree_bag::operator=(src);	
	return *this;
}
searchable_tree_bag::~searchable_tree_bag() {}

bool searchable_tree_bag::has(int value) const {
	searchable_tree_bag *root = const_cast<searchable_tree_bag *>(this);
	tree_bag::node *tmp = root->extract_tree();
	bool found = false;

	tree_bag::node *curr = tmp;
	while (curr) {
		if (curr->value == value) {
			found = true;
			break;
		}
		if (curr->value > value)
			curr = curr->l;
		else
			curr = curr->r;
	}
	root->set_tree(tmp);
	return found;
}
