//
//  main.cpp
//  plusi
//
//  Created by Иван Трофимов on 20.09.16.
//  Copyright © 2016 Иван Трофимов. All rights reserved.
//

#include <iostream>
#include "bimap.hpp"
#include <vector>

using namespace std;

int main() {
    bimap a;
    cout << *a.begin_left() << endl;
    a.insert(1, 123);
    a.insert(2, 256);
    a.insert(3, 12);
    a.insert(-3, 17);
    a.insert(0, -171);

    cout << *a.find_left(1).flip() << endl;
    cout << *a.find_left(2).flip() << endl;
    cout << *a.find_left(3).flip() << endl;
    cout << *a.find_left(-3).flip() << endl;
    cout << *a.find_left(0).flip() << endl;

    cout << endl;
    
    cout << *(++a.begin_left()) << endl;
    cout << *a.begin_right() << endl;
    cout << *a.end_left() << endl;  //фейковая вершина
    cout << *a.end_right() << endl; //фейковая вершина

    cout << endl;
    
    for (
         bimap::left_iterator it = a.begin_left();
         it != a.end_left();
         ++it) {
        cout << (*it) << " -> " << *(it.flip()) << endl;
    }
    
    cout << endl;
    
    for (
         bimap::right_iterator it = a.begin_right();
         it != a.end_right();
         ++it) {
        cout << (*it) << " -> " << *(it.flip()) << endl;
    }
    
    cout << endl;
    
    bimap::left_iterator it = a.end_left();
    for (int i = 0; i < 5; ++i) {
        --it;
        cout << (*it) << " -> " << *(it.flip()) << endl;
    }
    
    cout << endl;
    
    bimap::right_iterator it2 = a.end_right();
    for (int i = 0; i < 5; ++i) {
        --it2;
        cout << (*it2) << " -> " << *(it2.flip()) << endl;
    }
   
    int kol = 0;
    while (a.begin_right() != a.end_right()) {
        a.erase(a.begin_left());
        kol++;
    }
    cout << kol << endl;
    
    
    return 0;
}


