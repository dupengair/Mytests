#include <iostream>
#include <stddef.h>
#include <cassert>
#include <cstring>
#include <typeinfo>


namespace template_test
{

    using std::cout;
    using std::endl;


    template<typename T>
    class Trule;
    

    template<typename T>
    class Holder {
    private:
        T* ptr;
    public:
        Holder():ptr(0) {}
        explicit Holder(T* p):ptr(p) {}
        ~Holder() { delete ptr; }

        Holder<T>& operator= (T* p) {
            delete ptr;
            ptr = p;
            return *this;
        }
        T& operator* () const { return *ptr; }
        T* operator-> () const { return ptr; }
        T* get() const { return ptr; }
        void release() { ptr = 0; }
        void exchange_with (Holder<T>& h) { std::swap(ptr, h.ptr); }
        void exchange_with(T*& p) { std::swap(ptr, p); }
    private:
        Holder (Holder<T> const&);
        Holder<T>& operator= (Holder<T> const&);

    public:
        Holder(Trule<T> const& t) {
            ptr = t.ptr;
            const_cast<Trule<T>&>(t).ptr = 0;
            }

        Holder<T>& operator= (Trule<T> const& t) {
            delete ptr;
            ptr = t.ptr;
            const_cast<Trule<T>&>(t).ptr = 0;
            return *this;
            }
    };

    template<typename T>
    class Trule {
    private:
        T* ptr;
    public:
        Trule(Holder<T>& h) {
            ptr = h.get();
            h.release();
            }
        
        Trule(Trule<T> const& t) {
            ptr = t.ptr;
            const_cast<Trule<T>& >(t).ptr = 0;
            }

        ~Trule() { delete ptr; }
    private:
        Trule(Trule<T>&);
        Trule<T>& operator= (Trule<T>&);
        friend class Holder<T>;        
    };

/*
    class CounterPolicy {
        public:
            CounterPolicy();
            CounterPolicy(CounterPolicy const&);
            ~CounterPolicy();
            CounterPolicy& operator=(CounterPolicy const&);

            void init(T*);
            void dispose(T*);
            void increment(T*);
            void decrement(T*);
            bool is_zero(T*);
    };

    class ObjectPolicy {
        public:
            ObjectPolicy();
            ObjectPolicy(CounterPolicy const&);
            ObjectPolicy();
            ObjectPolicy& operator=(ObjectPolicy const&);

            void dispose(T*);
    };
*/
    
    class StandardObjectPolicy {
        public:
            template<typename T> void dispose (T* object) {
                delete object;
                }
        };

    class StandardArrayPolicy {
        public:
            template<typename T> void dispose (T* array) {
                delete[] array;
                }
        };

    size_t* alloc_counter();
    void dealloc_counter(size_t* ptr);

    class SimpleReferenceCount {
        private:
            size_t* counter;
        public:
            SimpleReferenceCount() { counter = NULL; }

            template<typename T> void init(T*) { counter = alloc_counter(); }
            template<typename T> void dispose(T*) { dealloc_counter(counter); }
            template<typename T> void increment(T*) { ++*counter; }
            template<typename T> void decrement(T*) { --*counter; }
            template<typename T> bool is_zero(T*) { return *counter == 0; }            

        };

    template<typename ObjectT, typename CountT, CountT ObjectT::*CountP>
    class MemberReferenceCount {
        public:
            void init (ObjectT* object) { object->*CountP = 1; }
            void dispose (ObjectT*) {}
            void increment (ObjectT* object) { ++object->*CountP; }
            void decrement (ObjectT* object) { --object->*CountP; }
            template<typename T> bool is_zero(ObjectT* object) { return object->*CountP == 0; }            
    };
  

    template <typename T, 
                        typename CounterPolicy = SimpleReferenceCount,
                        typename ObjectPolicy = StandardObjectPolicy>
    class CountingPtr: private CounterPolicy, private ObjectPolicy {
        private:
            typedef CounterPolicy CP;
            typedef ObjectPolicy OP;

            T* object_pointed_to;

        public:
            CountingPtr() { this->object_pointed_to = NULL; }
            explicit CountingPtr(T* p) { this -> init(p); }
            CountingPtr(CountingPtr<T, CP, OP> const& cp): CP((CP const&)cp), OP((OP const&)cp) { this->attach(cp); }
            ~CountingPtr() { this->detach(); }

            CountingPtr<T, OP, CP>& operator= (T* p) {
                assert(p != this->object_pointed_to);
                this->dectach();

                this->init(p);
                return *this;
                }

            CountingPtr<T, OP, CP>& operator= (CountingPtr<T, OP, CP> const& cp) {
                if(cp.object_pointed_to != this->object_pointed_to) {
                    this->detach();

                    CP::operator=((CP const&)cp);
                    OP::operator=((OP const&)cp);
                    this->attach(cp);
                    }

                return *this;
                }

            T* operator-> () const { return this->object_pointed_to; }
            T& operator* () const { return *this->object_pointed_to; }  

            private:
                void init(T* p) {
                    if(p != NULL) {
                        CounterPolicy::init(p);
                        }
                    this->object_pointed_to = p;
                    }

                void attach(CountingPtr<T, CP, OP> const& cp) {
                    this->object_pointed_to = cp.object_pointed_to;
                    if(cp.object_pointed_to != NULL) {
                        CounterPolicy::increment(cp.object_pointed_to);
                        }
                    }

                void detach() {
                    if(this->object_pointed_to != NULL) {
                        CounterPolicy::decrement(this->object_pointed_to);
                        if(CounterPolicy::is_zero(this->object_pointed_to)) {
                            CounterPolicy::dispose(this->object_pointed_to);
                            ObjectPolicy::dispose(this->object_pointed_to);
                            }
                        }
                    }

            public:
                template<typename S>
                CountingPtr(CountingPtr<S, CP, OP> const& cp): CP((CP const&)cp), OP((OP const&)cp), object_pointed_to(cp.object_pointed_to) {
                    if (cp.object_pointed_to != NULL) {
                        CP::increment(cp.object_pointed_to);
                        }
                    }

                 operator bool() const { return this->object_pointed_to != (T*)0; }               
            
        };
            
                               
        
};

