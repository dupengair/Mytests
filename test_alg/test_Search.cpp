
#include <stdio.h>
#include <vector>

#include "test_timer.h"

using std::vector;

#define MAXVAL 10
#define NOTEXIST 65535
#define GEN_RAND
#define GEN_SEQ
#define GEN_FIBO

int a[MAXVAL] = {58, 3, 69, 94, 37, 5, 82, 16, 7, 42};
int b[MAXVAL] = {3, 5, 7, 16, 37, 42, 58, 69, 82, 94};  
int c[MAXVAL] = {0, 1, 6, 24, 35, 47, 59, 62, 73, 99}; 
int Fibo[MAXVAL] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};



int Sequence_Search(vector<int>& a, int n, int key)
{
    a.push_back(key);

    int i = 0;
    while(a[i] != key)
        i++;

    if(i > n) 
        i = NOTEXIST;
    
    return i;    
}

int Binary_search(vector<int>& a, int n, int key)
{
    int l, h, m;
    l = 0;
    h = n - 1;

    while(l <= h) {
        m = (l + h)/2;
        if(key < a[m]) {
            h = m - 1;
        } else if(key > a[m]) {
            l = m + 1;
        } else
            return m;
    }
}

int Insert_search(vector<int>& a, int n, int key)
{
    int l, h, m;
    l = 0;
    h = n - 1;

    while(l <= h) {
        m = l + (h - l)*(key - a[l])/(a[h] - a[l]);
        if(key < a[m]) {
            h = m - 1;
        } else if(key > a[m]) {
            l = m + 1;
        } else
            return m;
    }
}

int Fibonacci_Search(vector<int>& a, int n, int key, vector<int>& Fibo)
{
    int l, h, m, i, k;
    l = 0;
    h = n - 1;
    k = 0;
    vector<int> v(a, a + n);

    while(n > (Fibo[k] -1)) 
        k++;

    for(i = n; i<(Fibo[k] -1); i++)
        v.push_back(a[n]); 

    while(l <= h) {
        m = l + Fibo[k-1] -1;
        if(key < a[m]) {
            h = m -1;
            k = k - 1;
        } else if(key > a[m]) {
            l = m + 1;
            k = k -2;
        } else {
            if (m <= n )
                return m;
            else
                return n;
        }
    }
}


int main(void)
{
    int i;
    
    STARTCOUNT;
    i = Sequence_Search(a, sizeof(a)/sizeof(a[0]), 37);
    ENDCOUNT;
    printf("Sequence_Search: %d, result: %d\n\n", 37, i);

    STARTCOUNT;
    i = Binary_search(b, sizeof(b)/sizeof(b[0]), 37);
    ENDCOUNT;
    printf("Binary_Search: %d, result: %d\n\n", 37, i);

    STARTCOUNT;
    i = Insert_search(b, sizeof(b)/sizeof(b[0]), 37);
    ENDCOUNT;
    printf("Insert_search: %d, result: %d\n\n", 37, i);

    STARTCOUNT;
    i = Fibonacci_Search(c, sizeof(c)/sizeof(c[0]), 59);
    ENDCOUNT;
    printf("Fibonacci_Search: %d, result: %d\n\n", 59, i);

}
