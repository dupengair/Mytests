#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <functional>
#include <map>

#include "motorbike.h"

using namespace std;

typedef struct tagStudentInfo
{
    int nID;
    string strName;
    bool operator < (tagStudentInfo const &_A) const
       {
              if(nID < _A.nID) return true;
              if(nID == _A.nID) return strName.compare(_A.strName) < 0;
              return false;
       }
    
}StudentInfo, *PStudentInfo;  //学生信息




void test_display_map2(void)
{
    //用学生信息映射分数
    map<StudentInfo, int> mapStudent;
    StudentInfo studentInfo;

    studentInfo.nID = 1;
    studentInfo.strName = "student_one";
    mapStudent.insert(pair<StudentInfo, int>(studentInfo, 90));

    studentInfo.nID = 2;
    studentInfo.strName = "student_two";
    mapStudent.insert(pair<StudentInfo, int>(studentInfo, 80));

    for(map<StudentInfo, int>::iterator iter = mapStudent.begin(); iter != mapStudent.end(); ++iter)
        {
        cout << "student : " << iter->second << " " << "ID = " << iter->first.nID << " " << "Name = " << iter->first.strName <<endl;
        }

}






void test_display_map(void)
{
    map<string, int> words;
    string key;

    words["dup1"] = 97;
    words["dup2"] = 98;
    words["dup3"] = 99;
    
    for(map<string, int>::iterator iter = words.begin(); iter != words.end(); ++iter)
        {
        key =  iter->first;
        cout << "key = " << iter->first << " " << "value = " << iter->second << endl;
        }

    cout << "last key = " << key << endl;
    map<string, int>::iterator iter2;
    iter2 = words.find(key);
    if( iter2 != words.end())
        {
        cout << "value = " << iter2->second << endl;
        }
    else
        {
        cout << "can't find value for key = " << key<<endl;
        }
           
}

