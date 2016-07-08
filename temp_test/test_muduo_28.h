#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <stdio.h>

#include "test_muduo_mutex.h"

using std::string;
using std::pair;
using std::vector;
using std::map;
using std::shared_ptr;


// Test 1 - BEGIN
class CustomerData {
    public:
        typedef pair<string, int> Entry;
        typedef vector<Entry> Entrylist;
        typedef map<string, Entrylist> Map;
        typedef shared_ptr<Map> MapPtr;
    
    private:
        MapPtr getData() const {
            MutexLockGuard Lock(mutex_);
            return data_;
        }

        mutable MutexLock mutex_;
        MapPtr data_;

    public:
        CustomerData(): data_(new Map) {}

        int query(const string& customer, int timewait = 0) const;
        void update(const string& customer, const Entrylist& entries);
        void printall(void);

};

// Test 1 - END 

// Test 2 - BEGIN
class Foo {
    public:
        Foo(int id):id(id) {}
        void doit() {
            MutexLockGuard Lock(mutex_);
            printf("Foo object %d do it!\n", id);
        }
        int getid() {
            return id;
        }
    private:
        int id;
        mutable MutexLock mutex_;
};

typedef vector<Foo> FooList;
typedef shared_ptr<FooList> FooListPtr;
// Test 2 - END