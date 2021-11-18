#pragma once
#include <set>
#include <map>
#include <unordered_map>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>

#include "Employee.h"
#include "Student.h"

using namespace std;

class AssociativeContainer
{
    public:
        AssociativeContainer();
        virtual ~AssociativeContainer();
        AssociativeContainer(const AssociativeContainer& other);
        AssociativeContainer& operator=(const AssociativeContainer& other);
        void populateSets();
        void populateEmployeeSet();
        void populateStudentSet();
        void populateStudentMarksMap();
        //friend ostream& operator<<(ostream& os, const set<Employee>& empSet);
        friend ostream& operator<<(ostream& os, const set<string>& strSet);
        friend ostream& operator<<(ostream& os, const vector<int>& marks);

    protected:

    private:
        set<string> aStringSet;
        set<Employee> anEmployeeSet;

        set<Student> aStudentSet;
};
