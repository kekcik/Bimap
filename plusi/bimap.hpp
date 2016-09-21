//
//  bimap.hpp
//  plusi
//
//  Created by Иван Трофимов on 20.09.16.
//  Copyright © 2016 Иван Трофимов. All rights reserved.
//

#ifndef bimap_hpp
#define bimap_hpp

#include <stdio.h>
#include <string>
struct bimap
{
    typedef int left_t;
    typedef int right_t;
    
    struct left_iterator;
    struct right_iterator;
    struct node; 
    
    bimap();
    ~bimap();
    left_iterator insert(left_t const& left, right_t const& right);
    void erase(left_iterator it);
    void erase(right_iterator it);
    
    left_iterator  find_left (left_t  const& left)  const;
    right_iterator find_right(right_t const& right) const;
    
    left_iterator begin_left() const;
    left_iterator end_left() const;
    
    right_iterator begin_right() const;
    right_iterator end_right() const;
private:
    node* root;
};

struct bimap::left_iterator
{
    friend bimap;
    left_t const& operator*() const;
    left_iterator& operator++();
    left_iterator operator++(int);
    
    left_iterator& operator--();
    left_iterator operator--(int);
    
    right_iterator flip() const;
    bool operator!=(const left_iterator) const;
    bool operator==(const left_iterator) const;
private:
    node* select;
};

struct bimap::right_iterator
{
    friend bimap;
    right_t const& operator*() const;
    right_iterator& operator++();
    right_iterator operator++(int);
    right_iterator& operator--();
    right_iterator operator--(int);
    left_iterator flip() const;
    bool operator!=(const right_iterator) const;
    bool operator==(const right_iterator) const;
private:
    node* select;
};

struct bimap::node
{
    bimap::left_t  left_data;
    node*   left_left;
    node*   left_right;
    node*   left_parent;
    bimap::right_t right_data;
    node*   right_left;
    node*   right_right;
    node*   right_parent;
};

#endif /* bimap_hpp */
