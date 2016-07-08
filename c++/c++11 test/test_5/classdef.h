#pragma once
#include <string>
#include <iostream>
              #include <algorithm>
		#include<initializer_list>	
		#include<vector>

using std::cout;
using std::endl;
               using std::string;
               using std::vector;

/*class definition*/

class A {
        int m, n;
    public:
        A(int x, int y): m(x), n (y) {}
        explicit operator int() { return m*n; }
};


    
class B {
       
    public:
         int m;
        explicit B(int x): m(x) {}
};





		class SmartArray {
			vector<int> idx;
			vector<int> d;
 		public:
			SmartArray& operator[](std::initializer_list<int> l) {
                
				std::for_each(l.begin(), l.end(), [&](int i) { idx.push_back(i); cout << i << " ";});
                            cout << endl;
				return *this;
			}

			SmartArray& operator=(int t) {
				if (!idx.empty()) {
					std::for_each(idx.begin(), idx.end(), [&](int i) {
						d.resize((i+1) > (int)d.size() ? (i+1) : (int)d.size());
						cout << "d[" << i << "] = " << t << endl;
						d[i] = t;
					});
					idx.clear();
				}
				return *this;
			}

			void Print() {
				for(auto i:d) cout << i << " ";
				cout << endl;
			}
                };
		