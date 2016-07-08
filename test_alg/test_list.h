template<typename T>
class list_interface {
public:
   virtual void Init(T init) = 0;
   virtual void Destroy(void) = 0;  
   virtual list_interface* Get(int pos) = 0;
   virtual list_interface* GetHead(void) = 0;
   virtual list_interface* GetTail(void) = 0;
   virtual void PrintAll(void) = 0;
   virtual int Insert(T e, int i = -1) = 0;
   virtual int Delete(int i) = 0;
   virtual int Length(void) = 0;
   virtual int Merge(list_interface<T>* l) = 0;
};


template<typename T>
class slist: public list_interface<T>{
private:
   T data;
   static int size;
   static slist<T> *head;   
   slist<T>* next;

public:
   void Init(T init);
   void Destroy(void);  
   slist<T>* Get(int pos);
   slist<T>* GetHead(void);
   slist<T>* GetTail(void);
   void PrintAll(void);
   int Insert(T e, int i = -1);
   int Delete(int i);
   int Length(void);
   int Merge(list_interface<T>* l);
};


template<typename T>
class dlist: public list_interface<T>{
private:
   T data;
   static int size;
   static dlist<T> *head;   
   dlist<T>* next; 
   dlist<T>* prev;

public:
   void Init(T init);
   void Destroy(void);  
   dlist<T>* Get(int pos);
   dlist<T>* GetHead(void);
   dlist<T>* GetTail(void);
   void PrintAll(void);
   int Insert(T e, int i = -1);
   int Delete(int i);
   int Length(void);
   int Merge(list_interface<T>* l);
};


template<typename T>
class rlist: public list_interface<T>{
private:
   T data;
   static int size;
   static rlist<T> *head;   
   rlist<T>* next; 
   rlist<T>* prev;

public:
   void Init(T init);
   void Destroy(void);  
   rlist<T>* Get(int pos);
   rlist<T>* GetHead(void);
   rlist<T>* GetTail(void);
   void PrintAll(void);
   int Insert(T e, int i = -1);
   int Delete(int i);
   int Length(void);
   int Merge(list_interface<T>* l);
};

