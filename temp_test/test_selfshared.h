#include <iostream>
#include <memory>

using std::cout;
using std::endl;

class selfshared : public std::enable_shared_from_this<selfshared> {
    private:
        int val;
        static int count;
        
    public:
        selfshared(int v):val(v) { 
            count++; 
            cout << "selfshared constructed: " << v << ", count = " << count << endl;             
         }
        
        ~selfshared() { 
            count--;
            cout << "selfshared desstructed: " << val << endl; 
        }
        
        std::shared_ptr<selfshared> get() {            
            cout << "get selfshared pointer: " << val << ", count = " << count << endl;            
            return shared_from_this();
        }

        void counter(void) {
            cout << "count = " << count << endl;
        }
};

class selfshared2 {
    private:
        int val;
        static int count;
        
    public:
        selfshared2(int v):val(v) { 
            count++; 
            cout << "selfshared2 constructed: " << v << ", count = " << count << endl;             
         }
        
        ~selfshared2() { 
            count--;
            cout << "selfshared2 desstructed: " << val << endl; 
        }
        

        std::shared_ptr<selfshared2> get() {            
            cout << "get selfshared2 pointer: " << val << ", count = " << count << endl;            
            std::shared_ptr<selfshared2> tp(this);
            return tp;
        }

        void counter(void) {
            cout << "count = " << count << endl;
        }
};


std::shared_ptr<selfshared> CreateObj(int v) {
    std::shared_ptr<selfshared> sptr = std::make_shared<selfshared>(v);
    return sptr->get();
}

int selfshared::count = 0;
int selfshared2::count = 0;

