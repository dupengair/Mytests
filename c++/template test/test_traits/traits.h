#ifndef TRAITS_H
#define TRAITS_H

#include <iostream>
#include "BearCorner.h"

using namespace std;


template<class Guest> class GuestTraits;

template<> class GuestTraits<Bear> {
public:
    typedef CondensedMilk beverage_type;
    typedef Honey snack_type;    
};

template<> class GuestTraits<Boy> {
 public:
    typedef Milk beverage_type;
    typedef Cookies snack_type;    
};   

class MixedUpTraits {
public:
    typedef Milk beverage_type;
    typedef Honey snack_type;        
};

template<class Guest, class Action, class traits = GuestTraits<Guest> >
class BearCorner {
    Guest theGuest;
    typedef typename traits::beverage_type beverage_type;
    typedef typename traits::snack_type snack_type;
    beverage_type bev;
    snack_type snack;
public:
    BearCorner(const Guest& g): theGuest(g) {}
    void entertain() {
        cout << Action::doAction() << " " << theGuest << " serveing " << bev << " and " << snack << endl;
        }
    
};







#endif
