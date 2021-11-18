#pragma once

#include <iostream>

using namespace std;

//print function using variadic templates.
void print() {
    cout << "Calling print()" << endl;
}

int count = 0;

template<typename T, typename... Types>
void print(const T& firstArg, const Types&... args) {
    //cout << "Argument number " << ++count << " --> " << firstArg << endl;
    print(args...);
}

//The Modern C++ Challenge Page 49
//minimum function using variadic templates.
template<typename T>
T minimum(T a, T b)
{
    return a < b ? a : b;
}

template<typename T1, typename... T>
T1 minimum(T1 a, T... args)
{
    return minimum(a, minimum(args...));
}

//minimum function using user provided comparator
template<typename Compare, typename T>
T minimumc(Compare comp, T a, T b)
{
    return comp(a, b) ? a : b;
}

template<typename Compare, typename T1, typename... T>
T1 minimumc(Compare comp, T1 a, T... args)
{
    return minimumc(comp, a, minimumc(comp, args...));
}

//Test above implementations
void callVariadicMins()
{
    cout << "Minimum among 5, 10, -99, -40, 100 is " << minimum(5, 10, -99, -40, 100) << endl;
    cout << "Minimum using std::greater amoing 5, 10, -99, -40, 100 is " << minimumc(std::greater<>(), 5, 10, -99, -40, 100) << endl;
}
