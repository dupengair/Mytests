#ifndef USECOUNT_H
#define USECOUNT_H

class UseCount {
public:
    UseCount(): p(new int(1)) {};
    UseCount(const UseCount& u): p(u.p) { ++*p; };
    ~UseCount() { if(--*p == 0) delete p; }   

    bool only() { return *p == 1; }
    bool makeonly();
    bool reattach(const UseCount& u);

private:
    UseCount& operator=(const UseCount&);

private:
    int* p;
};

#endif
