#include <iostream>

#include "test_list.h"

using std::cout;
using std::endl;


/*
 *  single list
 */
 template<typename T>
slist<T>* slist<T>::head = NULL;
template<typename T>
int slist<T>::size = 0;

// generate head node;
template<typename T>
void slist<T>::Init(T init)
{
    if(!head) {
        cout << "new born slist" << endl;
        size = 0;
        head = new slist;
        head->next = NULL;
        head->data=init;
    } else
        cout << "list exist, no need to init!" << endl;
}

template<typename T>
void slist<T>::Destroy(void)
{
    if(!head) 
        cout << "not yet inited!" << endl;    
    else {
        slist<T>* iter = head;
        slist<T>* todelete;
        int cnt = 0;
        while(iter) {
            todelete = iter;           
            iter = iter->next;
            delete todelete;
            ++cnt;
        }
        cout << "delete " << cnt << " elements" << endl;
    }
}

template<typename T>
slist<T>* slist<T>::Get(int pos)
{
    if(pos > size) {
        cout << "too large the position: " << pos << ", current: " << size << endl;
        return NULL;
    }

    slist<T>* iter = head->next;
    while(pos--)
         iter = iter->next;

    return iter;
}

template<typename T>
slist<T>* slist<T>::GetHead(void)
{
    return head->next;
}

template<typename T>
slist<T>* slist<T>::GetTail(void)
{
    slist<T>* iter = head;
    while(iter->next)
         iter = iter->next;

    cout << "tail: " << iter->data << endl;
    return iter;
}

template<typename T>
void slist<T>::PrintAll(void)
{
    cout << "current list: ";
    if(size > 0) {
        slist<T>* iter = head;
        while(iter->next) {
            iter = iter->next;
            cout << iter->data << " ";
        }
        cout << endl;
    }
}

template<typename T>
int slist<T>::Insert(T e, int i)
{
    if(i > size) {
        cout << "too large the position: " << i << ", current: " << size << endl;
        return -1;      
    } else if(size == 0) {
        cout << "add the 1st elem: " << e;
        i=0;
    }else if(i == -1) {
        cout << "add to the tail: " << e;
        i = size;
    } else if(i < 0) {
        cout << "invalid position: " << i << endl;
        return -1;      
    } else 
        cout << "add: " << e; 

    slist<T>* iter = head;
    int t = 0;
    while(t < i) {
        iter = iter->next;
        t++;
    }
       
    slist<T>* toinsert = new slist<T>;
    toinsert->data = e;
    toinsert->next = iter->next;
    iter->next = toinsert;
    size++;

    cout << ", before " << iter->data << ",  current size : " << size << endl;

    return 0;
}

template<typename T>
int slist<T>::Delete(int i)
{
    if(i > size) {
        cout << "too large the position: " << i << ", current: " << size << endl;
        return -1;      
    } else if(i < 0) {
        cout << "nothing to delete" << endl;
        return 0;
    } else if(i == 0) {
        cout << "could not delete head" << endl;
        return 0;
    }

    slist<T>* iter = head;
    slist<T>* prev = head;
    int t = 0;
    while(t++ < i) {
        prev = iter;
        iter = iter->next;
    }

    cout << "delete :" << iter->data << endl;
    prev->next = iter->next;
    size--;
    delete iter;  
}

template<typename T>
int slist<T>::Length(void)
{
    cout << "size: " << size << endl;
    return size;
}

template<typename T>
int slist<T>::Merge(list_interface<T>* l)
{
}

/*
 *  double list
 */
 template<typename T>
dlist<T>* dlist<T>::head = NULL;
template<typename T>
int dlist<T>::size = 0;
 
// generate head node;
template<typename T>
void dlist<T>::Init(T init)
{
    if(!head) {
        cout << "new born dlist" << endl;
        size = 0;
        head = new dlist;
        head->next = NULL;
        head->data=init;
        head->prev=NULL;
    } else
        cout << "list exist, no need to init!" << endl;
}

template<typename T>
void dlist<T>::Destroy(void)
{
    if(!head) 
        cout << "not yet inited!" << endl;    
    else {
        dlist<T>* iter = head;
        dlist<T>* todelete;
        int cnt = 0;
        while(iter) {
            cout << "delete: " << iter->data << endl;
            todelete = iter;           
            iter = iter->next;
            delete todelete;
            ++cnt;
        }
        cout << "delete " << cnt << " elements" << endl;
    }
}

template<typename T>
dlist<T>* dlist<T>::Get(int pos)
{
    if(pos > size) {
        cout << "too large the position: " << pos << ", current: " << size << endl;
        return NULL;
    }

    dlist<T>* iter = head->next;
    while(pos--)
         iter = iter->next;

    return iter;
}

template<typename T>
dlist<T>* dlist<T>::GetHead(void)
{
    return head->next;
}

template<typename T>
dlist<T>* dlist<T>::GetTail(void)
{
    dlist<T>* iter = head;
    while(iter->next)
         iter = iter->next;

    cout << "tail: " << iter->data << endl;
    return iter;
}

template<typename T>
void dlist<T>::PrintAll(void)
{
    cout << "current list: ";
    if(this->size > 0) {
        dlist<T>* iter = head;
        while(iter->next) {
            iter = iter->next;
            cout << iter->data << " ";
        }
        cout << endl;
    }
}

template<typename T>
int dlist<T>::Insert(T e, int i)
{
    if(i > size) {
        cout << "too large the position: " << i << ", current: " << size << endl;
        return -1;      
    } else if(size == 0) {
        cout << "add the 1st elem: " << e;
        i=0;
    }else if(i == -1) {
        cout << "add to the tail: " << e;
        i = size;
    } else if(i < 0) {
        cout << "invalid position: " << i << endl;
        return -1;      
    } else 
        cout << "add: " << e; 
    
    dlist<T>* iter = head;
    int t = 0;
    while(t < i) {
        iter = iter->next;
        t++;
    }

    dlist<T>* toinsert = new dlist<T>;
    toinsert->data = e;
    toinsert->next = iter->next;
    if(iter->next) {
        toinsert->prev = iter->next->prev;
        iter->next->prev = toinsert; 
    }
    iter->next = toinsert;
    size++;

    cout << ", before " << iter->data << ",  current size : " << size << endl;

    return 0;
}

template<typename T>
int dlist<T>::Delete(int i)
{
    if(i > size) {
        cout << "too large the position: " << i << ", current: " << this->size << endl;
        return -1;      
    } else if(i < 0) {
        cout << "nothing to delete" << endl;
        return 0;
    } else if(i == 0) {
        cout << "could not delete head" << endl;
        return 0;
    }

    dlist<T>* iter = head;
    dlist<T>* prev = head;
    int t = 0;
    while(t++ < i) {
        prev = iter;
        iter = iter->next;
    }

    cout << "delete :" << iter->data << endl;
    if(iter->next) 
        iter->next->prev = prev;    
    prev->next = iter->next;
    size--;
    
    delete iter;  
}

template<typename T>
int dlist<T>::Length(void)
{
    cout << "size: " << size << endl;
    return size;
}

template<typename T>
int dlist<T>::Merge(list_interface<T>* l)
{
}


/*
 *  ring list
 */
 template<typename T>
rlist<T>* rlist<T>::head = NULL;
template<typename T>
int rlist<T>::size = 0;
 
// generate head node;
template<typename T>
void rlist<T>::Init(T init)
{
    if(!head) {
        cout << "new born dlist" << endl;
        size = 0;
        head = new rlist;
        head->next = head;
        head->data= init;
        head->prev= head;
    } else
        cout << "list exist, no need to init!" << endl;
}

template<typename T>
void rlist<T>::Destroy(void)
{
    if(!head) 
        cout << "not yet inited!" << endl;    
    else {
        rlist<T>* iter = head;
        rlist<T>* todelete;
        int cnt = 0;
        while(iter) {            
            todelete = iter;   
            iter->prev->next = NULL;
            iter = iter->next;
            delete todelete;
            ++cnt;            
        }
        cout << "delete " << cnt << " elements" << endl;
    }
}

template<typename T>
rlist<T>* rlist<T>::Get(int pos)
{
    if(pos > size) {
        cout << "too large the position: " << pos << ", current: " << size << endl;
        return NULL;
    }

    rlist<T>* iter = head->next;
    while(pos--)
         iter = iter->next;

    return iter;
}

template<typename T>
rlist<T>* rlist<T>::GetHead(void)
{
    return head->next;
}

template<typename T>
rlist<T>* rlist<T>::GetTail(void)
{
    rlist<T>* iter = head;
    while(iter->next != head)
         iter = iter->next;

    cout << "tail: " << iter->data << endl;
    return iter;
}

template<typename T>
void rlist<T>::PrintAll(void)
{
    cout << "current list: ";
    if(this->size > 0) {
        rlist<T>* iter = head;
        while(iter->next != head) {
            iter = iter->next;
            cout << iter->data << " ";
        }
        cout << endl;
    }
}

template<typename T>
int rlist<T>::Insert(T e, int i)
{
    if(i > size) {
        cout << "too large the position: " << i << ", current: " << size << endl;
        return -1;      
    } else if(size == 0) {
        cout << "add the 1st elem: " << e;
        i=0;
    }else if(i == -1) {
        cout << "add to the tail: " << e;
        i = size;
    } else if(i < 0) {
        cout << "invalid position: " << i << endl;
        return -1;      
    } else 
        cout << "add: " << e; 
    
    rlist<T>* iter = head;
    int t = 0;
    while(t < i) {
        iter = iter->next;
        t++;
    }

    rlist<T>* toinsert = new rlist<T>;
    toinsert->data = e;
    toinsert->next = iter->next;
    if(iter->next) {
        toinsert->prev = iter->next->prev;
        iter->next->prev = toinsert; 
    }
    iter->next = toinsert;
    size++;

    cout << ", before " << iter->data << ",  current size : " << size << endl;

    return 0;
}

template<typename T>
int rlist<T>::Delete(int i)
{
    if(i > size) {
        cout << "too large the position: " << i << ", current: " << this->size << endl;
        return -1;      
    } else if(i < 0) {
        cout << "nothing to delete" << endl;
        return 0;
    } else if(i == 0) {
        cout << "could not delete head" << endl;
        return 0;
    }

    rlist<T>* iter = head;
    rlist<T>* prev = head;
    int t = 0;
    while(t++ < i) {
        prev = iter;
        iter = iter->next;
    }

    cout << "delete :" << iter->data << endl;
    if(iter->next) 
        iter->next->prev = prev;    
    prev->next = iter->next;
    size--;
    
    delete iter;  
}

template<typename T>
int rlist<T>::Length(void)
{
    cout << "size: " << size << endl;
    return size;
}

template<typename T>
int rlist<T>::Merge(list_interface<T>* l)
{
}



int main() 
{
    // baisc list test
    //slist<int> l;
    dlist<int> l;
    //rlist<int> l;

    l.Init(23223);

    l.Insert(1);
    l.Insert(2);
    l.Insert(3);
    l.Insert(4);
    l.Insert(5);
    l.Insert(99, 4);
    
    l.PrintAll();
    l.GetTail();
    l.Length();

    l.Delete(5);
    l.PrintAll();
    l.GetTail();
    l.Length();
    
    l.Destroy();

    return -1;
}
