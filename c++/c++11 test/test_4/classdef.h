#pragma once
#include <string>
#include <iostream>
#include <initializer_list>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

/*class definition*/

class Student {
			std::vector<std::pair<int, std::string> > data;
		public:
			Student(std::initializer_list<std::pair<int, std::string> > l) {
				for(auto i=l.begin(); i!=l.end(); ++i) 
					data.push_back(*i);
			}
		};

extern void func(std::initializer_list<int> l);



class SmartArray {
			std::vector<int> idx;
			std::vector<int> d;
 		public:
			SmartArray& operator[] (std::initializer_list<int> l) {
				std::for_each(l.begin(), l.end(), [&](int i) { idx.push_back(i); });
				return *this;
			}

			SmartArray& operator= (int t) {
				if (!idx.empty()) {
					std::for_each(idx.begin(), idx.end(), [&](int i) {
						d.resize((i+1) > (int)d.size() ? (i+1) : (int)d.size());
						d[i] = t;
					});
					idx.clear();
				}
				return *this;
			}

			void Print() {
				//for(auto i:d) 
                            for(auto i=d.begin(); i!=d.end(); ++i)  cout << *i << " ";
				cout << endl;
			}
		};

