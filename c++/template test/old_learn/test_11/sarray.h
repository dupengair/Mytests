#pragma once

#include <iostream>
#include <stddef.h>
#include <cassert>

using std::cout;
using std::endl;

namespace template_test
{

    template <typename T>
    class SArray {
    private:
        T* storage;
        size_t storage_size;

    protected:
        void init() {
            for(size_t idx = 0; idx < size(); ++idx)
                //storage[idx] = T();
                storage[idx] = 1;
        }

        void copy (SArray<T> const& orig) {
            assert(size() == orig.size());
            for(size_t idx = 0; idx < size(); ++idx)
                storage[idx] = orig.storage[idx];
        }
        
    public:
        explicit SArray (size_t s): storage(new T[s]), storage_size(s) {
            init();
        }

        SArray (SArray<T> const& orig): storage(new T[orig.size()]), storage_size(orig.size()) {
            copy(orig);
        }

        ~SArray() {
            delete[] storage;
        }


        SArray<T>& operator= (SArray<T> const& orig) {
            if (&orig != this) 
                copy(orig);
            
            return *this;
        }

        size_t size() const {
            return storage_size;
        }

        T operator[] (size_t idx) const {
            return storage[idx];
        }

        T& operator[](size_t idx) {
            return storage[idx];
        }

        void pr(void) {
            for(size_t idx = 0; idx < size(); ++idx) {
                cout << storage[idx] << " ";
            }
        }
        
    };
};

