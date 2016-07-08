#ifndef BEARCORNER_H
#define BEARCORNER_H

#include <iostream>

using std ::ostream;


class Milk {
public:
    friend ostream& operator<< (ostream& os, const Milk&) {
        return os << "Milk";
        }
};


class Honey {
public:
    friend ostream& operator<< (ostream& os, const Honey&) {
        return os << "Honey";
        }
};


class Cookies {
public:
    friend ostream& operator<< (ostream& os, const Cookies&) {
        return os << "Cookies";
        }
};


class Bear {
public:
    friend ostream& operator<< (ostream& os, const Bear&) {
        return os << "Bear";
        }
};


class Boy {
public:
    friend ostream& operator<< (ostream& os, const Boy&) {
        return os << "Boy";
        }
};


class CondensedMilk {
public:
    friend ostream& operator<< (ostream& os, const CondensedMilk&) {
        return os << "CondensedMilk";
        }
};


class Feed {
public:
    static const char* doAction() { return "feeding"; }
};

class Stuff {
public:
    static const char* doAction() { return "Stuffing"; }
};


class Sleep {
public:
    static const char* doAction() { return "Sleepng"; }
};



#endif
