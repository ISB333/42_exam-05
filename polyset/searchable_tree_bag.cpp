#include "searchable_tree_bag.hpp"
#include "subject/subject/tree_bag.hpp"
#include <cstddef>

searchable_tree_bag::searchable_tree_bag() {}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag &other) {
    *this = other;
}

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag &other) {
    tree_bag::operator=(other);
    return *this;
}

searchable_tree_bag::~searchable_tree_bag() {}

bool searchable_tree_bag::has(int value) const {
    searchable_tree_bag *tmp = const_cast<searchable_tree_bag *>(this);
    tree_bag::node *root = tmp->extract_tree();
    bool found = false;

    tree_bag::node *curr = root;
    while (curr != NULL) {
        if (curr->value == value) {
            found = true;
            break;
        } else if (value < curr->value)
            curr = curr->l;
        else
            curr = curr->r;
    }
    tmp->set_tree(root);
    return found;
}