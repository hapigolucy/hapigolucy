#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

template<typename Iter>
string bytes_to_hexstr(Iter begIter, Iter endIter, bool upperCase = false)
{
    std::stringstream oss;
    if(upperCase)
        oss.setf(std::ios_base::uppercase);
    while( begIter != endIter)
    {
        oss << std::hex
            << std::setw(2)
            << std::setfill('0')
            << static_cast<int>(*begIter);

        ++begIter;
    }
    std::string retVal;
    oss >> retVal;
    cout << "Returning : " << retVal << endl;
    return oss.str();
}

template<typename Cont>
string bytes_to_hexstr(Cont const& c, bool upperCase = false)
{
    return bytes_to_hexstr(begin(c), end(c), upperCase);
}

string& capitalize(string& text);

string& capitalizeSentence(string& text);

void runStringAndRegEx();

string compressString();
