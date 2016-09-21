//
//  bimap.cpp
//  plusi
//
//  Created by Иван Трофимов on 20.09.16.
//  Copyright © 2016 Иван Трофимов. All rights reserved.
//

#include "bimap.hpp"

void clear (bimap::node* cur) {
    if (cur -> left_left != nullptr) {
        clear(cur -> left_left);
    }
    if (cur -> left_right != nullptr) {
        clear(cur -> left_right);
    }
    delete(cur);
}
bimap::bimap() {
    root = new node();
};
bimap::~bimap() {
    clear(root);
}

bimap::left_iterator bimap::insert(bimap::left_t const& left, bimap::right_t const& right){
    bimap::node* data = new node();
    bimap::node* cur_left = root;
    bimap::node* cur_right = root;

    data -> left_data = left;
    data -> right_data = right;
    
    left_iterator ans;
    
    bool correct = true;
    bool left_is_left = true;
    bool right_is_left = true;

    if (cur_left -> left_left == nullptr) {
        data -> left_parent = root;
        data -> right_parent = root;
        root -> left_left = data;
        root -> right_left = data;
        ans.select = data;
        return ans;
    } else {
        cur_left = cur_left -> left_left;
        cur_right = cur_right -> right_left;
    }
    
    while (true) {
        if (cur_left -> left_data > data -> left_data) {
            if (cur_left -> left_left != nullptr) {
                cur_left = cur_left -> left_left;
            } else {
                data -> left_parent = cur_left;
                break;
            }
        } else if (cur_left -> left_data < data -> left_data) {
            if (cur_left -> left_right != nullptr) {
                cur_left = cur_left -> left_right;
            } else {
                data -> left_parent = cur_left;
                left_is_left = false;
                break;
            }
        } else {
            correct = false;
            break;
        }
    }
    while (true) {
        if (cur_right -> right_data > data -> right_data) {
            if (cur_right -> right_left != nullptr) {
                cur_right = cur_right -> right_left;
            } else {
                data -> right_parent = cur_right;
                break;
            }
        } else if (cur_right -> right_data < data -> right_data) {
            if (cur_right -> right_right != nullptr) {
                cur_right = cur_right -> right_right;
            } else {
                data -> right_parent = cur_right;
                right_is_left = false;
                break;
            }
        } else {
            correct = false;
            break;
        }
    }
    
    if (correct) {
        if (left_is_left) {
            cur_left -> left_left = data;
        } else {
            cur_left -> left_right = data;
        }
        if (right_is_left) {
            cur_right -> right_left = data;
        } else {
            cur_right -> right_right = data;
        }
    }
    ans.select = data;
    return ans;
};

bimap::left_iterator bimap::find_left (left_t  const& left)  const {
    node* cur = root -> left_left;
    left_iterator ans;
    while (true) {
        
        if (cur -> left_data == left) {
            ans.select = cur;
            return ans;
        }
        if (cur -> left_data > left) {

            cur = cur -> left_left;
        }
        if (cur -> left_data < left) {
            
            cur = cur -> left_right;
        }
    }
};
bimap::right_iterator bimap::find_right(right_t const& right) const {
    node* cur = root -> right_left;
    right_iterator ans;
    while (true) {
        if (cur -> right_data == right) {
            ans.select = cur;
            return ans;
        }
        if (cur -> right_data > right) {
            cur = cur -> right_left;
            continue;
        }
        if (cur -> right_data < right) {
            cur = cur -> right_right;
            continue;
        }
    }
};

bimap::left_iterator bimap::begin_left() const {
    node* cur = root -> left_left;
    left_iterator ans;

    if (cur == nullptr) {
        ans.select = root;
        return ans;
    }

    while (true) {
        if (cur -> left_left == nullptr) {
            ans.select = cur;
            return ans;
        } else {
            cur = cur -> left_left;
        }
    }
};
bimap::left_iterator bimap::end_left() const {
    left_iterator ans;
    ans.select = root;
    return ans;
};
bimap::right_iterator bimap::begin_right() const {
    node* cur = root -> right_left;
    right_iterator ans;
    
    if (cur == nullptr) {
        ans.select = root;
        return ans;
    }
    
    while (true) {
        if (cur -> right_left == nullptr) {
            ans.select = cur;
            return ans;
        } else {
            cur = cur -> right_left;
        }
    }
};
bimap::right_iterator bimap::end_right() const {
    right_iterator ans;
    ans.select = root;
    return ans;
};

bimap::left_t const& bimap::left_iterator::operator*() const {
    return select -> left_data;
};
bimap::right_t const& bimap::right_iterator::operator*() const {
    return select -> right_data;
}

bimap::left_iterator& bimap::left_iterator::operator++() {
    node* cur = select;
    if (cur -> left_right != nullptr) {
        cur = cur -> left_right;
        while (true) {
            if (cur -> left_left != nullptr) {
                cur = cur -> left_left;
            } else {
                select = cur;
                return *this;
            }
        }
    } else {
        while (true) {
            if (cur -> left_parent != nullptr) {
                if (cur -> left_parent -> left_left == cur) {
                    cur = cur -> left_parent;
                    break;
                }
                cur = cur -> left_parent;
            } else {
                break;
            }
        }
        select = cur;
        return *this;
    }
};
bimap::left_iterator& bimap::left_iterator::operator--() {
    node* cur = select;
    if (cur -> left_left != nullptr) {
        cur = cur -> left_left;
        while (true) {
            if (cur -> left_right != nullptr) {
                cur = cur -> left_right;
            } else {
                select = cur;
                return *this;
            }
        }
    } else {
        while (true) {
            if (cur -> left_parent != nullptr) {
                if (cur -> left_parent -> left_right == cur) {
                    cur = cur -> left_parent;
                    break;
                }
                cur = cur -> left_parent;
            } else {
                break;
            }
        }
        select = cur;
        return *this;
    }
}
bimap::right_iterator& bimap::right_iterator::operator++() {
    node* cur = select;
    if (cur -> right_right != nullptr) {
        cur = cur -> right_right;
        while (true) {
            if (cur -> right_left != nullptr) {
                cur = cur -> right_left;
            } else {
                select = cur;
                return *this;
            }
        }
    } else {
        while (true) {
            if (cur -> right_parent != nullptr) {
                if (cur -> right_parent -> right_left == cur) {
                    cur = cur -> right_parent;
                    break;
                }
                cur = cur -> right_parent;
            } else {
                break;
            }
        }
        select = cur;
        return *this;
    }
}
bimap::right_iterator& bimap::right_iterator::operator--() {
    node* cur = select;
    if (cur -> right_left != nullptr) {
        cur = cur -> right_left;
        while (true) {
            if (cur -> right_right != nullptr) {
                cur = cur -> right_right;
            } else {
                select = cur;
                return *this;
            }
        }
    } else {
        while (true) {
            if (cur -> right_parent != nullptr) {
                if (cur -> right_parent -> right_right == cur) {
                    cur = cur -> right_parent;
                    break;
                }
                cur = cur -> right_parent;
            } else {
                break;
            }
        }
        select = cur;
        return *this;
    }
}

bimap::left_iterator bimap::left_iterator::operator++(int) {
    left_iterator ans;
    node* cur = select;
    
    ans.select = cur;
    select = cur;

    if (cur -> left_right != nullptr) {
        cur = cur -> left_right;
        while (true) {
            if (cur -> left_left != nullptr) {
                cur = cur -> left_left;
            } else {
                select = cur;
                return ans;
            }
        }
    } else {
        while (true) {
            if (cur -> left_parent != nullptr) {
                if (cur -> left_parent -> left_left == cur) {
                    cur = cur -> left_parent;
                    break;
                }
                cur = cur -> left_parent;
            } else {
                break;
            }
        }
    }
    select = cur;
    return ans;
};
bimap::left_iterator bimap::left_iterator::operator--(int) {
    left_iterator ans;
    node* cur = select;
    ans.select = cur;
    select = cur;
    if (cur -> left_left != nullptr) {
        cur = cur -> left_left;
        while (true) {
            if (cur -> left_right != nullptr) {
                cur = cur -> left_right;
            } else {
                select = cur;
                return ans;
            }
        }
    } else {
        while (true) {
            if (cur -> left_parent != nullptr) {
                if (cur -> left_parent -> left_right == cur) {
                    cur = cur -> left_parent;
                    break;
                }
                cur = cur -> left_parent;
            } else {
                break;
            }
        }
        select = cur;
        return ans;
    }
};
bimap::right_iterator bimap::right_iterator::operator++(int) {
    right_iterator ans;
    node* cur = select;
    ans.select = cur;
    select = cur;
    if (cur -> right_right != nullptr) {
        cur = cur -> right_right;
        while (true) {
            if (cur -> right_left != nullptr) {
                cur = cur -> right_left;
            } else {
                select = cur;
                return ans;
            }
        }
    } else {
        while (true) {
            if (cur -> right_parent != nullptr) {
                if (cur -> right_parent -> right_left == cur) {
                    cur = cur -> right_parent;
                    break;
                }
                cur = cur -> right_parent;
            } else {
                break;
            }
        }
        select = cur;
        return ans;
    }

};
bimap::right_iterator bimap::right_iterator::operator--(int) {
    right_iterator ans;
    node* cur = select;
    ans.select = cur;
    select = cur;
    if (cur -> right_left != nullptr) {
        cur = cur -> right_left;
        while (true) {
            if (cur -> right_right != nullptr) {
                cur = cur -> right_right;
            } else {
                select = cur;
                return ans;
            }
        }
    } else {
        while (true) {
            if (cur -> right_parent != nullptr) {
                if (cur -> right_parent -> right_right == cur) {
                    cur = cur -> right_parent;
                    break;
                }
                cur = cur -> right_parent;
            } else {
                break;
            }
        }
        select = cur;
        return ans;
    }
};

bimap::right_iterator bimap::left_iterator::flip() const {
    right_iterator ans;
    ans.select = select;
    return ans;
};
bimap::left_iterator bimap::right_iterator::flip() const {
    left_iterator ans;
    ans.select = select;
    return ans;
};

void bimap::erase (bimap::left_iterator it) {
    if (it.select -> left_left == nullptr and it.select -> left_right == nullptr) {
        if (it.select -> left_parent -> left_left == it.select) {
            it.select -> left_parent -> left_left = nullptr;
        } else {
            it.select -> left_parent -> left_right = nullptr;
        }
    }
    if (it.select -> left_left != nullptr and it.select -> left_right == nullptr) {
        if (it.select -> left_parent -> left_left == it.select) {
            it.select -> left_parent -> left_left = it.select -> left_left;
            it.select -> left_left -> left_parent = it.select -> left_parent;
        } else  {
            it.select -> left_parent -> left_right = it.select -> left_left;
            it.select -> left_left -> left_parent = it.select -> left_parent;
        }
    }
    if (it.select -> left_left == nullptr and it.select -> left_right != nullptr) {
        if (it.select -> left_parent -> left_left == it.select) {
            it.select -> left_parent -> left_left = it.select -> left_right;
            it.select -> left_right -> left_parent = it.select -> left_parent;
        } else  {
            it.select -> left_parent ->left_right = it.select -> left_right;
            it.select -> left_right -> left_parent = it.select -> left_parent;
        }
    }
    if (it.select -> left_left != nullptr and it.select -> left_right != nullptr) {
        it.select -> left_left -> left_parent = it.select -> left_parent;
        if (it.select -> left_parent -> left_left == it.select) {
            it.select -> left_parent -> left_left = it.select -> left_left;
        } else {
            it.select -> left_parent -> left_right = it.select -> left_left;
        }
        bimap::node* cur = it.select;
        cur = cur -> left_left;
        while (cur -> left_right != nullptr) {
            cur = cur -> left_right;
        }
        cur -> left_right = it.select -> left_right;
        it.select -> left_right -> left_parent = cur;
    }
    
    if (it.select -> right_left == nullptr and it.select -> right_right == nullptr) {
        if (it.select -> right_parent -> right_left == it.select) {
            it.select -> right_parent -> right_left = nullptr;
        } else {
            it.select -> right_parent -> right_right = nullptr;
        }
    }

    if (it.select -> right_left != nullptr and it.select -> right_right == nullptr) {
        if (it.select -> right_parent -> right_left == it.select) {
            it.select -> right_parent -> right_left = it.select -> right_left;
            it.select -> right_left -> right_parent = it.select -> right_parent;
        } else  {
            it.select -> right_parent -> right_right = it.select -> right_left;
            it.select -> right_left -> right_parent = it.select -> right_parent;
        }
    }
    if (it.select -> right_left == nullptr and it.select -> right_right != nullptr) {
        if (it.select -> right_parent -> right_left == it.select) {
            it.select -> right_parent -> right_left = it.select -> right_right;
            it.select -> right_right -> right_parent = it.select -> right_parent;
        } else  {
            it.select -> right_parent ->right_right = it.select -> right_right;
            it.select -> right_right -> right_parent = it.select -> right_parent;
        }
    }
    if (it.select -> right_left != nullptr and it.select -> right_right != nullptr) {
        it.select -> right_left -> right_parent = it.select -> right_parent;
        if (it.select -> right_parent -> right_left == it.select) {
            it.select -> right_parent -> right_left = it.select -> right_left;
        } else {
            it.select -> right_parent -> right_right = it.select -> right_left;
        }
        bimap::node* cur = it.select;
        cur = cur -> right_left;
        while (cur -> right_right != nullptr) {
            cur = cur -> right_right;
        }
        cur -> right_right = it.select -> right_right;
        it.select -> right_right -> right_parent = cur;
    }
    delete(it.select);
}
void bimap::erase (bimap::right_iterator it) {
    erase(it.flip());
}

bool bimap::left_iterator::operator!=(const bimap::left_iterator a) const {
    return (a.select != select);
};
bool bimap::left_iterator::operator==(const bimap::left_iterator a) const {
    return (a.select == select);
};
bool bimap::right_iterator::operator!=(const bimap::right_iterator a) const {
    return (a.select != select);
};
bool bimap::right_iterator::operator==(const bimap::right_iterator a) const {
    return (a.select == select);
};

