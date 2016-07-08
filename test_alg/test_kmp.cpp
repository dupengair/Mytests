#include <string>
#include <string.h>

#include "test_kmp.h"

using std::string;

int alg_find_substring_normal(const string& m, const string& s)
{
        int i = 0;
        int j = 0;
        
        while(i < m.size() && j < s.size()) {
            //cout << "current m[" << i << "]: " << m[i] << ", s[" << j << "]: " << s[j] << endl;
            
            if(m[i] == s[j]) {
                i++;
                j++;
            } else {
                i = i -j + 1;           // i back to the next pos from beginning
                j = 0;
            }

            if (j == s.size()) 
                return (i -j);
        }

        return 0;
}


int kmp_g_next(const string& s, int *next)
{
    int cur = 0;
    int pre = 0;
    int post = 0;
    int nums = 0;

    while(cur < s.size()) {     
        next[cur] = 0;
        nums = 0;
        while(nums < cur) {
            pre = 0;
            post = cur-nums; 
            while(pre <= nums) {
                if(s[pre] != s[post]) 
                    break;
                pre++;
                post++;
            }
            if(pre > nums)
                next[cur] = pre;
            nums++;
        }        
        //cout << "next[" << cur << "] = " << next[cur] << endl;
        cur++;
    }

    return 0;
}

int alg_find_substring_kmp(const string& m, const string& s)
{
    int* next = new int[s.size()];
    kmp_g_next(s, next);

    int i = 0;
    int j = 0;
        
    while(i < m.size() && j < s.size()) {
        //cout << "current m[" << i << "]: " << m[i] << ", s[" << j << "]: " << s[j] << endl;
            
        if(m[i] == s[j]) {
            i++;
            j++;
        } else {  
            ((j > 0) && (next[j-1]>0)) ? (i += j - next[j-1]) : (i = i -j + 1);    
            j = 0;
        }

        if (j == s.size()) {
            delete[] (next); 
            return (i -j);
        }
    }

    delete[] (next); 
    return 0;
}


int main(void)
{
       string s1 = "tadajiutaerjiutajiutajxdoutajiutajshitajiutajtadajiutaerjiutajiutajxdoutajiutajshitajiutajtadajiutaerjiutajiutajxdoutajiutajshitajiutajtadajiutaerjiutajiutajxdoutajiutajshitajiutajtadajiutaerjiutajiutajxdoutajiutajshitajiutajtadajiutaerjiutajiutajxdoutajiutajshitajiutajtadajiutaerjiutajiutajxdoutajiutajshitajiutajtadajiutaerjiutajiutajxdoutajiutajshitajiutajiu";
       string s2 = "tajiu";
       cout << "main string (" << s1.size() << "): " << s1 << ",  substring (" << s2.size() <<"): " << s2<< endl; 

       STARTCOUNT;
       cout << "find substring at: " << alg_find_substring_normal(s1, s2) << endl;
       ENDCOUNT;

       STARTCOUNT;
       cout << "find substring at: " << alg_find_substring_kmp(s1, s2) << endl;
       ENDCOUNT;
       
       #if 0
       string s3 = "ABCDABD";
       int next[7];
       memset(next, 0, sizeof(next));
       kmp_g_next(s3, next);
       s3 = "abcabca";
       memset(next, 0, sizeof(next));
       kmp_g_next(s3, next);
       #endif

       s1 = "tadajiutaerjiutajiutajxdoutajiutajshitajiutajtadajiutaerjiutajiutajxdoutajiutajshitajiutajtadajiutaerjiutajiutajxdoutajiutajshitajiutajtadajiutaerjiutajiutajxdoutajiutajshitajiutajtadajiutaerjiutajiutajxdoutajiutajshitajiutajtadajiutaerjiutajiutajxdoutajiutajshitajiutajtadajiutaerjiutajiutajxdoutajiutajshitajiutajtadajiutaerjiutajiutajxdoutajiutajshitajiutajiu";
       s2 = "tajiutaji";
       cout << "main string (" << s1.size() << "): " << s1 << ",  substring (" << s2.size() <<"): " << s2<< endl; 

       STARTCOUNT;
       cout << "find substring at: " << alg_find_substring_normal(s1, s2) << endl;
       ENDCOUNT;

       STARTCOUNT;
       cout << "find substring at: " << alg_find_substring_kmp(s1, s2) << endl;
       ENDCOUNT;

       
}


