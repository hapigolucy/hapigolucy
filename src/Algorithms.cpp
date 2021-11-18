#include<iostream>
#include<functional>

#include<random>
#include<iterator>
#include<unordered_map>
#include "Algorithms.h"

using namespace std;

Algorithms::Algorithms()
{
    //init();
}

Algorithms::~Algorithms()
{

}

Algorithms::Algorithms(const Algorithms& other)
{
    integerVector = other.integerVector;
    employeeVector = other.employeeVector;
}

Algorithms& Algorithms::operator=(const Algorithms& rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    //assignment operator
    return *this;
}

ostream& operator<<(ostream& os, vector<int> vec) {
    for(auto num : vec)
        os << num << "\t";
    return os;
}

void Algorithms::init() {
    integerVector = {10, -9, 6, 4, 5, 2, 0, 22, 10};
    employeeVector = {
        {"Aasim", "Surve", 34, 10000},
        {"Shatam", "Bhatt", 38, 15000},
        {"Viswam", "Kanduri", 40, 15000},
        {"Siva", "Paddin", 45, 20000},
        {"Nikhil", "Koshi", 38, 12000},
        {"Elroy", "Haw", 22, 4000},
        {"Mahad", "Hachim", 25, 4000},
        {"Another", "Hachim", 26, 4000},
        {"Another", "Haw", 25, 4000}
    };
}

void Algorithms::createUnorderedMap() {
    /*
    Refer 'The C++ Standard Library: A Tutorial and Reference' by Nicolai Josuttis Page 380
    for example to create unordered_map using lambdas instead of functors.
    */
    unordered_map<Employee, double, EmployeeHash, EmployeeEqual> employeeSalaryMap;
    Employee e{"Aasim", "Surve", 34, 10000};
    employeeSalaryMap.insert({e, 10417.76});
    employeeSalaryMap[{"Shatam", "Bhatt", 38, 15000}] = 15416.67;

    employeeSalaryMap.max_load_factor(0.7);
}

//Count
int Algorithms::countInVector(int target)
{
    auto res = min_element(begin(integerVector), end(integerVector));
    cout << "Minimum from the integer vector is : " << *res << endl;
    return count(integerVector.begin(), integerVector.end(), target);
}

int Algorithms::countWithCondition()
{
    /*return count_if(integerVector.begin(), integerVector.end(), [](const auto& number)
    {
        return number%2 != 0;
    });*/

    int employeesWithHighSalaries =
        count_if(begin(employeeVector), end(employeeVector), [](const auto& employee) {
            return employee.salary > 11000;
        });

    return employeesWithHighSalaries;
}

void Algorithms::employeesSalariesCategory() {
    int numHighSalary = count_if(begin(employeeVector), end(employeeVector), [](const auto& employee){
        return employee.salary > 11000;
    });
    int medianSalary = count_if(begin(employeeVector), end(employeeVector), [](const auto& employee){
        return employee.salary == 10000;
    });
    int numLowSalary = count_if(begin(employeeVector), end(employeeVector), [](const auto& employee){
        return employee.salary < 10000;
    });

    cout << "Number of employees with : "
        << "\nHigh Salaries   : " << numHighSalary
        << "\nMedium Salaries : " << medianSalary
        << "\nLow Salaries    : " << numLowSalary << endl;
}

//Find

void Algorithms::findEmployeeWith10KSalary() {
    double salary = 10000;
    auto res = find_if(begin(employeeVector), end(employeeVector), [&salary](const auto& employee){
        return employee.salary == salary;
    });
    if(res != end(employeeVector))
        cout << "Employee with " << salary << " salary : " << *res << endl;
    else
        cout << "No Employee has a salary of " << salary << endl;

    salary = 20000;
    auto res2 = find_if(res, end(employeeVector), [&salary](const auto& employee){
        return employee.salary == salary;
    });
    if(res2 != end(employeeVector))
        cout << "\nEmployee with " << salary << " salary : " << *res2 << endl;
    else
        cout << "No Employee has a salary of " << salary << endl;

    vector<Employee> empVector {
        {"Elroy", "Haw", 22, 4000},
        {"Mahad", "Hachim", 25, 5000}
    };
    auto res3 = find_first_of(begin(employeeVector), end(employeeVector), begin(empVector), end(empVector));
    if(res3 != end(employeeVector))
        cout << "find_first_of Found : " << *res3 << " at index " << res3 - begin(employeeVector)<< endl;
    else
        cout << "find_first_of Found Nothing!!!" << endl;

    auto res4 = search(begin(employeeVector), end(employeeVector), begin(empVector), end(empVector));
    if(res4 != end(employeeVector))
        cout << "Search Found : " << *res4 << " at index "<< res4 - begin(employeeVector) << endl;
    else
        cout << "Search Found Nothing !!!" << endl;
}

string Algorithms::findInVector(int target)
{
    auto iter = find(integerVector.begin(), integerVector.end(), target);
    if( iter != integerVector.end() )
        return " found";
    else
        return " not found";
}

bool Algorithms::findWithCondition()
{
    auto iter = find_if(integerVector.begin(), integerVector.end(), [](const auto& number)
    {
        return number % 2 == 0;
    });
    if( iter != integerVector.end() )
        return true;
    else
        return false;
}

bool Algorithms::findWithConditionNegated()
{
    auto iter = find_if_not(integerVector.begin(), integerVector.end(), [](const auto& number)
    {
        return number % 2 == 0;
    });

    if( iter != integerVector.end() )
        return true;
    else
        return false;
}

pair<bool, int> Algorithms::findFirstOf(vector<int>& temp)
{
    auto iter = find_first_of(integerVector.begin(), integerVector.end(), temp.begin(), temp.end());

    if(iter != integerVector.end())
        return make_pair(true, *iter);
    else
        return make_pair(false, 0);
}

//Sort
void Algorithms::sortStruct() {
    cout << "\nBefore sorting... ";
    cout << employeeVector << endl;

    //using operator<
    sort(employeeVector.begin(), employeeVector.end());
    cout <<"\nAfter Sorting using operator< ";
    cout << employeeVector << endl;

    //using lambda
    sort(begin(employeeVector), end(employeeVector), [](Employee emp1, Employee emp2){
        return emp1.salary < emp2.salary;
    });
    cout << "\nAfter sorting by salary ";
    cout << employeeVector << endl;

    bool sorted = is_sorted(employeeVector.begin(), employeeVector.end(), [](const Employee& e1, const Employee& e2){
        return e1.salary < e2.salary;
    });
    cout << "\n\nChecking if the employees are sorted by salary. ";

    if(sorted)
        cout << "\nSorted by salary." << employeeVector << endl;
    else
        cout << "\nNot sorted.";

    cout << "\n\nShuffled Employee Vector. ";
    random_device randomDevice;
    mt19937 generator(randomDevice());
    shuffle(employeeVector.begin(), employeeVector.end(), generator);
    cout << employeeVector << endl;

    /***Stable sort will sort the Employees vector in aplphabetical order if two Employees have same salary.***/
    stable_sort(begin(employeeVector), end(employeeVector), [](const Employee& e1, const Employee& e2){
        return e1.salary < e2.salary;
    });
    cout << "\n\nStable Sort on Employee Vector.";
    cout << employeeVector << endl;

    cout << "\n\nFinding Max and Min employees." << endl;
    auto maxEmployee = max_element(begin(employeeVector), end(employeeVector), [](const Employee& emp1, const Employee& emp2){
        return emp1.salary < emp2.salary;
    });
    auto minEmployee = min_element(begin(employeeVector), end(employeeVector), [](const Employee& emp1, const Employee& emp2){
        return emp1.salary < emp2.salary;
    });
    cout << "Max Employee is : " << *maxEmployee << endl;
    cout << "Min Employee is : " << *minEmployee << endl;

    cout << "\n\n========================\n" <<"std::partial_sort_copy: Finding the bottom 3 and top 3 employees by salary." << "\n========================" << endl;
    vector<Employee> empList(3);
    partial_sort_copy(begin(employeeVector), end(employeeVector), begin(empList), end(empList), [](const Employee& e1, const Employee& e2){
        return e1.salary < e2.salary;
    });
    cout <<"Bottom 3 " << empList << endl;

    vector<Employee> empList2(3);
    partial_sort_copy(begin(employeeVector), end(employeeVector), begin(empList2), end(empList2), [](const Employee& e1, const Employee& e2){
        return e1.salary > e2.salary;
    });
    cout <<"Top 3 " << empList2 << endl;

    partial_sort(begin(employeeVector), begin(employeeVector) + 3, end(employeeVector), [](const Employee& e1, const Employee& e2){
    return e1.salary < e2.salary;
    });
    cout <<"Top 3 again " << employeeVector << endl;

    cout << "\n\n========================\n" << "std::nth_element employee with the 3rd highest salary." << "\n========================" << endl;
    nth_element(begin(employeeVector), begin(employeeVector) + 5, end(employeeVector), [](const Employee& e1, const Employee& e2){
        return e1.salary < e2.salary;
    });
    cout << employeeVector[5] << " Has the 5th highest salary amongst : \n\n" << employeeVector << endl;

}

//Compare and Accumulate
void Algorithms::compareEmployees() {
    vector<Employee> employeeVector2 = employeeVector;
    employeeVector2.emplace_back("Trevor", "Tang", 40, 15000);
    employeeVector.emplace_back("Ying", "Hao", 25, 7000);
    bool equalEmpVectors = equal(begin(employeeVector), end(employeeVector), begin(employeeVector2), end(employeeVector2));
    if (equalEmpVectors)
        cout << "Both Employee lists are equal." << endl;
    else
        cout << "The Employee lists are not equal." << endl;

    auto diff = mismatch(begin(employeeVector), end(employeeVector), begin(employeeVector2));
    cout << "Mismatched employee in the  first list : " << *(diff.first) << endl;

    cout << "Mismatched employee in the second list : " << *(diff.second) << endl;
}

void Algorithms::shuffleVector()
{
    sort(integerVector.begin(), integerVector.end());

    cout << "\n\nSorted Int Vector..." << endl;
    for( const auto& i : integerVector) {
        cout << i << "\t";
    }

    random_device randomDevice;
    mt19937 generator(randomDevice());
    shuffle(integerVector.begin(), integerVector.end(), generator);
    cout << "\nShuffled Int Vector..." << endl;
    cout << integerVector << endl;
    /*for( const auto& i : integerVector) {
        cout << i << "\t";
    }*/
}

void Algorithms::copyAlgos()
{
    cout << "\n\n========================\n" <<"Original Employee Vector" << "\n========================" << endl;
    cout << employeeVector << endl;

    std::vector<Employee> reverseEmployeeVector;
    reverse_copy(begin(employeeVector), end(employeeVector), back_inserter(reverseEmployeeVector));
    cout << "\n\n========================\n" <<"std::reverse_copy: Reversed Employee Vector" << "\n========================" << endl;
    cout << reverseEmployeeVector << endl;

    cout << "\n\n========================\n" <<"std::move: Moving a vector" << "\n========================" << endl;
    cout << "Vector to be moved : \n" << reverseEmployeeVector << endl;
    vector<Employee> anotherReverseEmployeeCopy;
    anotherReverseEmployeeCopy = reverseEmployeeVector;

    std::deque<Employee> movedUsingBackInserter, movedUsingFrontInserter;
    move(begin(reverseEmployeeVector), end(reverseEmployeeVector), back_inserter(movedUsingBackInserter));
    move(begin(anotherReverseEmployeeCopy), end(anotherReverseEmployeeCopy), front_inserter(movedUsingFrontInserter));
    cout << "Back  Inserter (Maintain order): \n" << movedUsingBackInserter  << endl;
    cout << "Front Inserter (Reverse order) : \n" << movedUsingFrontInserter << endl;
    copy_backward(begin(movedUsingBackInserter), begin(movedUsingBackInserter) + 4, begin(movedUsingBackInserter)+3+5);
    cout << "copy_backward: Copying first 5 elements into the container starting at position 3.\n";
    cout << "cannot use copy because values from 3 to 5 will be overwritten.\n" << movedUsingBackInserter << endl;


    //Expected state Only the row from above three should remain becaue the comparison operator has been defined only on the first and last name.
    cout << "\n\n========================\n" <<"std::unique_copy: Employee Vector after Unique Copy" << "\n========================" << endl;
    vector<Employee> uniqueEmployeeVector;
    unique_copy(begin(employeeVector), end(employeeVector), back_inserter(uniqueEmployeeVector));
    cout << uniqueEmployeeVector << endl;

    cout << "\n\n========================\n" <<"std::copy_if: Employee Vector. Removing dummy values having 'Another' in their first name." << "\n========================" << endl;
    vector<Employee> anotherEmployees(employeeVector.size());
    copy_if( begin(employeeVector),
             end(employeeVector),
             begin(anotherEmployees),
             [](const Employee& emp){ return emp.firstName.find("Another") == string::npos; } );
    cout << anotherEmployees<< endl;

    cout << "\n\n========================\n" <<"std::copy_backward: Doesnt seem to be of much use since order is preserved. reverser_copy should be used if the intention is to reverse the order." << "\n========================" << endl;
    copy_backward(begin(anotherEmployees), end(anotherEmployees), end(anotherEmployees));

    random_device randomDevice;
    mt19937 generator(randomDevice());
    shuffle(anotherEmployees.begin(), anotherEmployees.end(), generator);
    cout << anotherEmployees << endl;

    cout << "\n\n========================\n"
    <<"std::remove_if: remove moves the elements to be removed to the end of the vector and returns the iterator to the starting position of all elements that need to be removed."
    "\nAfter remove, erase need to be run beginning at the return iterator upto the end of the vector."
    << "\n========================" << endl;
    auto newend = remove_if(begin(anotherEmployees), end(anotherEmployees), [](const Employee& emp){
        return emp.firstName.empty();
    });
    anotherEmployees.erase(newend, end(anotherEmployees));
    cout << anotherEmployees << endl;

    /*cout << "\n\n========================\n" << "Splitting a long String" << "\n========================" << endl;
    string aLongString = "a long string that needs to be split";
    cout << "Length of the long string is : " << aLongString.length() << endl;
    for(auto& c : aLongString) {
        cout << c << endl;
    }*/
}

void Algorithms::transformAlgos(){
    cout << "\n\n========================\n" <<"std::transform: Give a raise of 10% to every employee. Remove all the dummy employees." << "\n========================" << endl;
    transform(begin(employeeVector), end(employeeVector), begin(employeeVector), [](Employee& emp){
        emp.salary *= 1.10;
        return emp;
    });
    //cout << employeeVector << endl;

    employeeVector.erase(remove_if(begin(employeeVector), end(employeeVector), [](const Employee& emp){
        return emp.firstName.find("Another") != string::npos;
    }), end(employeeVector));

    cout << employeeVector << endl;
}

void Algorithms::reverseAlgos() {
    cout << "\n\n========================\n" << "std::reverse: Reversing the contents of the container." << "\n========================" << endl;
    reverse(begin(employeeVector), end(employeeVector));
    cout << employeeVector << endl;

    iter_swap(begin(employeeVector), end(employeeVector)-1);
    cout << employeeVector << endl;

    cout << "\n\n========================\n" << "std::reverse_copy: Reversing and copying the contents of the container." << "\n========================" << endl;
    deque<Employee> anotherEmployeeVector;
    reverse_copy(begin(employeeVector), end(employeeVector), back_inserter(anotherEmployeeVector));
    cout << anotherEmployeeVector << endl;
}

void Algorithms::swapEmployees() {
    cout << "\n\n========================\n" << "std::swap: Swapping the first and last Employees." << "\n========================" << endl;
    cout << "Before Swap " << employeeVector << endl;
    swap(*begin(employeeVector), *(end(employeeVector)-1));
    cout << "After Swap " << employeeVector << endl;
}

void Algorithms::partitionBySalary() {
    cout << "\n\n========================\n" << "std::partition: Patitioning Employees by their salaries." << "\n========================" << endl;
    cout << "Before Partition " << employeeVector << endl;
    partition(begin(employeeVector), end(employeeVector), [](const Employee& e1){
        return e1.salary < 11000;
    });
    cout <<"After Partition " << employeeVector << endl;
}

void Algorithms::splitString() {
    vector<string> splittedStrVec;
    string aLargeString = {"A quick brown fox jumped over the lazy dog.!!! The dog was quick to react."};
    string delimiters = {" ,./\\!"};
    string::iterator itBeg = begin(aLargeString);
    string::iterator itEnd;
    //itEnd = find(begin(aLargeString), end(aLargeString), ' ');

    itEnd = find_first_of(begin(aLargeString), end(aLargeString), begin(delimiters), end(delimiters));


    string temp(itBeg, itEnd);
    splittedStrVec.emplace_back(temp);

    while(itEnd != end(aLargeString)) {
        itBeg = itEnd + 1;
        //itEnd = find(itBeg, end(aLargeString), ' ');
        itEnd = find_first_of(itBeg, end(aLargeString), begin(delimiters), end(delimiters));
        string temp(itBeg, itEnd);
        splittedStrVec.emplace_back(temp);
    }
    string emptyStr;
    splittedStrVec.erase(remove_if(begin(splittedStrVec), end(splittedStrVec), [](const string& str){
        return str.size() == 0;
    }));

    for(const auto& str : splittedStrVec)
        cout << str << "\t";
    cout <<"\nNumber of words in the string : " << splittedStrVec.size() << "\n\n" << endl;
}

void Algorithms::stringReplace() {
    string s1 = "\n\nExample of replace.";
    string s2 = "Demonstration";
    cout << s1 << " --> ";
    s1.replace(0, 9, s2);
    cout << s1 << endl;

    string s3 = "HeyWorld!";
    cout << s3 << " --> ";
    s3.replace(0, 3, "Hello ");
    cout << s3 << endl;
}

int Algorithms::compressString(){
    //string input = "aaaabbccccd";
    vector<char> input = {'a', 'a', 'b', 'b', 'b', 'b', 'c'};
    int length = input.size();
    vector<char> output;

    function<int(int)> getCount = [&](int index){
        int cnt = 1;
        while( index < length-1 && input[index] == input[index+1] ){
            ++cnt;
            ++index;
        }
        return cnt;
    };

    for( int i = 0; i < length; ){
        int cnt = getCount(i);
        char current = input[i];
        input[i] = current;
        if(cnt > 1) {
            //cout << current << cnt << endl;
            string replacement = current + to_string(cnt);
            for(char r : replacement)
                input.push_back(r);
        }
        else {
            //cout << current << endl;
            input.push_back(current);
        }

        i += cnt;
    }
    input.erase(begin(input), begin(input)+length);
    for( char a : input)
        cout << a;
    cout << endl;
    return input.size();
}

