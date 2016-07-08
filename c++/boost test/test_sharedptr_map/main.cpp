#include <iostream>
#include <string>
#include <map>
#include <boost/smart_ptr.hpp> 
#include <boost/make_shared.hpp> 

#include "product.h"

using std::cout;
using std::endl;
using std::string;
//using namespace test_boost;



test_boost::TPDTMAP PdtMap;
test_boost::TPDTOBJMAP PdtObjMap;



void addProduct(string name, test_boost::Factory fac)
{
    cout << "add product : " << name << endl;
    PdtMap[name]=fac.produce(name);

    //cout << " use count 2 : " << PdtMap[name].use_count() << endl;
    
    cout << PdtMap.size() << " products in factory";

    for(test_boost::TPDTMAP::iterator iter = PdtMap.begin(); iter != PdtMap.end(); ++iter)
        {
        cout << " " << iter->first ;
        }

    cout << endl;
}

void delProduct(string name)
{
    cout << "delete product : " << name << endl;
    PdtMap.erase(name);
    
    cout << PdtMap.size() << " products in factory"; 

    for(test_boost::TPDTMAP::iterator iter = PdtMap.begin(); iter != PdtMap.end(); ++iter)
        {
        cout << " " << iter->first ;
        }

    cout << endl;
}

void addProductObj(string name, test_boost::Factory fac)
{
    cout << "add product : " << name << endl;
    PdtObjMap[name]=fac.produceobj(name);

    cout << PdtObjMap.size() << " product objs in factory";
    
    for(test_boost::TPDTOBJMAP::iterator iter = PdtObjMap.begin(); iter != PdtObjMap.end(); ++iter)
        {
        cout << " " << iter->first ;
        }

    cout << endl;
}

void delProductObj(string name)
{
    cout << "delete product : " << name << endl;
    PdtObjMap.erase(name);
    
    cout << PdtObjMap.size() << " product objs in factory"; 

    for(test_boost::TPDTOBJMAP::iterator iter = PdtObjMap.begin(); iter != PdtObjMap.end(); ++iter)
        {
        cout << " " << iter->first ;
        }

    cout << endl;
}

#define TEST_BOOST


int main(void)
{
    test_boost::Factory fac;
    test_boost::ProductPtr gPdtPtr;

   
    #ifdef TEST_BOOST
    addProduct("p1", fac);
    addProduct("p2", fac);
    addProduct("p3", fac);


    cout << endl << "shared count : " << PdtMap["p1"].use_count() << endl;
    gPdtPtr = PdtMap["p1"];
    cout << endl << "shared count : " << PdtMap["p1"].use_count() << endl;


    delProduct("p1");

      cout << endl << "shared count : " << gPdtPtr.use_count() << endl;

    #else
    
    addProductObj("p1", fac);
    addProductObj("p2", fac);
    addProductObj("p3", fac);

    delProductObj("p1");
    #endif

    
    return 0;
}

