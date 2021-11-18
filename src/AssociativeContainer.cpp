#include "AssociativeContainer.h"

using namespace std;

using StudMarksPair = pair<Student, vector<int>>;

AssociativeContainer::AssociativeContainer()
{
    anEmployeeSet = {
        {"Aasim", "Surve", 34, 10000},
        {"Shatam", "Bhatt", 38, 15000},
        {"Viswam", "Kanduri", 40, 15000},
        {"Siva", "Paddin", 45, 20000},
        {"Nikhil", "Koshi", 38, 12000},
        {"Elroy", "Haw", 22, 4000},
        {"Mahad", "Hachim", 25, 5000}
    };

    aStringSet = {"Sachin", "Sehwag", "Rahul", "Dinesh", "Sourav", "Dhoni", "Irfan", "Ashwin"};
}

AssociativeContainer::~AssociativeContainer()
{
    //dtor
}

AssociativeContainer::AssociativeContainer(const AssociativeContainer& other)
{
    //copy ctor
    anEmployeeSet = other.anEmployeeSet;
    aStringSet = other.aStringSet;
}

AssociativeContainer& AssociativeContainer::operator=(const AssociativeContainer& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
/*
ostream& operator<<(ostream& os, const set<Employee>& empSet){
    os << "\nEmployees are : \n";
    for(const auto& employee : empSet) {
        os << employee << "\n";
    }
    return os;
}
*/
ostream& operator<<(ostream& os, const set<string> strSet){
    for(const auto& str : strSet) {
        os << str << "\t";
    }
    return os;
}

ostream& operator<<(ostream& os, const vector<int>& marks){
    for(const int& mark : marks){
        os << "\t" << mark;
    }
    return os;
}

void AssociativeContainer::populateSets() {

    cout << "Players are : " << aStringSet << endl;

    string removeBatsman;
    cout << "\n\nEnter the name of the player to be dropped : " ;
    cin >> removeBatsman;

    auto res = aStringSet.find(removeBatsman);
    if( res == aStringSet.end())
        cout << removeBatsman << " is not there in the team!!!" << endl;
    else {
        cout << removeBatsman << " has been removed from the team." << endl;
        aStringSet.erase(res);
        cout << "\nThe team now is : " << aStringSet << endl;
    }

    /*auto res = find_if(begin(aStringSet), end(aStringSet), [&removeBatsman](const auto& batsman){
        return removeBatsman == batsman;
    });
    if(res != end(aStringSet)) {
        aStringSet.erase(res);
        cout << removeBatsman <<" dropped." << endl;
        cout <<"\nThe team now is : " << aStringSet << endl;
    }
    else
        cout << removeBatsman <<" not found in the team." << endl;*/
}

void AssociativeContainer::populateEmployeeSet(){
    cout << anEmployeeSet << endl;
}

void AssociativeContainer::populateStudentSet() {
    Student aasim{"Aasim", "Surve", 16};
    Student fahim{"Fahim", "Mullaji", 15};
    Student imran{"Imran", "Dhondne", 16};
    aStudentSet.insert(aasim);
    aStudentSet.emplace(fahim);
    aStudentSet.insert(imran);

    aStudentSet.emplace("Irfan", "Dhondne", 17);
    aStudentSet.emplace("Ismail", "Kazi", 18);
    aStudentSet.insert({"Kaif", "Dabir", 16});
    aStudentSet.emplace("Makhdum", "Kazi", 16);
    aStudentSet.emplace("Rameez", "Khan", 16);
    aStudentSet.emplace("Zoheb", "Hamdulay", 16);

    cout << "Students are : \n" << aStudentSet << endl;

    set<Student> anotherStudentSet = {
        {"Abdullah", "Gadkari", 16},
        {"Mobin", "Kazi", 17},
        {"Shoaib", "Khan", 18},
        {"Aasim", "Surve", 16},
        {"Imran", "Dhondne", 16}
    };

    vector<Student> mergedStudentSet;
    merge(begin(aStudentSet), end(aStudentSet), begin(anotherStudentSet), end(anotherStudentSet), back_inserter(mergedStudentSet));
    cout << mergedStudentSet << endl;

    vector<Student> unionOfStudents;
    set_union(begin(aStudentSet), end(aStudentSet), begin(anotherStudentSet), end(anotherStudentSet), back_inserter(unionOfStudents));
    cout << unionOfStudents << endl;

    vector<Student> commonStudents;
    set_intersection(begin(aStudentSet), end(aStudentSet), begin(anotherStudentSet), end(anotherStudentSet), back_inserter(commonStudents));
    cout << commonStudents << endl;

    vector<Student> differntStudents;
    set_difference(begin(aStudentSet), end(aStudentSet), begin(anotherStudentSet), end(anotherStudentSet), back_inserter(differntStudents));
    cout << differntStudents << endl;

    //Found in either set but not found in both the sets
    vector<Student> symmetricDiff;
    set_symmetric_difference(begin(aStudentSet), end(aStudentSet), begin(anotherStudentSet), end(anotherStudentSet), back_inserter(symmetricDiff));
    cout << symmetricDiff << endl;

}

void AssociativeContainer::populateStudentMarksMap(){

    Student aasim{"Aasim", "Surve", 16};
    Student fahim{"Fahim", "Mullaji", 15};
    Student imran{"Imran", "Dhondne", 16};

    cout << "\n\n========================Student Sorted by operator< ========================" << endl;
    map<Student, vector<int>> studentMarks;
    studentMarks.emplace(StudMarksPair({"Aasim", "Surve", 16}, {60, 70, 80}));
    studentMarks.insert(StudMarksPair({"Fahim", "Mullaji", 15}, {50, 90, 90}));
    studentMarks[imran] = {70, 70, 70};
    studentMarks[{"Abdullah", "Gadkari", 16}] = {90, 90, 80};
    cout << studentMarks;

    cout << "\n\n========================Student Sorted by First Name ========================" << endl;
    {
        map<Student, vector<int>, StudentFirstNameSort> studentMarks;
        studentMarks.emplace(StudMarksPair({"Aasim", "Surve", 16}, {60, 70, 80}));
        studentMarks.insert(StudMarksPair({"Fahim", "Mullaji", 15}, {50, 90, 90}));
        studentMarks[imran] = {70, 70, 70};
        studentMarks[{"Abdullah", "Gadkari", 16}] = {90, 90, 80};
        cout << studentMarks;
    }
    cout << "\n\n========================Student Marks are========================" << endl;
    multimap<float, Student> marksStudentMap;
    for(const auto& student : studentMarks) {
        float m1 = 0.0;
        if(student.second.size() != 0)
            m1 = accumulate(begin(student.second), end(student.second), 0.0) / static_cast<float>(student.second.size());
        marksStudentMap.insert(pair<float, Student>(m1, student.first));
    }

    for(const auto& student : marksStudentMap)
    {
        vector<int> marks = studentMarks[student.second];
        cout << student.second << marks << endl;
    }
}
