#include "Student.h"

int Student::currentRollNo = 0;

Student::Student():_fName(""), _lName(""), _class(0), _rollNo(0)
{
    //ctor
}

Student::Student(string fName, string lName, int cls):_fName(fName), _lName(lName), _class(cls), _rollNo(++currentRollNo)
{

}

Student::~Student()
{
    //dtor
}

bool Student::operator<(const Student& s) const {
    if (_lName < s._lName) return true;
    if (_lName > s._lName) return false;
    if (_class < s._class) return true;
    else return false;
}

ostream& operator<<(ostream& os, const Student& s){
    auto padRight = [](string s){
        size_t padLength = max( 1, static_cast<int>(15 - s.length()) );
        return s.append( padLength, ' ');
    };
    string name = s._fName + " " + s._lName;
    os << padRight(name) << "   " << s._class << "      " << s._rollNo << endl;
    return os;
}

ostream& operator<<(ostream& os, const set<Student>& students){
    auto padRight = [](string s){
        size_t padLength = max( 1, static_cast<int>(15 - s.length()) );
        return s.append( padLength, ' ');
    };
    os << "=====================================" << endl;
    os << padRight("Name") << "| Class" << "| Roll Number" << endl;
    os << "=====================================" << endl;
    for(const Student& student : students)
        os << student;
    return os;
}

ostream& operator<<(ostream& os, const vector<Student>& students){
    auto padRight = [](string s){
        size_t padLength = max( 1, static_cast<int>(15 - s.length()));
        return s.append( padLength, ' ');
    };
    os << "=====================================" << endl;
    os << padRight("Name") << "| Class" << "| Roll Number" << endl;
    os << "=====================================" << endl;
    for(const Student& student : students)
        os << student;
    return os;
}

ostream& operator<<(ostream& os, const map<Student, vector<int>>& studentMarks){
    auto padRight = [](string&& s){
        size_t padLength = max( 1, static_cast<int>(15 - s.length()));
        return s.append( padLength, ' ');
    };
    os << "=====================================" << endl;
    os << padRight("Name") << "| Class" << "| Roll Number" << endl;
    os << "=====================================" << endl;
    for(const auto& student : studentMarks)
        os << student.first;
    return os;
}

ostream& operator<<(ostream& os, const map<Student, vector<int>, StudentFirstNameSort>& studentMarks){
    auto padRight = [](string&& s){
        size_t padLength = max( 1, static_cast<int>(15 - s.length()));
        return s.append( padLength, ' ');
    };
    os << "=====================================" << endl;
    os << padRight("Name") << "| Class" << "| Roll Number" << endl;
    os << "=====================================" << endl;
    for(const auto& student : studentMarks)
        os << student.first;
    return os;
}
