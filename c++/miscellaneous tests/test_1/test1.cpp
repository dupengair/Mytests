#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <functional>
#include <map>
#include <iterator>
#include <fstream>

#include "motorbike.h"

using namespace std;

#define _TEST1_C

template <typename T>
static void display(const string &msg, const vector<T> &vec)
{
    cout << msg;
    cout << "size of vec : " << vec.size() << endl;
    for(unsigned int i=0; i<vec.size(); i++)
        {
        cout << vec[i] << ' ';
        }
    cout << '\n';
}

template <typename T>
static void display2(const T *first, const T *last)
{
    int i = 0;
    
    if(!first || !last)
        {
        return;
        }

    for(; first <= last; ++first, ++i)
        {
        cout <<i << ' ' << *first << ' ' << endl;
        }

    cout << "size = " << i << endl;
}

template <typename T>
inline const T *begin( const vector<T> &vec )
{
    return vec.empty() ? 0 : &vec[0];
}

template <typename T>
inline const T *end( const vector<T> &vec )
{
    int size = vec.size();
    return vec.empty() ? 0 : &vec[size - 1];
}


template <typename T>
static void display3(const vector <T> &vec)
{
    int i = 0;
    
    for(typename vector<T>::const_iterator iter = vec.begin(); iter != vec.end(); ++iter, ++i)
        {
        cout <<i << " = " << *iter << endl;
        }

    cout << "size = " << i << endl;
}

template <typename T>
static void display4(T first, T last)
{
    int i = 0;
   
    for(; first != last; ++first, ++i)
        {
        cout <<i << ' ' << *first << ' ' << endl;
        }

    cout << "size = " << i << endl;
}

int count_occurs(const vector<int> &vec, int val)
{
    vector<int>::const_iterator iter = vec.begin();
    int occurs_count = 0;
    while((iter = find(iter, vec.end(), val)) != vec.end())
        {
        cout << "iter = " << *iter << endl;
        ++occurs_count;
        ++iter;
        }
 
    return occurs_count;
}

vector<int> filter(const vector<int> &vec, int val, less<int> lt)
{
    vector<int> nvec;
    vector<int>::const_iterator iter = vec.begin();

   while((iter = find_if(iter, vec.end(), bind2nd(lt, val))) != vec.end())
        {
        nvec.push_back(*iter);
        iter++;
        }

    return nvec;
}


template <typename T_in, typename T_out, typename T_cmp, typename T_op>
void filter2(T_in first, T_in last, T_out out, T_cmp val, T_op op)
{
    while((first = find_if(first, last, not1(bind2nd(op, val)))) != last)
        {
        cout << "found value: " << *first << endl;
        *out++ = *first++;
        first++;
        }
}

vector<int> sub_vec(const vector<int> &vec, int val)
{
    vector<int> local_vec(vec);

    sort(local_vec.begin(), local_vec.end());

    vector<int>::iterator iter=find_if(local_vec.begin(), local_vec.end(), bind2nd(greater<int>(), val));

    local_vec.erase(iter, local_vec.end());
    return local_vec;
}

template <typename T_in, typename T_out, typename T_cmp, typename T_op>
T_out sub_vec2(T_in first, T_in last, T_out out, T_cmp val, T_op op)
{
    sort(first, last);

    T_in mid=find_if(first, last, bind2nd(op, val));
    while(first != mid)
        {
        *out++ = *first++;
        }

    return out;
}


void test_copy (void)   
{  
     typedef vector<string> IntVector;  
     typedef istream_iterator<string> IstreamItr;  
     typedef ostream_iterator<string> OstreamItr;  

     IntVector myvector;  
     ifstream in_file("input_file.txt");
     ofstream out_file("output_file.txt");

     if(!in_file || !out_file)
        {
        cout << "can't open file" << endl;
        }
     
  
     cout << "Please input element:" << endl;  
     copy(IstreamItr(in_file), IstreamItr(), back_inserter(myvector));

     
     sort(myvector.begin(), myvector.end());
     
     cout << "Copy : " << endl;  
     copy(myvector.begin(), myvector.end(), OstreamItr(out_file, " "));   
}

void test_copy2 (void)   
{  
     typedef istream_iterator<string> IstreamItr;  
     typedef ostream_iterator<string> OstreamItr;  

     
     ifstream in_file2("output_file.txt");
     
     if(!in_file2)
        {
        cout << "can't open in_file2" << endl;
        }

     
     cout << "Output : " << endl;  
     copy(IstreamItr(in_file2), IstreamItr(), OstreamItr(cout, " "));   
     cout << endl;
}

void test_display(void)
{
    string msg = "fhpaiofhpaoehf";
    const char *ar[] = {"ar1", "ar2", "ar3", "ar4"};
    Motorbike mb1("mb1"), mb2("mb2"), mb3("mb3"), mb4("mb4");
    Motorbike mb[] = {mb1, mb2, mb3, mb4};
    const int occ[] = {6, 10, 8, 4, 10, 7, 10, 6};
    
    vector <int> ivec(8, 1);
    vector <string> svec(4, "hello world");
    vector <string> sarvec(ar, ar+4);
    list <string> slist(4, "list!");
    list <Motorbike> mblist(mb, mb+4);
    vector <int> ivec2(occ, occ+sizeof(occ)/sizeof(int));
    vector <int> after_vec(occ, occ+sizeof(occ)/sizeof(int));
/*    
    display(msg, ivec);
    display(msg, svec);

    display2(begin(ivec), end(ivec));
    display2(begin(svec), end(svec));

    display3(ivec);
    display3(svec);
    
    display4(ar, ar+4);
    display4(svec.begin(), svec.end());
    display4(slist.begin(), slist.end());
    display4(mblist.begin(), mblist.end());

    cout << "occur counts : " << count_occurs(ivec2, 6) << endl;
    cout << "binary_search : " << binary_search(ivec2.begin(), ivec2.end(), 6) << endl;
    transform(ivec2.begin(), ivec2.end(),
                   ivec.begin(),
                   after_vec.begin(),
                   plus<int>());
    display4(after_vec.begin(), after_vec.end());

    vector <int> nvec = filter(after_vec, 10, less<int>());
    display4(nvec.begin(), nvec.end());

    vector <int> nvec2(10);
    filter2(after_vec.begin(), after_vec.end(), nvec2.begin(), 10, less<int>());
    display4(nvec2.begin(), nvec2.end());

    vector <int> nvec3 = sub_vec(after_vec, 10);
    display4(nvec3.begin(), nvec3.end());

    vector <int> nvec4(10);
    sub_vec2(after_vec.begin(), after_vec.end(), nvec4.begin(), 10, greater<int>());
    display4(nvec4.begin(), nvec4.end());

    vector <int> nvec5;
    filter2(after_vec.begin(), after_vec.end(), back_inserter(nvec5), 10, less<int>());*/

    vector <string> myvector;
    copy(sarvec.begin(), sarvec.end(), back_inserter(myvector));  
    display3(myvector);
    test_copy();
    test_copy2();
    
}



