#include "test_muduo_28.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <unistd.h>

using std::cout;
using std::endl;
using std::for_each;

#define RUN_TEST2

// Test 1 - BEGIN

int CustomerData::query(const string& customer, int timewait) const
{
    MapPtr data = getData();
   
    Map::const_iterator entries = data->find(customer);
    if(entries != data->end()) {
        cout << "customer " << customer << " have stocks: " << endl;
    
        const Entrylist& stocks = entries->second;
        for_each(stocks.begin(), stocks.end(), [timewait, &data](const Entry& entry){
            cout << "   " << entry.first << ", " << entry.second << ", map address = " << &(*data) << endl;
            if(timewait)
                sleep(timewait);
        });       
    } else {
        cout << "finish query: " << customer << endl;
        return -1;
    }

    cout << "finish query: " << customer << endl;
    return 0;
}

void CustomerData::update(const string& customer, const Entrylist& entries)
{
    MutexLockGuard Lock(mutex_);
    cout << "beging update: " << customer << endl;
    
    if(!data_.unique()) {
        MapPtr newData(new Map(*data_));
        cout << "before swap, old map addr = " << &(*data_) << ", new map addr = " << &(*newData) << endl;
        data_.swap(newData);
        cout << "after swap, old map addr = " << &(*data_) << ", new map addr = " << &(*newData) << endl;
        sleep(2);
    }
    (*data_)[customer] = entries;    
    
    cout << "finish update: " << customer << endl;
}

void CustomerData::printall(void)
{
    for_each(data_->begin(), data_->end(), [&](const pair<string, Entrylist>& p){
        query(p.first);
    });
}

void* threadfunc1(void* data)
{
    CustomerData* pCst = (CustomerData*)data;
    pCst->query("Almond", 1);
    pCst->query("Iris", 1);
    pCst->query("Jessie", 1);
}

void* threadfunc2(void* data)
{
    CustomerData::Entrylist cst = {{"infnv", 3}, {"hikiv", 3}, {"dahua", 3}, 
                                                    {"stock1", 31}, {"stock2", 32}, {"stock3", 33}, 
                                                    {"stock4", 34}, {"stock5", 35}, {"stock6", 36}};

    CustomerData* pCst = (CustomerData*)data;
    sleep(2);
    pCst->update("almond", cst);
    pCst->update("Jessie", cst);
}

void test1(void* param)
{
    pthread_t tid1, tid2;
    pthread_attr_t attr1, attr2;

    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    
    if(pthread_create(&tid1, &attr1, threadfunc1, param)) {
        cout << "create thread 1 failed" << endl;
        exit(1);
     }

    if(pthread_create(&tid2, &attr2, threadfunc2, param)) {
        cout << "create thread 2 failed" << endl;
        exit(1);
     }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
}

// Test 1 - END

// Test 2 - BEGIN
MutexLock Test2mutex;
FooListPtr g_foos;

void init()
{
    for(int i = 0; i < 10; i++) {
        Foo tmp(i);
        g_foos->push_back(tmp);
    }

    for(int i = 0; i < 10; i++) {
        printf("FooList(%d) has: %d \n", g_foos->size(), (*g_foos)[i].getid());
    }
}

void traverse(int interval) 
{
    FooListPtr foos;
    {
        MutexLockGuard lock(Test2mutex);
        foos = g_foos;
    }

    for(FooList::const_iterator it = foos->begin(); it != foos->end(); ++it) {
        sleep(interval);
        it->doit();
    }
}


void post(const Foo& f)
{
    printf("post\n");
    MutexLockGuard lock(Test2mutex);
    if(!g_foos.unique()) {
        g_foos.reset(new FooList(*g_foos));
        print("copy the whole list\n");
    }
    
    g_foos->push_back(f);    
}

void* threadfunc2_1(void* data)
{
    traverse(50);   
}

void* threadfunc2_2(void* data)
{
    sleep(200);
    post(new Foo(11));
    traverse(10);
}
    
void test2(void* param)
{
    pthread_t tid1, tid2;
    pthread_attr_t attr1, attr2;

    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    
    if(pthread_create(&tid1, &attr1, threadfunc2_1, param)) {
        cout << "create thread 1 failed" << endl;
        exit(1);
     }

    if(pthread_create(&tid2, &attr2, threadfunc2_2, param)) {
        cout << "create thread 2 failed" << endl;
        exit(1);
     }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
}


// Test 2 - END

int main(void)
{
// Test 1 - BEGIN
#ifdef RUN_TEST1
    CustomerData MyCsts;

    CustomerData::Entrylist cst1 = {{"infnv", 0}, {"hikiv", 0}, {"dahua", 0}, 
                                                    {"stock1", 1}, {"stock2", 2}, {"stock3", 3}, 
                                                    {"stock4", 4}, {"stock5", 5}, {"stock6", 6}};
    
    CustomerData::Entrylist cst2 = {{"infnv", 1}, {"hikiv", 1}, {"dahua", 1}, 
                                                    {"stock1", 11}, {"stock2", 12}, {"stock3", 13}, 
                                                    {"stock4", 14}, {"stock5", 15}, {"stock6", 16}};
    
    CustomerData::Entrylist cst3 = {{"infnv", 2}, {"hikiv", 2}, {"dahua", 2}, 
                                                    {"stock1", 21}, {"stock2", 22}, {"stock3", 23}, 
                                                    {"stock4", 24}, {"stock5", 25}, {"stock6", 26}};
    
    MyCsts.update("Almond", cst1);
    MyCsts.update("Iris", cst2);
    MyCsts.update("Jessie", cst3);

    MyCsts.printall();
    sleep(3);
    
    cout << "Test begin ======>" << endl;
    test1(&MyCsts);
    cout << "Test end <======" << endl;
#endif
// Test 1 - END

// Test 2 - BEGIN
#ifdef RUN_TEST2
    init();
    test2();
#endif
// Test 2 - END
}
