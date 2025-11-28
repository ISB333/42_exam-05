#pragma once

#include "subject/subject/array_bag.hpp"
#include "subject/subject/searchable_bag.hpp"

class searchable_array_bag : public array_bag, public searchable_bag {
    private:
    public:
        searchable_array_bag();
        searchable_array_bag(const searchable_array_bag &other);
        searchable_array_bag& operator=(const searchable_array_bag &other);
        virtual ~searchable_array_bag();

	    virtual bool has(int) const;
};