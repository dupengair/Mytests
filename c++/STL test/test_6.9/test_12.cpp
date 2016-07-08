#include <iostream>
#include <string>
#include "test.h"

#include <stdio.h>
#include <set>
#include <array>
#include <forward_list>
#include <algorithm>
#include <iterator>


using std::cout;
using std::endl;
using std::string;
using std::forward_list;
using std::set;


template <typename T>
inline void PE(const T& coll, const string& optstr="")
{
    cout<<optstr;
    for(const auto& e : coll)
        cout << e << ' ';
    cout<<endl;
}

class Person {
public:
    string fname;
    string lname;
    Person() {
        fname = "hh";
        lname = "kk";
    }
    Person(const string& f, const string& l): fname(f), lname(l) {}
    void Get() {
        cout << fname << "." << lname << endl;
    }
        
};



int main(void)
{
    auto cmp = [] (const Person& p1, const Person& p2) {
        return p1.lname < p2.lname || (p1.lname == p2.lname && p1.fname < p2.fname);
    };

    std::set<Person, decltype(cmp)> coll(cmp);

    forward_list<int> l1 = {1, 2, 3, 4, 5};
    forward_list<int> l2 = {98, 99, 100};

    auto pos1 = l1.before_begin();
    for (auto pb1=l1.begin(); pb1 != l1.end(); ++pb1, ++pos1)
          if(*pb1 == 3) break;
     
     auto pos2 = l2.before_begin();
     for (auto pb2=l2.begin(); pb2 != l2.end(); ++pb2, ++pos2)
           if(*pb2 == 99) break;

     l1.splice_after(pos2, l2, pos1);

     //l1.splice_after(pos1, l2, pos2);

    PE(l1, "l1: ");
    PE(l2, "l2: ");

    return 0;
}
