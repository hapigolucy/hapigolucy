#pragma once
#include <set>
#include <vector>
#include <deque>

using namespace std;

struct Employee {
    string firstName;
    string lastName;
    int age;
    double salary;

    Employee() {}

    Employee(const string &fName, const string &lName, int a, double sal):firstName(fName), lastName(lName), age(a), salary(sal) {}

    Employee(const Employee& rhs) {
        age = rhs.age;
        firstName = rhs.firstName;
        lastName = rhs.lastName;
        salary = rhs.salary;
    }

    Employee& operator=(const Employee& rhs) {
        if( this != &rhs )
        {
            age = rhs.age;
            firstName = rhs.firstName;
            lastName = rhs.lastName;
            salary = rhs.salary;
        }
        return *this;
    }

    Employee(Employee&& rhs) {
        age = move(rhs.age);
        firstName = move(rhs.firstName);
        lastName  = move(rhs.lastName);
        salary    = move(rhs.salary);
    }

    Employee& operator=(Employee&& rhs) {
        if( this != &rhs )
        {
            age = move(rhs.age);
            firstName = move(rhs.firstName);
            lastName  = move(rhs.lastName);
            salary    = move(rhs.salary);
        }
        return *this;
    }

    string getSortingName() { return lastName + ", " + firstName; }

    bool operator<(const Employee& emp) {
        if (firstName < emp.firstName) return true;
        if (firstName > emp.firstName) return false;
        if (lastName < emp.lastName) return true;
        if (lastName > emp.lastName) return false;
        if (age < emp.age) return true;
        if (age > emp.age) return false;
        if (salary < emp.salary) return true;
        else return false;
    }

    friend bool operator<(const Employee& emp1, const Employee& emp2) {
        if (emp1.firstName < emp2.firstName) return true;
        if (emp1.firstName > emp2.firstName) return false;
        if (emp1.lastName < emp2.lastName) return true;
        if (emp1.lastName > emp2.lastName) return false;
        if (emp1.age < emp2.age) return true;
        if (emp1.age > emp2.age) return false;
        if (emp1.salary < emp2.salary) return true;
        else return false;
    }

    friend bool operator==(const Employee& e1, const Employee& e2) {
        return e1.firstName == e2.firstName && e1.lastName == e2.lastName;
    }

    /***Overload for displayin an Employee object ***/
    friend ostream& operator<<(ostream& out, const Employee& emp) {
        auto padRight = [](string s){
            size_t padLength = max( 1, static_cast<int>(15 - s.length()) );
            return s.append( padLength, ' ');
        };
        string name = emp.firstName + " " + emp.lastName;
        out << padRight(name) << " " << "    " << emp.age << "    " << emp.salary;
        return out;
    }

    /***Overload for displayin vector<Employee> ***/
    friend ostream& operator<<(ostream& os, const vector<Employee>& empSet){
        os << "Employees are : \n";
        for(const auto& employee : empSet) {
            os << employee << "\n";
        }
        return os;
    }

    /***Overload for displayin set<Employee> ***/
    friend ostream& operator<<(ostream& os, const set<Employee>& empSet){
        os << "\nEmployees are : \n";
        for(const auto& employee : empSet) {
            os << employee << "\n";
        }
        return os;
    }

    /***Overload for displayin deque<Employee> ***/
    friend ostream& operator<<(ostream& os, deque<Employee>& empDeque){
        for(const auto& employee : empDeque)
            os << employee << "\n";
        return os;
    }

    friend class EmployeeHash;
    friend class EmployeeEqual;
};

class EmployeeHash {
    public:
    size_t operator()(const Employee& e) const {
        return hash<string>()(e.firstName) + hash<string>()(e.lastName);
    }
};

class EmployeeEqual {
    public:
    bool operator()(const Employee& e1, const Employee& e2) const {
        return e1.firstName == e2.firstName && e1.lastName == e2.lastName;
    }
};
