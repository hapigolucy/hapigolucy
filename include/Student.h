#pragma once

#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <map>

using namespace std;

class StudentFirstNameSort;

class Student
{
    //for convenience, I have created them as public inorder to avoid having to write getters.
    public:
        string _fName;
        string _lName;
        int    _class;
        int    _rollNo;
        //vector<string> _subjects;
        //vector<int> _marks;
        static int currentRollNo;

        Student();
        Student(string fName, string lName, int cls);
        virtual ~Student();
        bool operator<(const Student& s1) const;
        friend ostream& operator<<(ostream& os, const Student& s);
        friend ostream& operator<<(ostream& os, const set<Student>& students);
        friend ostream& operator<<(ostream& os, const vector<Student>& students);
        friend ostream& operator<<(ostream& os, const map<Student, vector<int>>& studentMarks);
        friend ostream& operator<<(ostream& os, const map<Student, vector<int>, StudentFirstNameSort>& studentMarks);
};

class StudentFirstNameSort
{
    public:
        bool operator()(const Student& s1, const Student& s2)
        {
            if(s1._fName < s2._fName)
                return true;
            else
                return false;
        }

};
